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
    void calculateResults();
    std::vector<double> spectrumDataFromDFT;

private:
    QString sdatFilename;
    std::vector<int> sampledSignal;
    std::vector<double> sampledTimePoints;
    std::vector<int> harmonicIndexes;
    double THD;
    double SNHR;
    double SFDR;
    double SINAD;
    double ENOB;

    void fourierTransform();
    void normalizeSpectrum();
    void findHarmonics(int N_h);
    void calculateMetrics();
    void saveResultsToFiles();
};




#endif // OUTPUTPARSER_H
