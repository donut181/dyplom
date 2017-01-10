#ifndef OUTPUTPARSER_H
#define OUTPUTPARSER_H

#include<QFile>
#include<QStringList>
#include<iostream>
#include<QTextStream>
#include<QDebug>

#include <complex>
#include <valarray>

#include "Config.h"

class OutputParser
{
public:
    OutputParser(QString filename);
    void parse();
    void cutFrontDummyPoints(unsigned dummy_points);
    void cutEndDummyPoints(unsigned dummy_points);
    void limitValuesNumber(unsigned n);
    void saveValuesToFile(bool printTime=false)const;//saving m_values and maybe m_times
    void saveFftToFile()const;//saving m_values and maybe m_times
    void ffTransform();
    std::vector<double> m_fft;
private:
    QString m_filename;
    std::vector<int> m_values;
    std::vector<double> m_times;

};




#endif // OUTPUTPARSER_H
