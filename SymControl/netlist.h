#ifndef NETLIST_H
#define NETLIST_H

#include <QObject>
#include <QFile>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <iostream>
#include <QDebug>

class Netlist
{
public:
    Netlist(const QString &filename);
    void parse();
    void rewrite(const QString newFileName);

    QString parameters()const;
    QString include()const;
    QString simulatorOptions()const;
    QString simulationType()const;
    QString fileName()const;
    void setParameters(QString parameters);
    void setInclude(QString include);
    void setSimulatorOptions(QString options);
    void setSimulatorType(QString type);
private:
    QString m_parameters;
    QString m_include;
    QString m_simulatorOptions;
    QString m_simulationType;

    QString m_filename;

};

#endif // NETLIST_H
