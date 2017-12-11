#include "simulationsobserver.h"

SimulationsObserver::SimulationsObserver(const QString &app_home_path):
    m_app_workspace(QDir(app_home_path))
{
    qDebug() << m_app_workspace;
}

void SimulationsObserver::run(){
    while(true){
        QThread::sleep(2);
        qDebug() << "observer report every 2 sec";
        m_simulatorList = m_app_workspace.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
        emit resultReady(m_simulatorList);
    }
}
