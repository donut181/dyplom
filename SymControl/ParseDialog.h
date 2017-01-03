#ifndef PARSEDIALOG_H
#define PARSEDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QVBoxLayout>
#include <netlist.h>
#include <QLineEdit>
#include "OptionsTab.h"
#include "extrasTab.h"
#include <QDebug>

namespace Ui {
class ParseDialog;
}

class ParseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParseDialog(QString filename,QWidget *parent = 0);
    ~ParseDialog();
    Netlist getData()const;

private:
    Ui::ParseDialog *ui;
    QTabWidget *tabWidget;
    Netlist *m_netlist;
    OptionsTab* m_optionsTab;
    OptionsTab* m_parametersTab;
    ExtrasTab* m_extrasTab;
};

#endif // PARSEDIALOG_H
