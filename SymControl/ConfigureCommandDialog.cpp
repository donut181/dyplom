#include "ConfigureCommandDialog.h"
#include "ui_configurecommanddialog.h"

ConfigureCommandDialog::ConfigureCommandDialog(const Netlist& netlist,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureCommandDialog)
{
    ui->setupUi(this);
    QFormLayout *layout = new QFormLayout;

    //escape chars
    QCheckBox *escCharCheck = new QCheckBox(tr("+escchars"));
    escCharCheck->setChecked(true);
    layout->addRow(escCharCheck);
    m_checkboxList.insert("escchars",escCharCheck);

    //parasitics
    QCheckBox *parasiticsCheck = new QCheckBox(tr("+parasitics"));
    parasiticsCheck->setChecked(true);
    layout->addRow(parasiticsCheck);
    m_checkboxList.insert("parasitics",parasiticsCheck);

    //64bit
    QCheckBox *sixtyFourCheck = new QCheckBox(tr("-64"));
    sixtyFourCheck->setChecked(true);
    layout->addRow(sixtyFourCheck);
    m_checkboxList.insert("64",sixtyFourCheck);

    //cores number
    QString mt;
    if(Config::instance().containsOption("mt")){
        mt = Config::instance().getOption("mt");
    }else{
        mt = "4";
    }
    QLineEdit *coresNumberEdit = new QLineEdit(mt);
    layout->addRow(tr("Number of cores"),coresNumberEdit);
    m_lineEditList.insert("mt",coresNumberEdit);

    //"=log src" and "-raw src"
    //need to generate name from netlist name
    QString nameEnding;
    if(Config::instance().containsOption("Fclk")){
        nameEnding.append("_");
        nameEnding.append(Config::instance().getOption("Fclk"));
    }
    if(Config::instance().containsOption("n")){
        nameEnding.append("_");
        nameEnding.append(Config::instance().getOption("n"));
    }
    //"delay" is in parameters, not config
    {
        QStringList params = netlist.parameters().split(" ");
        foreach (QString parameter, params) {
            if(parameter.startsWith("delay")){
                QStringList delay = parameter.split("=");
                nameEnding.append("_delay");
                nameEnding.append(delay.last());
                break;
            }
        }
    }

    QString netlistFileName = netlist.fileName();
    if(netlistFileName.contains("/")){
        //cutting name from directory tree
        netlistFileName = netlistFileName.right(netlistFileName.length()-netlistFileName.lastIndexOf("/")-1);
    }
    QString netlistFileNameScs = netlistFileName; //neccesary later
    //cutting ".scs" extension
    netlistFileName.chop(4);

    //"=log"
    QString logFileName = netlistFileName;
    logFileName.append(nameEnding); //"_fclk_n_delay"
    logFileName.append(".log"); //extension
    QLineEdit *logSrc = new QLineEdit(logFileName);
    layout->addRow(tr("=log"),logSrc);
    m_lineEditList.insert("log",logSrc);

    //-format
    QLineEdit *format = new QLineEdit("nutascii");
    layout->addRow(tr("-format"),format);
    m_lineEditList.insert("format",format);

    //"-raw"
    QString outFileName = netlistFileName;
    outFileName.append(nameEnding); //"_fclk_n_delay"
    outFileName.append(".Sdat"); //extension
    QLineEdit *outSrc = new QLineEdit(outFileName);
    layout->addRow(tr("-raw"),outSrc);
    m_lineEditList.insert("raw",outSrc);

    //"+aps=" e.g. "conservative" <- from netlist::simulationType
    QString apsString;
    {
        QStringList simType = netlist.simulationType().simplified().split(" ");
        foreach (QString parameter, simType) {
            if(parameter.startsWith("errpreset") && parameter.contains("=")){
                QStringList aps = parameter.split("=");
                apsString = aps.last();
                break;
            }
        }
    }
    QLineEdit *aps = new QLineEdit(apsString);
    layout->addRow(tr("+aps"), aps);
    m_lineEditList.insert("aps",aps);

    //+lqtimeout
    QLineEdit *lqTimeOut = new QLineEdit("900");
    layout->addRow(tr("+lqtimeout"),lqTimeOut);
    m_lineEditList.insert("lqtimeout",lqTimeOut);

    //-maxw
    QLineEdit *maxW = new QLineEdit("5");
    layout->addRow(tr("-maxw"),maxW);
    m_lineEditList.insert("maxw",maxW);

    //+lqtimeout
    QLineEdit *maxN = new QLineEdit("5");
    layout->addRow(tr("-maxn"),maxN);
    m_lineEditList.insert("maxn",maxN);

    //+lqtimeout
    QLineEdit *netlistEdit = new QLineEdit(netlistFileNameScs);
    layout->addRow(tr("Netlist"),netlistEdit);
    m_lineEditList.insert("netlist",netlistEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addWidget(ui->buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Command configuration"));
}

ConfigureCommandDialog::~ConfigureCommandDialog()
{
    delete ui;
}

QString ConfigureCommandDialog::getCommand()const{
    QString command = "";
    if(m_checkboxList.value("escchars")->isChecked()){
        command.append("+escchars").append(" ");
    }
    if(m_checkboxList.value("parasitics")->isChecked()){
        command.append("+parasitics").append(" ");
    }
    if(m_checkboxList.value("64")->isChecked()){
        command.append("-64").append(" ");
    }
    command.append("+mt=").append(m_lineEditList.value("mt")->text()).append(" ");
    command.append("=log ").append(m_lineEditList.value("log")->text()).append(" ");
    command.append("-format ").append(m_lineEditList.value("format")->text()).append(" ");
    command.append("-raw ").append(m_lineEditList.value("raw")->text()).append(" ");
    command.append("+aps=").append(m_lineEditList.value("aps")->text()).append(" ");
    command.append("+lqtimeout ").append(m_lineEditList.value("lqtimeout")->text()).append(" ");
    command.append("-maxw ").append(m_lineEditList.value("maxw")->text()).append(" ");
    command.append("-maxn ").append(m_lineEditList.value("maxn")->text()).append(" ");
    command.append(m_lineEditList.value("netlist")->text()); //just program argument, not flag
    return command;
}
