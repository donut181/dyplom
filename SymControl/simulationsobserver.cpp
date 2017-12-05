#include "simulationsobserver.h"

SimulationsObserver::SimulationsObserver(const QString &app_home_path):
    m_app_workspace(QDir(app_home_path))
{
    qDebug() << m_app_workspace;
}

void SimulationsObserver::run(){
    int a = 1;
    while(true){
        QThread::sleep(1);
        emit resultReady(QString::number(a));
        ++a;
    }
}
