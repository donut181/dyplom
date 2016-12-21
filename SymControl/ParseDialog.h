#ifndef PARSEDIALOG_H
#define PARSEDIALOG_H

#include <QDialog>

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
};

#endif // PARSEDIALOG_H
