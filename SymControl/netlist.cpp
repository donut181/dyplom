#include "netlist.h"

Netlist::Netlist(const QString &filename):
    m_filename(filename)
{

}

void Netlist::parse(){
    QFile file(m_filename);

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
               mparameters = line;
               while(line.right(1) == "\\"){
                   line = in.readLine();
                   mparameters.append(line);
               }
               mparameters.remove('\\'); //removing '\' from string
               mparameters.remove(0,11); //removing "parameters " from string
               mparameters = mparameters.simplified();
               break;
           }
       }
       std::cout << mparameters.toStdString() << std::endl;

       //looking for include
       while(!in.atEnd()){
           if(line.left(7) == "include"){
               minclude = line;
               minclude.remove(0,8); //removing "include " from string
               minclude.remove('"');
               std::cout << minclude.toStdString() << std::endl;
               break;
           }
           line = in.readLine();
       }

       //looking for simulatorOptions
       while(!in.atEnd()){
           line = in.readLine();
           if(line.left(16) == "simulatorOptions"){
               msimulatorOptions = line;
               while(line.right(1) == "\\"){
                   line = in.readLine();
                   msimulatorOptions.append(line);
               }
               msimulatorOptions.remove('\\'); //removing '\' from string
               msimulatorOptions.remove(0,25); //removing "simulatorOptions options" from str
               msimulatorOptions = msimulatorOptions.simplified();
               break;
           }
       }
       std::cout << msimulatorOptions.toStdString() << std::endl;

       //assuming that simulation type is right in next line
       line = in.readLine();
       msimulationType = line;
       while(line.right(1)=="\\"){
           line = in.readLine();
           msimulationType.append(line);
       }
       msimulationType.remove('\\'); //removine '/' from str
       //cant remove "tran tran " what to do? dont know rules
       msimulationType = msimulationType.simplified();

       std::cout << msimulationType.toStdString() << std::endl;

    }
}

QString Netlist::include(){
    return minclude;
}
QString Netlist::parameters(){
    return mparameters;
}
QString Netlist::simulationType(){
    return msimulationType;
}
QString Netlist::simulatorOptions(){
    return msimulatorOptions;
}
