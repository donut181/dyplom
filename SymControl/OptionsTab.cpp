#include "OptionsTab.h"

OptionsTab::OptionsTab(QString options, QWidget *parent) : QWidget(parent)
{
    QStringList optionss = options.split(" ");
    QFormLayout *layout = new QFormLayout;
    foreach (QString a, optionss){
        QStringList option = a.split("=");
        QLineEdit *tmp = new QLineEdit(option.last());
        tmp->setObjectName(option.first());
        layout->addRow(option.first(),tmp);
        m_fields_pointers.insert(option.first(),tmp);
    }
    setLayout(layout);
}

QString OptionsTab::getValues(){
    QString parameters;
    QMapIterator<QString,QLineEdit*> i(m_fields_pointers);
    while(i.hasNext()){
        i.next();
        parameters.append(i.key()).append("=").append(i.value()->text());
        parameters.append(" ");
    }
    return parameters;
}
