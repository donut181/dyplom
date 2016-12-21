#include "parsedialog.h"
#include "ui_parsedialog.h"

ParseDialog::ParseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParseDialog)
{
    ui->setupUi(this);
}

ParseDialog::~ParseDialog()
{
    delete ui;
}
