#ifndef SIMULATIONSOBSERVER_H
#define SIMULATIONSOBSERVER_H
#include<QThread>
#include<QDebug>
#include<QDir>
#include<QMainWindow>
#include"ui_mainwindow.h"

class SimulationsObserver : public QThread {
    Q_OBJECT

private:
    void run() override;

signals:
    void refresh_signal();

};

#endif // SIMULATIONSOBSERVER_H
