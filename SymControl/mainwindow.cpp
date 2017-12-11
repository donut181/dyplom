#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    DEFAULT_SCS_SRC("/home/marcin/Pobrane")
{
    ui->setupUi(this);
    Config::instance().load();
    prepareWorkspace();
    startObservingWorkspace();
}

MainWindow::~MainWindow()
{
    foreach(Simulator* sim,m_SimulatorList){
        delete sim;
    }
    delete ui;
}

void MainWindow::on_actionParse_scs_triggered()
{
    QUuid uuid = QUuid();
    QString filename = QFileDialog::getOpenFileName(this,QObject::tr("Chose Netlist"),DEFAULT_SCS_SRC,QObject::tr("Netlist Files (*.scs)"));
    if(filename.isEmpty()){
        std::cout << tr("No file specified").toStdString() << std::endl;
    }else{
        ParseDialog parseDialog(filename,this);
        if(parseDialog.exec()){
            Netlist netlist = parseDialog.getData();
            ConfigureCommandDialog configCommandDialog(netlist,this);
            if(configCommandDialog.exec()){
                qDebug() << "DO SOMETHING WITH DIALOG RESULT";
                QString process_dir_path = QString(m_app_home_path).append('/').append(uuid.createUuid().toString());
                QString process_netlist_path = QString(process_dir_path).append('/').append(QFileInfo(netlist.fileName()).fileName());
                QString process_command_path = QString(process_dir_path).append("/command");
                QDir().mkdir(process_dir_path);
                netlist.rewrite(process_netlist_path);
                QFile command_file(process_command_path);
                if (command_file.open(QIODevice::WriteOnly)){
                    QTextStream stream (&command_file);
                    stream << configCommandDialog.getCommand();
                }
                m_SimulatorList.append(new Simulator(process_dir_path));
            }
        }
    }

}

void MainWindow::on_actionParse_output_Sdat_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,QObject::tr("Chose output file"),DEFAULT_SCS_SRC,QObject::tr("Output Files (*.sdat)"));
    if(filename.isEmpty()){
        std::cout << tr("No file specified").toStdString() << std::endl;
    }else{
        OutputParser parser(filename);
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
}

void MainWindow::startObservingWorkspace()const{
    SimulationsObserver *sim_observer = new SimulationsObserver(m_app_home_path);
    connect(sim_observer,&SimulationsObserver::resultReady,this,&MainWindow::on_result_from_sim_observer);
    sim_observer->start();
}

void MainWindow::on_result_from_sim_observer(const QStringList &sim_list){
    ui->tableWidget->setRowCount(sim_list.count());
    qDebug() << sim_list.count();
    for(int i=0; i<sim_list.count(); ++i){
        QString sim_dir_path = QString(m_app_home_path).append('/').append(sim_list.at(i));
        QDir sim_files(sim_dir_path);
        QStringList sim_parts = sim_files.entryList(QDir::Files);
        if(sim_parts.contains("command")){
            QFile command_file(QString(sim_dir_path).append("/command"));
            if(command_file.open(QIODevice::ReadOnly)){
                QTextStream in(&command_file);
                QString command_string = in.readLine();
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(command_string));
                command_file.close();
            }

        }
        foreach (QString sim_part, sim_parts) {
            if(sim_part.right(4) == ".scs"){
                qDebug() << sim_part << " is a netlist";
                ui->tableWidget->setItem(i,2,new QTableWidgetItem(sim_part));
            }
        }

        qDebug() << sim_parts;
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(sim_list.at(i)));
    }
}

void MainWindow::prepareWorkspaceDir()
{
    if(Config::instance().containsOption("app_home"))
        m_app_home_path = Config::instance().getOption("app_home");
    else{
        m_app_home_path = QDir().homePath().append(QString("/.Sim_app_workspace"));
        Config::instance().setOption("app_home",m_app_home_path);
    }

    m_app_workspace = QDir(m_app_home_path);
    if(!m_app_workspace.exists())
        m_app_workspace.mkpath(".");
}

QStringList MainWindow::loadSimulatorListFromWorkspace()
{
    QStringList simulatorList = m_app_workspace.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    for(int i = 0; i<simulatorList.count(); ++i){
        QDir tmpDir = QDir(QString(m_app_home_path).append('/').append(simulatorList.at(i)));
        QStringList tmpDirContent = tmpDir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::NoSymLinks);
        if(tmpDirContent.count() == 0){
            qDebug() << "Empty sim folder";
            simulatorList.removeAt(i--);
            continue;
        }
        if(!tmpDirContent.contains("command")){
            qDebug() << "No command file in sim folder";
            simulatorList.removeAt(i--);
            continue;
        }
    }
    return simulatorList;
}

void MainWindow::populateSimulators(QStringList &simUids){
    foreach(QString simUid, simUids){
        m_SimulatorList.append(new Simulator(QString(m_app_home_path).append('/').append(simUid)));
    }
}

void MainWindow::prepareWorkspace()
{
    prepareWorkspaceDir();
    QStringList simListFromWorkspace = loadSimulatorListFromWorkspace();
    populateSimulators(simListFromWorkspace);
    qDebug() << m_SimulatorList;
}
