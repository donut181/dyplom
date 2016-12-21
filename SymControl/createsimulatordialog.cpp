#include "createsimulatordialog.h"
#include "ui_createsimulatordialog.h"

CreateSimulatorDialog::CreateSimulatorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateSimulatorDialog)
{
    ui->setupUi(this);
}

CreateSimulatorDialog::~CreateSimulatorDialog()
{
    delete ui;
}

Simulator CreateSimulatorDialog::getData()const{
    Simulator sim;
    if(!ui->commandLineEdit->text().isEmpty()){
        sim.setCommand(ui->commandLineEdit->text().toStdString());
    }

    if(!ui->flag1LineEdit->text().isEmpty()){
        sim.addFlag(ui->flag1LineEdit->text().toStdString());
    }
    if(!ui->flag2LineEdit->text().isEmpty()){
        sim.addFlag(ui->flag2LineEdit->text().toStdString());
    }
    return sim;
}
