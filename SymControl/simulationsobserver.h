#ifndef SIMULATIONSOBSERVER_H
#define SIMULATIONSOBSERVER_H
#include<QThread>
#include<QDebug>
#include<QDir>
#include<QMainWindow>
#include"ui_mainwindow.h"

class SimulationsObserver : public QThread {
    Q_OBJECT

public:
    SimulationsObserver(const QString &app_home_path);

private:
    QDir m_app_workspace;
    void run() override;
    void listProcessess() const;
signals:
    void resultReady(const QString &result);

};

#endif // SIMULATIONSOBSERVER_H
