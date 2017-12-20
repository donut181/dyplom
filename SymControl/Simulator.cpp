#include "Simulator.h"

Simulator::Simulator(){
    std::cout << "Simulator created" << std::endl;
    _stdout = "/dev/null";
    _stdin = "/dev/null";
    _stderr = "/dev/null";
    m_state = "fresh";
}

Simulator::Simulator(QString workspace_path): Simulator(){
    m_workspace = workspace_path;
    qDebug() << "Do sth with command!";
    setCommand("python");
    addFlag("/home/marcin/bin/spectre.py");
    addFlag("asdf");
    addFlag("orly?");
    addFlag("hehehe");
    data();
    start();
}

void Simulator::setCommand(std::string program){
    programName = program;
    //adding flag 0 -> name of program
    flags.push_back(programName.substr(programName.find_last_of('/')+1));
}

void Simulator::addFlag(std::string flag){
    flags.push_back(flag);
}

std::string Simulator::command()const{
    return programName;
}
std::string Simulator::firstFlag()const{
    return flags.at(1);
}
void Simulator::data(){
    std::cout << "Program: " << programName
        << " pid: " << pid << std::endl
        << "out:" << _stdout
        << " in :" << _stdin
        << " err:" << _stderr << std::endl
        << m_workspace.toStdString()
        << std::endl<<std::endl;
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
            if((chdir(m_workspace.toStdString().c_str())) < 0){
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

void Simulator::kill(){
    ::kill(pid,SIGTERM);
}
