#include "extrasTab.h"
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>

ExtrasTab::ExtrasTab(QString include,QString sim, QWidget *parent) : QWidget(parent)
{
    QStringList simFlags = sim.split(" ");
    QFormLayout *layout = new QFormLayout;
    foreach (QString a, simFlags) {
        if(a.contains("=")){
            QStringList flag = a.split("=");
            QString second;
            QLineEdit *tmp;
            bool n  = Config::instance().containsOption("n");
            bool d  = Config::instance().containsOption("dummy_point");
            bool f  = Config::instance().containsOption("Fclk");
            bool t  = Config::instance().containsOption("time_offset");
            if(flag.first() == "stop" && n && d && f && t){
                double n,dp,f,to,stop_time;
                n=Config::instance().getOption("n").toDouble();
                dp=Config::instance().getOption("dummy_point").toDouble();
                f=Config::instance().getOption("Fclk").toDouble();
                to=Config::instance().getOption("time_offset").toDouble();
                stop_time = (n+dp)/f + to;
                std::cout << stop_time << std::endl;
                second = QString::number(stop_time);
                tmp = new QLineEdit(second);
            }else{
                tmp = new QLineEdit(flag.last());
            }
            tmp->setObjectName(flag.first());
            layout->addRow(flag.first(),tmp);
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

    //multithread
    QCheckBox *tmp0 = new QCheckBox(tr("multithread=true"));
    tmp0->setChecked(true);
    tmp0->setObjectName("multithread");
    layout->addRow(tmp0);

    //save D<9:0>
    QHBoxLayout * checkLayout = new QHBoxLayout;

    QCheckBox *tmp1 = new QCheckBox;
    tmp1->setChecked(true);
    tmp1->setObjectName("saveD");
    checkLayout->addWidget(tmp1);

    QLabel *tmp2 = new QLabel;
    tmp2->setText(tr("save"));
    checkLayout->addWidget(tmp2);

    QLineEdit *tmp3 = new QLineEdit("D");
    tmp3->setObjectName("letter");
    checkLayout->addWidget(tmp3);

    QLabel *tmp4 = new QLabel;
    tmp4->setText("<9:0>");
    checkLayout->addWidget(tmp4);

    layout->addRow(checkLayout);


    setLayout(layout);
}