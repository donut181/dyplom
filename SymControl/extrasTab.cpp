#include "extrasTab.h"

ExtrasTab::ExtrasTab(QString include,QString simulationType, QWidget *parent) : QWidget(parent),m_sim(simulationType)
{
    QStringList simulationFlags = simulationType.split(" ");
    QFormLayout *layout = new QFormLayout;
    foreach (QString a, simulationFlags) {
        if(a.contains("=")){
            QStringList flag = a.split("=");
            QString second;
            QLineEdit *tmp;

            if(flag.first() == "stop"){
                bool n  = Config::instance().containsOption("n");
                bool d  = Config::instance().containsOption("dummy_point");
                bool f  = Config::instance().containsOption("Fclk");
                bool t  = Config::instance().containsOption("time_offset");
                if(n && d && f && t){
                    double n,dummyPoints,frequency,timeOffset,stop_time;
                    n=Config::instance().getOption("n").toDouble();
                    dummyPoints=Config::instance().getOption("dummy_point").toDouble();
                    frequency=Config::instance().getOption("Fclk").toDouble();
                    timeOffset=Config::instance().getOption("time_offset").toDouble();
                    stop_time = (n+dummyPoints)/frequency + timeOffset;

                    std::cout << tr("Calculated stop time: ").toStdString() << stop_time << std::endl;

                    second = QString::number(stop_time);
                    tmp = new QLineEdit(second);
                }else{
                    tmp = new QLineEdit(flag.last());
                }
            }else{
                tmp = new QLineEdit(flag.last());
            }
            tmp->setObjectName(flag.first());
            layout->addRow(flag.first(),tmp);
            m_fields_pointers.insert(flag.first(),tmp);
        }
    }

    //libs src (include)
    QString edit;
    QString label;
    if(Config::instance().containsOption("include")){
        edit = Config::instance().getOption("include");
        label = tr("include(from cfg):");
    }else{
        edit = include;
        label = tr("include");
    }
    QLineEdit *tmp = new QLineEdit(edit);
    tmp->setObjectName("include");
    layout->addRow(label,tmp);
    m_includeField = tmp;

    //multithread
    QCheckBox *tmp0 = new QCheckBox(tr("multithread=true"));
    tmp0->setChecked(true);
    tmp0->setObjectName("multithread");
    layout->addRow(tmp0);
    m_multithreadOption = tmp0;

    //save D<9:0>
    QHBoxLayout * checkLayout = new QHBoxLayout;
    if(Config::instance().containsOption("dig_out_name")){
        edit = Config::instance().getOption("dig_out_name");
        label = tr("save(from cfg):");
    }else{
        edit = "D";
        label = tr("save");
    }
    QCheckBox *tmp1 = new QCheckBox;
    tmp1->setChecked(true);
    tmp1->setObjectName("saveD");
    checkLayout->addWidget(tmp1);
    m_saveOption=tmp1;

    QLabel *tmp2 = new QLabel;
    tmp2->setText(label);
    checkLayout->addWidget(tmp2);

    QLineEdit *tmp3 = new QLineEdit(edit);
    tmp3->setObjectName("letter");
    checkLayout->addWidget(tmp3);
    m_saveLetterField = tmp3;

    QLabel *tmp4 = new QLabel;
    tmp4->setText("<9:0>");
    checkLayout->addWidget(tmp4);

    layout->addRow(checkLayout);


    setLayout(layout);
}

QString ExtrasTab::getValues(){
    QString parameters;
    parameters = "dcOp dc write=\"spectre.dc\" maxiters=150 maxsteps=10000 annotate=status \n";

    //retriving "tran tran"
    QStringList parameterList = m_sim.split(" ");
    foreach (QString param, parameterList) {
        if(!param.contains("=")){
            //probably appending "tran " and again
            parameters.append(param).append(" ");
        }
    }

    //retriving other options
    QMapIterator<QString,QLineEdit*> i(m_fields_pointers);
    while(i.hasNext()){
        i.next();
        parameters.append(i.key()).append("=").append(i.value()->text());
        parameters.append(" ");
    }
    return parameters;
}

QString ExtrasTab::getIncludeField(){
    return m_includeField->text().remove('"');
}

bool ExtrasTab::isMultithreadOptionChecked(){
    return m_multithreadOption->isChecked();
}

bool ExtrasTab::isSaveOptionChecked(){
    return m_saveOption->isChecked();
}

QString ExtrasTab::getSaveString(){
    QString saveString = "save ";
    QString letter = m_saveLetterField->text().remove('\'').remove('"');
    for(int i=9; i>-1;--i){
        saveString.append(letter).append("\\<\\").append(QString::number(i)).append("\\> ");
    }
    return saveString;
}
