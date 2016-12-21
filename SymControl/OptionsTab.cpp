#include "OptionsTab.h"
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>

OptionsTab::OptionsTab(QString options, QWidget *parent) : QWidget(parent)
{
    QStringList optionss = options.split(" ");
    QFormLayout *layout = new QFormLayout;
    foreach (QString a, optionss) {
        QStringList option = a.split("=");
        QLineEdit *tmp = new QLineEdit(option.last());
        tmp->setObjectName(option.first());
        layout->addRow(option.first(),tmp);
    }
    setLayout(layout);
}
