#include "Simulator.h"

Simulator::Simulator(){
    _stdout = "/dev/null";
    _stdin = "/dev/null";
    _stderr = "/dev/null";
    m_state = "fresh";
}

Simulator::Simulator(QString workspace_path, QString uuid): Simulator(){
    m_workspace = workspace_path.append('/').append(uuid);
    m_uuid = uuid;
    if(Config::instance().containsOption("simulator_app"))
        setCommand(Config::instance().getOption("simulator_app").toStdString());
    else
        setCommand("spectre");
    prepareCommand();
    QString pid_file_path = QString(m_workspace).append("/pid");
    QFile pid_file(pid_file_path);
    if(pid_file.exists()){
        if(pid_file.open(QIODevice::ReadOnly)){
            QString read_pid = QTextStream(&pid_file).readLine();
            pid = read_pid.toInt();
        }else
            qDebug() << "can't open pid file for " << m_uuid;
    }
    data();
}

void Simulator::prepareCommand(){
    QString pathToCommand = QString(m_workspace).append("/command");
    QFile command_file(pathToCommand);
    if (command_file.open(QIODevice::ReadOnly)){
        QTextStream stream (&command_file);
        QString commandLine = stream.readLine();
        QStringList commandFlags = commandLine.split(' ');
        foreach (QString flag, commandFlags) {
            addFlag(flag.toStdString());
        }
        command_file.close();
    }else{
        qDebug() << "can't open command file in " << m_workspace;
    }
}

void Simulator::write_pid_to_file()
{
    QFile pid_file(QString(m_workspace).append("/pid"));
    if(pid_file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QTextStream pid_file_stream(&pid_file);
        pid_file_stream << pid;
        pid_file.close();
    }
}

void Simulator::get_progress()
{
    QString log_file_path;
    foreach (std::string flag, flags) {
        if(QString::fromStdString(flag).contains(".log"))
            log_file_path = QString::fromStdString(flag);
    }
    qDebug() << "log_file: " << log_file_path;

    if(log_file_path.isEmpty()){
        qDebug() << "no .log file in flags = no progress raports";
        m_progress = "?";
    }else{
        QFile log_file(QString(m_workspace).append('/').append(log_file_path));
        if(log_file.open(QIODevice::ReadOnly)){
            QTextStream log_file_stream(&log_file);
            QString line;
            while(!log_file_stream.atEnd())
                line = log_file_stream.readLine();
            if(line.contains("spectre completes"))
                setState("ready");
            else if(line.contains(QRegExp("\\([\\d\\.]+ %\\)"))){
                // .....(123.123 %)... -> split left paren, then right and take whats inside
                QStringList line_parts = line.split('(');
                QString after_left_paren = line_parts.at(1);
                line_parts = after_left_paren.split(')');
                m_progress = line_parts.at(0);
                qDebug() << m_progress;
            }
        }else
            qDebug() << "can't open .log in " << m_workspace;
    }
}

void Simulator::calculate_fft()
{
    QString sdat_file_path = QString(m_workspace).append('/');
    foreach (std::string flag, flags) {
        if(QString::fromStdString(flag).contains(".Sdat")){
            sdat_file_path.append(QString::fromStdString(flag));
            break;
        }
    }

    OutputParser parser(sdat_file_path);
    parser.parse();
    int n;
    if(Config::instance().containsOption("n"))
        n=Config::instance().getOption("n").toInt();
    else{
        std::cout << "No N specified in config, using n=128" << std::endl;
        n=128;
    }
    parser.limitValuesNumber(n);
    parser.ffTransform();
    std::cout << "size: " << parser.m_fft.size() << std::endl;
    parser.saveValuesToFile();
    std::cout << "size: " << parser.m_fft.size() << std::endl;
    parser.saveFftToFile();
    std::cout << "size: " << parser.m_fft.size() << std::endl;
}

void Simulator::calculate_results()
{
    calculate_fft();
    setState("finished");
}

