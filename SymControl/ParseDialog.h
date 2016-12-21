#ifndef PARSEDIALOG_H
#define PARSEDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QVBoxLayout>
#include <netlist.h>

namespace Ui {
class ParseDialog;
}

class ParseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParseDialog(QWidget *parent = 0);
    ~ParseDialog();

private:
    Ui::ParseDialog *ui;
    QTabWidget *tabWidget;
    Netlist *m_netlist;
};

#endif // PARSEDIALOG_H
