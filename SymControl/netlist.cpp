#include "netlist.h"

Netlist::Netlist(const QString &filename):
    m_filename(filename)
{

}

void Netlist::parse(){
    QFile file(m_filename);
    std::cout << m_filename.toStdString() << std::endl;

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
       QTextStream in(&file);

       QString line;
       //looking for parameters
       while(!in.atEnd()){
           line = in.readLine();
           if(line.left(7) == "include"){
               std::cout << "No parameters" << std::endl;
               break;
           }
           if(line.left(10) == "parameters"){
               m_parameters = line;
               while(line.right(1) == "\\"){
                   line = in.readLine();
                   m_parameters.append(line);
               }
               m_parameters.remove('\\'); //removing '\' from string
               m_parameters.remove(0,11); //removing "parameters " from string
               m_parameters = m_parameters.simplified();
               break;
           }
       }
       //std::cout << m_parameters.toStdString() << std::endl;

       //looking for include
       while(!in.atEnd()){
           if(line.left(7) == "include"){
               m_include = line;
               m_include.remove(0,8); //removing "include " from string
               m_include.remove('"');
               //std::cout << m_include.toStdString() << std::endl;
               break;
           }
           line = in.readLine();
       }

       //looking for simulatorOptions
       while(!in.atEnd()){
           line = in.readLine();
           if(line.left(16) == "simulatorOptions"){
               m_simulatorOptions = line;
               while(line.right(1) == "\\"){
                   line = in.readLine();
                   m_simulatorOptions.append(line);
               }
               m_simulatorOptions.remove('\\'); //removing '\' from string
               m_simulatorOptions.remove(0,25); //removing "simulatorOptions options" from str
               m_simulatorOptions = m_simulatorOptions.simplified();
               break;
           }
       }
       //std::cout << m_simulatorOptions.toStdString() << std::endl;

       //assuming that simulation type is right in next line
       line = in.readLine();
       m_simulationType = line;
       while(line.right(1)=="\\"){
           line = in.readLine();
           m_simulationType.append(line);
       }
       m_simulationType.remove('\\'); //removing '/' from str
       //cant remove "tran tran " what to do? dont know rules
       m_simulationType = m_simulationType.simplified();

       //std::cout << m_simulationType.toStdString() << std::endl;
        file.close();
    }
}

QString Netlist::include(){
    return m_include;
}
QString Netlist::parameters(){
    return m_parameters;
}
QString Netlist::simulationType(){
    return m_simulationType;
}
QString Netlist::simulatorOptions(){
    return m_simulatorOptions;
}

void Netlist::setParameters(QString parameters){
    m_parameters = parameters;
}
void Netlist::setInclude(QString include){
    m_include = include;
}
void Netlist::setSimulatorOptions(QString options){
    m_simulatorOptions = options;
}
void Netlist::setSimulatorType(QString type){
    m_simulationType = type;
}

void Netlist::rewrite(){
    QString fileName = m_filename;
    QString tmpFileName = m_filename;
    tmpFileName.append("_tmp");

    QFile fileIn(fileName);
    QFile fileOut(tmpFileName);
    if(fileIn.open(QIODevice::ReadOnly | QIODevice::Text) &&
       fileOut.open(QIODevice::Append | QIODevice::Text)){

       QTextStream in(&fileIn);
       QTextStream out(&fileOut);
       QString line;
       //looking for parameters
       while(!in.atEnd()){
           line = in.readLine();
           if(line.left(7) == "include"){
                out << "include " << m_include << "\n";
           }else if(line.left(10) == "parameters"){
               while(line.right(1) == "\\"){
                   line = in.readLine();
               }
               out << "parameters " << m_parameters << "\n"; //this may contain "\n save D\<\9\> D\<\8\>..."
           }else if(line.left(16) == "simulatorOptions"){
               while(line.right(1) == "\\"){
                   line = in.readLine();
               }
               out << "simulatorOptions options " << m_simulatorOptions << "\n";

               //assuming simulationType is in next line
               line = in.readLine();
               while(line.right(1)=="\\"){
                   line = in.readLine();
               }
               out << m_simulationType << "\n"; //e.g. "tran tran " have to be added in ParseDialog::getValues()
           }else{
               out << line << "\n";
           }
       }
    fileIn.close();
    fileOut.close();
    //fileIn.remove();
    //fileOut.rename(tmpFileName,fileName);
    }else{
        std::cerr << "File error during rewriting netlist" << std::endl;
        qDebug() << fileName;
        qDebug() << tmpFileName;
    }
}
