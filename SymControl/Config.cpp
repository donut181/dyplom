#include "Config.h"

Config::Config()
{
}

void Config::load(){
    QString configFileName = "configuration.cfg";
    std::cout << configFileName.toStdString() << std::endl;
    QFile configFile(configFileName);
    if(configFile.open(QIODevice::ReadWrite | QIODevice::Text)){
        QTextStream file(&configFile);
        if(file.readAll().length() < 1){
            std::cerr << "Config is empty" << std::endl;
        }
        file.seek(0);
        while(!file.atEnd()){
            QString line = file.readLine();

            //for comments
            if(!line.startsWith('#') && !line.isEmpty()){
                QStringList option = line.trimmed().split('=');
                m_config.insert(option.first(),option.last());
            }
        }
        qDebug() << m_config;
    }


}

void Config::save(){

}

bool Config::containsOption(const QString &key)const{
    return m_config.contains(key);
}

QString Config::getOption(const QString &key)const{
    return m_config.value(key);
}
