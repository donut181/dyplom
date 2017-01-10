#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    DEFAULT_SRC("/home/marcin/Pobrane")
{
    ui->setupUi(this);
    Config::instance().load();
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
    QString filename = QFileDialog::getOpenFileName(this,QObject::tr("Chose Netlist"),DEFAULT_SRC,QObject::tr("Netlist Files (*.scs)"));
    if(filename.isEmpty()){
        std::cout << tr("No file specified").toStdString() << std::endl;
    }else{
        ParseDialog parseDialog(filename,this);
        if(parseDialog.exec()){
            Netlist netlist = parseDialog.getData();
            netlist.rewrite();
            ConfigureCommandDialog configCommandDialog(netlist,this);
            if(configCommandDialog.exec()){
                ui->textEdit->setText(configCommandDialog.getCommand());
            }
        }
    }

}

void MainWindow::on_actionParse_output_Sdat_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,QObject::tr("Chose output file"),DEFAULT_SRC,QObject::tr("Output Files (*.sdat)"));
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
