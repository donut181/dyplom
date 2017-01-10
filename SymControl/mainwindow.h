#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <createsimulatordialog.h>
#include <QFileDialog>
#include <QDebug>
#include <ParseDialog.h>
#include <Config.h>
#include "OutputParser.h"
#include "ConfigureCommandDialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void on_actionCreate_triggered();

    void on_actionParse_scs_triggered();

    void on_actionParse_output_Sdat_triggered();

private:
    Ui::MainWindow *ui;

    const QString DEFAULT_SRC;
};

#endif // MAINWINDOW_H
