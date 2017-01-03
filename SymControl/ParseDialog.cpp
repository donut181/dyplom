#include "ParseDialog.h"
#include "ui_parsedialog.h"

ParseDialog::ParseDialog(QString filename,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParseDialog)
{
    ui->setupUi(this);

    m_netlist = new Netlist(filename);
    m_netlist->parse();

    tabWidget = new QTabWidget;
    m_parametersTab = new OptionsTab(m_netlist->parameters());
    m_optionsTab = new OptionsTab(m_netlist->simulatorOptions());
    m_extrasTab = new ExtrasTab(m_netlist->include(),m_netlist->simulationType());

    tabWidget->addTab(m_parametersTab,tr("Parameters"));
    tabWidget->addTab(m_optionsTab,tr("Options"));
    tabWidget->addTab(m_extrasTab,tr("Extras"));

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

Netlist ParseDialog::getData()const{
    //retriving data from forms logic
    //parameters:
    QString parametersList = m_parametersTab->getValues();

    //simOptions:
    QString optionsList = m_optionsTab->getValues();

    //simType
    //this is line which can start with e.g. "tran tran " and it may be implemented badly. Check ExtrasTab::getValues()
    //and also its prepended with "dcOp dc write=..." simulation
    QString simTypeList = m_extrasTab->getValues();

    //include:
    //its not clear whether it starts with " or not, so it is clarified here
    QString include = m_extrasTab->getIncludeField().remove('"');
    include.prepend('"');
    include.append('"');

    //save letter<9:0>
    //its line right after parameters list in netlist
    QString saveLetterOut;
    if(m_extrasTab->isSaveOptionChecked()){
        saveLetterOut = m_extrasTab->getSaveString();
        //adding after parameters list
        parametersList.append("\n").append(saveLetterOut);
    }else{
        std::cout << "No including save option" << std::endl;
    }

    //multithread
    //its just option added to optionsList
    if(m_extrasTab->isMultithreadOptionChecked()){
        optionsList.append("multithread=on ");
    }

    //now changing netlist and returning it with possibly new values
    m_netlist->setInclude(include);
    m_netlist->setParameters(parametersList);
    m_netlist->setSimulatorOptions(optionsList);
    m_netlist->setSimulatorType(simTypeList);
    return *m_netlist;
}
