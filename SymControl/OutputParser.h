#ifndef OUTPUTPARSER_H
#define OUTPUTPARSER_H

#include<QFile>
#include<QStringList>
#include<iostream>
#include<QTextStream>
#include<QDebug>
#include "Config.h"

class OutputParser
{
public:
    OutputParser(QString filename);
    void parse();
    void save();
    void save(QString name);
private:
    QString m_filename;
    std::vector<int> m_values;
    std::vector<double> m_times;
};

#endif // OUTPUTPARSER_H