void Simulator::setCommand(std::string program){
    programName = program;
    //adding flag 0 -> name of program
    flags.push_back(programName.substr(programName.find_last_of('/')+1));
}

void Simulator::addFlag(std::string flag){
    flags.push_back(flag);
}

void Simulator::setState(QString state)
{
    QFile stateFile(QString(m_workspace).append("/"+m_stateFile));
    if(stateFile.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QTextStream stream(&stateFile);
        stream << state;
        stateFile.close();
    }else{
        qDebug() << "Can't open state file in " << m_workspace;
    }
}

void Simulator::getState()
{
    QFile stateFile(QString(m_workspace).append("/"+m_stateFile));
    if(stateFile.open(QIODevice::ReadOnly)){
        QTextStream stream(&stateFile);
        m_state = stream.readLine();
        stateFile.close();
    }else{
        qDebug() << "Can't open state file in " << m_workspace;
    }
}

void Simulator::data(){
    std::cout << std::endl
        << "Program: " << programName << " pid: " << pid << std::endl
        << "out:" << _stdout << " in :" << _stdin << " err:" << _stderr << std::endl
        << m_workspace.toStdString() << std::endl
        << "---command---" << std::endl;
    foreach (std::string flag, flags) {
       std::cout << flag << " ";
    }
    std::cout << std::endl << "-------------" << std::endl << std::endl;
}

void Simulator::refresh_state()
{
    QFile state_file(QString(m_workspace).append("/state"));
    if(state_file.exists()){
        getState();
        if(m_state.contains("fresh")){
            qDebug() << m_uuid << " fresh";
            start();
            write_pid_to_file();
            setState("in progress");
        }else if(m_state.contains("in progress")){
            qDebug() << m_uuid << " in progress";
            get_progress();
        }else if(m_state.contains("ready")){
            qDebug() << m_uuid << " ready for analysis";
            calculate_results();
        }else if(m_state.contains("finished")){
            qDebug() << m_uuid << " finished";
        }
    }else
        qDebug() << "state file does not exist!";
}

QStringList Simulator::report_state(){
    QString netlist_file_name;
    foreach (std::string flag, flags) {
        if(QString::fromStdString(flag).contains(".scs")){
            netlist_file_name = QString::fromStdString(flag);
            break;
        }
    }

    QString state = m_state;
    if (state == "in progress"){
        state.append(" ").append(m_progress);
    }

    QStringList report;
    report.push_back(QString::number(pid));
    report.push_back(netlist_file_name);
    report.push_back(state);
    return report;
}

void Simulator::start(){
    if(programName.empty() || _stdin.empty() || _stdout.empty() || _stderr.empty()){
        std::cout << "cant start new process, no name,stdin,stdout or stderr" << std::endl;
    }else{
        pid = fork();
        if(pid == 0){
            //only for child

            //steps to daemonize
            //1.changing file mode mask
            umask(0);

            //2.creatin SID for child process
            sid = setsid();
            if (sid<0){
                //error
                std::cout << "error with setsid" << std::endl;
            }

            //3.changing dir so current wont be locked
            if( (chdir(m_workspace.toStdString().c_str()) ) < 0){
                std::cout << "error with chdir" << std::endl;
            }

            //4.redirect stdio [to null?]
            freopen(_stdin.c_str(),"r",stdin);
            freopen(_stdout.c_str(),"w",stdout);
            freopen(_stderr.c_str(),"w",stderr);

            //and now exec sth
            for(size_t i=0; i<flags.size(); ++i)
                cFlags.push_back(const_cast<char*>(flags[i].c_str()));
            cFlags.push_back(NULL);

            if(execvp(programName.c_str(), &cFlags[0]) == -1){
                std::cout<< "execvp failed" << std::endl;
            }


        }else if(pid <0){
            //error
            std::cout << "error during fork() " << std::endl;
        }else{
            std::cout << "child process has started " << pid << std::endl;
        }
    }
}

//void Simulator::kill(){
//    ::kill(pid,SIGTERM);
//}
