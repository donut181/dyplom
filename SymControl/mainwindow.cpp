#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Config::instance().load();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCreate_triggered()
{
    CreateSimulatorDialog dialog(this);
    if(dialog.exec()){
        Simulator sim = dialog.getData(); //To trzebabędzie zmienić
        sim.data();
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::fromStdString(sim.command())));
    }
}

void MainWindow::on_actionParse_scs_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,QObject::tr("Chose Netlist"),"/home/marcin/Pobrane",QObject::tr("Netlist Files (*.scs)"));
    if(filename.isEmpty()){
        std::cout << tr("No file specified").toStdString() << std::endl;
    }else{
        ParseDialog dialog(filename,this);
        if(dialog.exec()){
            Netlist netlist = dialog.getData();
            netlist.rewrite();
        }
    }

}

void MainWindow::on_actionParse_output_Sdat_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,QObject::tr("Chose output file"),"/home/marcin/Pobrane",QObject::tr("Output Files (*.sdat)"));
    if(filename.isEmpty()){
        std::cout << tr("No file specified").toStdString() << std::endl;
    }else{
        OutputParser parser(filename);
        parser.parse();
        parser.save("trololo");
    }
}
