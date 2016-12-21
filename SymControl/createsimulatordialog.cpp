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
