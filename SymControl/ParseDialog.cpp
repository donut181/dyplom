#include "ParseDialog.h"
#include "ui_parsedialog.h"
#include "OptionsTab.h"
#include "extrastab.h"
#include <QDebug>

ParseDialog::ParseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParseDialog)
{
    ui->setupUi(this);
    QString filename = QFileDialog::getOpenFileName(this,QObject::tr("Chose Netlist"),"/home/marcin/Pobrane",QObject::tr("Netlist Files (*.scs)"));
    m_netlist = new Netlist(filename);
    m_netlist->parse();

    tabWidget = new QTabWidget;
    tabWidget->addTab(new OptionsTab(m_netlist->parameters()),tr("Parameters"));
    tabWidget->addTab(new OptionsTab(m_netlist->simulatorOptions()),tr("Options"));
    tabWidget->addTab(new ExtrasTab(m_netlist->include(),m_netlist->simulationType()),tr("Extras")) ;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(ui->buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Netlist Configuration"));
}

ParseDialog::~ParseDialog()
{
    delete ui;
    delete m_netlist;
}
