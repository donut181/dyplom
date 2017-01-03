#include "OutputParser.h"

OutputParser::OutputParser(QString fileName): m_filename(fileName)
{
}

void OutputParser::parse(){
    //getting value to compare
    double digitalThreshold;
    if(Config::instance().containsOption("dig_tresh")){
        digitalThreshold = Config::instance().getOption("dig_tresh").toDouble();
    }else if(Config::instance().containsOption("vsup")){
        digitalThreshold = Config::instance().getOption("vsup").toDouble() / 2.;
    }else{
        std::cout << "No digital threshold value in config, using 0.6" << std::endl;
        digitalThreshold = .6;
    }
    QFile fileName(m_filename);
    if(fileName.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream file(&fileName);
        while(!file.atEnd()){
            QString line = file.readLine();

            //looking for "Plotname: " and contains 'tran'
            if(line.startsWith("Plotname:") && line.contains("tran")){
                //good part of file, now looking for first "Values:" occurance
                while(!file.atEnd()){
                    line = file.readLine();
                    if(line.startsWith("Values")){
                        //now is time to start parsing
                        line = file.readLine();
                        while(!file.atEnd() && line.startsWith(" ")){
                            QString fewLines = line;
                            std::vector<bool> oneValue;
                            while(!file.atEnd()){
                                line = file.readLine();
                                if(line.startsWith(" ")){
                                    //here is new value line, so break while and calculate last value
                                    QString values = fewLines.simplified();
                                    QStringList valuesList= values.split(" ");
                                    //removing number, reading time, removing time
                                    valuesList.removeFirst();
                                    m_times.push_back(valuesList.at(0).toDouble());
                                    valuesList.removeFirst();
                                    foreach (QString value, valuesList) {
                                        double valueInDouble = value.toDouble();
                                        oneValue.push_back( (valueInDouble > digitalThreshold) ? true : false );
                                    }
                                    break;
                                }else{
                                    fewLines.append(line);
                                }
                            }
                            //after break -> need to calculate value from oneValie vector
                            int value = 0;
                            for(int i=0;i<10;++i){
                                if(oneValue.at(9-i)){
                                    value += std::pow(2,i);
                                }
                            }
                            m_values.push_back(value);
                        }
                    }
                }
            }
        }
        fileName.close();
    }else{
        std::cerr << "Failed to load file " << m_filename.toStdString() << std::endl;
    }
}
void OutputParser::save(){
    if(m_filename.isEmpty()){
        std::cerr << "No filename to write to" << std::endl;
    }else{
        save(m_filename);
    }
}

void OutputParser::save(QString name){
    foreach (int value, m_values) {
        std::cout << value << std::endl;
    }
}
