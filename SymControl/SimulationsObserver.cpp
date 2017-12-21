#include "SimulationsObserver.h"

void SimulationsObserver::run(){
    while(true){
        QThread::sleep(3);
        qDebug() << "observer report every 3 sec";
        emit refresh_signal();
    }
}
