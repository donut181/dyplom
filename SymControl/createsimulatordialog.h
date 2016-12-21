#ifndef CREATESIMULATORDIALOG_H
#define CREATESIMULATORDIALOG_H

#include <QDialog>

namespace Ui {
class CreateSimulatorDialog;
}

class CreateSimulatorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateSimulatorDialog(QWidget *parent = 0);
    ~CreateSimulatorDialog();

private:
    Ui::CreateSimulatorDialog *ui;
};

#endif // CREATESIMULATORDIALOG_H
