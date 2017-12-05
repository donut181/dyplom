#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    DEFAULT_SCS_SRC("/home/marcin/Pobrane")
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(1);
    Config::instance().load();
    prepareWorkspace();
    startObservingWorkspace();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::on_actionCreate_triggered()
{
    CreateSimulatorDialog dialog(this);
    if(dialog.exec()){
        Simulator sim = dialog.getData(); //To trzebabędzie zmienić
        sim.data();
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::fromStdString(sim.command())));
    }
}*/

void MainWindow::on_actionParse_scs_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,QObject::tr("Chose Netlist"),DEFAULT_SCS_SRC,QObject::tr("Netlist Files (*.scs)"));
    if(filename.isEmpty()){
        std::cout << tr("No file specified").toStdString() << std::endl;
    }else{
        ParseDialog parseDialog(filename,this);
        if(parseDialog.exec()){
            Netlist netlist = parseDialog.getData();
            netlist.rewrite();
            ConfigureCommandDialog configCommandDialog(netlist,this);
            if(configCommandDialog.exec()){
                std::cout << "rows: " << ui->tableWidget->rowCount()+0 << std::endl;
                std::cout << "columns: " << ui->tableWidget->columnCount()+0 << std::endl;
                ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(configCommandDialog.getCommand()));
                        //setText(configCommandDialog.getCommand());
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

void MainWindow::startObservingWorkspace(){
    SimulationsObserver *sim_observer = new SimulationsObserver(m_app_home_path);
    connect(sim_observer,&SimulationsObserver::resultReady,this,&MainWindow::on_result_from_sim_observer);
    sim_observer->start();
}

void MainWindow::on_result_from_sim_observer(const QString &s){
    ui->tableWidget->setItem(0,0,new QTableWidgetItem(s));
}

void MainWindow::prepareWorkspace()
{
    if(Config::instance().containsOption("app_home"))
        m_app_home_path = Config::instance().getOption("app_home");
    else
        m_app_home_path = QDir().homePath().append(QString("/Sim_app_workspace"));

    QDir app_home(m_app_home_path);
    if(!app_home.exists())
        app_home.mkpath(".");
}
