#ifndef CONFIG_H
#define CONFIG_H

#include<QFile>
#include<QStringList>
#include<iostream>
#include<QTextStream>
#include<QDebug>

class Config
{
public:
    static Config& instance(){
        static Config instance;
        return instance;
    }
    void load(); //reads configuration.cfg and saves options to m_config
    void save(); //empty for now
    bool containsOption(const QString &key)const;
    QString getOption(const QString &key)const;
private:
    Config();
    QMap<QString,QString> m_config;
};

#endif // CONFIG_H
