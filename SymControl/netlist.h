#ifndef NETLIST_H
#define NETLIST_H

#include <QObject>
#include <QFile>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <iostream>

class Netlist
{
public:
    Netlist(const QString &filename);
    void parse();
    QString parameters();
    QString include();
    QString simulatorOptions();
    QString simulationType();
private:
    QString mparameters;
    QString minclude;
    QString msimulatorOptions;
    QString msimulationType;


    QString m_filename;

};

#endif // NETLIST_H
