#include "Config.h"

Config::Config()
{
}

void Config::load(){
    //config src
    QString configFileName = "configuration.cfg";

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
            if(!line.startsWith('#') && !line.isEmpty() && line.contains("=")){
                //parsing ( simplified() removes multiple spaces, replece() removes left ones)
                QStringList option = line.simplified().replace(" ", "").split('=');

                //parsing complicated values, like Tclk+<number> or 1/Tclk, but only 2 args, cant process sth+sth+sth
                //and ignoring values of type string
                if((option.last().contains("+") || option.last().contains("/") || option.last().contains("*") ) && !option.last().startsWith("'") && !option.last().startsWith("\"")){
                    QChar oper;
                    if(option.last().contains("+"))
                        oper = '+';
                    if(option.last().contains("/"))
                        oper = '/';
                    if(option.last().contains("*"))
                        oper = '*';

                    //std::cout << option.last().toStdString() << std::endl;

                    QStringList complicatedOption = option.last().split(oper);
                    double a,b;
                    a = (m_config.contains(complicatedOption.first()) ? m_config.value(complicatedOption.first()).toDouble() : complicatedOption.first().toDouble());
                    b = (m_config.contains(complicatedOption.last()) ? m_config.value(complicatedOption.last()).toDouble() : complicatedOption.last().toDouble());
                    //std::cout << option.first().toStdString() << " : " << a << " " << b << std::endl;

                    if(oper == '+')
                        option.last() = QString::number(a+b);
                    if(oper == '/')
                        option.last() = QString::number(a/b);
                    if(oper == '*')
                        option.last() = QString::number(a*b);
                }

                if(option.first() == "app_home"){
                    option.last().replace("\"","");
                }
                //save this option
                m_config.insert(option.first(),option.last());
            }
        }
        qDebug() << m_config;
        configFile.close();
    }else{
        std::cerr << "Config file loading failed" << std::endl;
    }


}
void Config::setOption(const QString &key, const QString &value){
    m_config.insert(key,value);
}

void Config::save(){

}

bool Config::containsOption(const QString &key)const{
    return m_config.contains(key);
}

QString Config::getOption(const QString &key)const{
        return m_config.value(key);
}
