#ifndef CONFIGURECOMMANDDIALOG_H
#define CONFIGURECOMMANDDIALOG_H

#include <QDialog>
#include "netlist.h"
#include <QString>
#include <Config.h>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>

namespace Ui {
class ConfigureCommandDialog;
}

class ConfigureCommandDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigureCommandDialog(const Netlist& netlist,QWidget *parent = 0);
    ~ConfigureCommandDialog();
    QString getCommand()const;

private:
    Ui::ConfigureCommandDialog *ui;
    QMap<QString,QCheckBox*> m_checkboxList;
    QMap<QString,QLineEdit*> m_lineEditList;
};

#endif // CONFIGURECOMMANDDIALOG_H
