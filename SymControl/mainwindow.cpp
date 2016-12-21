#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    Config::instance().load();
    ParseDialog dialog(this);
    dialog.exec();
}
