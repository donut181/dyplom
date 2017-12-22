#include "OutputParser.h"

const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> cplx_valarray;

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

        QString line;
        bool tranFound = false;
        while(!file.atEnd()){
            line = file.readLine();

            //looking for "Plotname: " and contains 'tran'
            if(line.startsWith("Plotname:") && line.contains("tran")){
                tranFound = true;
            }
            if(tranFound && line.startsWith("Values:")){
                //now is time to start parsing
                break;
            }
        }

        //vars declaration
        std::vector<QString> fewLinesValues;

        while(!file.atEnd()){
            line = file.readLine();
            if(line.startsWith(" ")){
                //starting new value
                fewLinesValues.push_back(line);
            }else{
                //adding to prev value
                fewLinesValues.at(fewLinesValues.size()-1).append(line);
            }
        }

        //all values in fewLinesValues
        foreach (QString line, fewLinesValues) {
            QString values = line.simplified();
            QStringList valuesList= values.split(" ");
            std::vector<bool> oneValue;

            //removing number, reading time, removing time
            valuesList.removeFirst();
            m_times.push_back(valuesList.first().toDouble());
            valuesList.removeFirst();
            foreach (QString value, valuesList) {
                double valueInDouble = value.toDouble();
                oneValue.push_back( (valueInDouble > digitalThreshold) ? true : false );
            }

            //calculating value from vector<bool> (D<9>D<8>D<7>...) => (2^9, 2^8, 2^7 ...)
            int value = 0;
            for(unsigned int i=0; i<oneValue.size(); ++i){
                if(oneValue.at(oneValue.size()-1-i)){
                    value += std::pow(2,i);
                }
            }
            m_values.push_back(value);
            //std::cout << m_times.at(m_times.size()-1) << " " << value << std::endl;
        }
        fileName.close();
    }else{
        std::cerr << "Failed to load file " << m_filename.toStdString() << std::endl;
    }
}

void OutputParser::saveValuesToFile(bool printTime)const{
    if(m_filename.isEmpty()){
        //no file to save
        std::cerr << "No file specified for saving values from output parser." << std::endl;
    }else{
        QString saveFileName = m_filename;
        saveFileName.replace(".Sdat",".dat");
        std::cout << "Saving output values to: " << saveFileName.toStdString() << std::endl;
        QFile saveFile(saveFileName);
        if(saveFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream streamOut(&saveFile);
            for(unsigned int i = 0; i<m_values.size(); ++i){
                if(printTime){
                    streamOut << m_times.at(i) << "\t";
                }
                streamOut << m_values.at(i) << "\n";
            }
            saveFile.close();
        }
    }
}

void OutputParser::saveFftToFile()const{
    QString fft_filename = m_filename;
    fft_filename.replace(".Sdat",".fft");
    std::cout << "Saving output fft values to: " << fft_filename.toStdString() << std::endl;
    QFile fftSaveFile(fft_filename);
    if(fftSaveFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream file(&fftSaveFile);
        foreach (double value, m_fft) {
            file << value << "\n";
        }
        fftSaveFile.close();
    }else{
        std::cerr << "Error opening a file to save fft values" << std::endl;
    }
}

// Cooley–Tukey FFT (in-place, divide-and-conquer)
// Higher memory requirements and redundancy although more intuitive
void FFT(cplx_valarray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;

    // divide
    cplx_valarray even = x[std::slice(0, N/2, 2)];
    cplx_valarray  odd = x[std::slice(1, N/2, 2)];

    // conquer
    FFT(even);
    FFT(odd);

    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}

void OutputParser::ffTransform(){
    //fft(...) functions require array of complex values
    std::vector<Complex> m_complex_values;
    foreach (int value, m_values) {
        m_complex_values.push_back(Complex(value,0));
    }
    cplx_valarray values(m_complex_values.data(),m_complex_values.size());
    FFT(values);
    //need for real values so calculating magnitudes
    m_complex_values.assign(std::begin(values),std::end(values));
    foreach (Complex value, m_complex_values) {
        m_fft.push_back(std::abs(value));
    }
}

void OutputParser::cutFrontDummyPoints(unsigned dummy_points){
    if(dummy_points < m_values.size()){
        m_values.erase(m_values.begin(),m_values.begin()+dummy_points);
        m_times.erase(m_times.begin(),m_times.begin()+dummy_points);
    }else{
        std::cout << "Deleting more points than vector contains is impossible" << std::endl;
    }
}

void OutputParser::cutEndDummyPoints(unsigned dummy_points){
    if(dummy_points < m_values.size()){
        m_values.erase(m_values.end()-dummy_points,m_values.end());
        m_times.erase(m_times.end()-dummy_points,m_times.end());
    }else{
        std::cout << "Deleting more points than vector contains is impossible" << std::endl;
    }
}

void OutputParser::limitValuesNumber(unsigned n){
    if(n<m_values.size()){
        cutFrontDummyPoints(m_values.size()-n);
    }else{
        std::cout << "Deleting more points than vector contains is impossible" << std::endl;
    }
}
