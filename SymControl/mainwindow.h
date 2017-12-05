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
#include "simulationsobserver.h"
#include "ui_mainwindow.h"

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
    void on_result_from_sim_observer(const QString &s);

    void on_actionParse_scs_triggered();

    void on_actionParse_output_Sdat_triggered();

private:
    Ui::MainWindow *ui;
    QString m_app_home_path;
    const QString DEFAULT_SCS_SRC;
    void startObservingWorkspace();
    void prepareWorkspace();

};

#endif // MAINWINDOW_H
