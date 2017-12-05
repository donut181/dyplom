#include "simulationsobserver.h"

SimulationsObserver::SimulationsObserver(const QString &app_home_path):
    m_app_workspace(QDir(app_home_path))
{
    qDebug() << m_app_workspace;
}

void SimulationsObserver::run(){
    while(true){
        QThread::sleep(1);
        qDebug() << "observer has nothing to do";
        emit resultReady(m_simulatorList);
    }
}
