#include "OutputParser.h"

const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> cplx_valarray;

OutputParser::OutputParser(QString fileName): sdatFilename(fileName)
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
    QFile fileName(sdatFilename);
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
            sampledTimePoints.push_back(valuesList.first().toDouble());
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
            sampledSignal.push_back(value);
            //std::cout << m_times.at(m_times.size()-1) << " " << value << std::endl;
        }
        fileName.close();
    }else{
        std::cerr << "Failed to load file " << sdatFilename.toStdString() << std::endl;
    }
}

void OutputParser::saveValuesToFile(bool printTime)const{
    if(sdatFilename.isEmpty()){
        //no file to save
        std::cerr << "No file specified for saving values from output parser." << std::endl;
    }else{
        QString saveFileName = sdatFilename;
        saveFileName.replace(".Sdat",".dat");
        std::cout << "Saving output values to: " << saveFileName.toStdString() << std::endl;
        QFile saveFile(saveFileName);
        if(saveFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream streamOut(&saveFile);
            for(unsigned int i = 0; i<sampledSignal.size(); ++i){
                if(printTime){
                    streamOut << sampledTimePoints.at(i) << "\t";
                }
                streamOut << sampledSignal.at(i) << "\n";
            }
            saveFile.close();
        }
    }
}

void OutputParser::saveFftToFile()const{
    QString fft_filename = sdatFilename;
    fft_filename.replace(".Sdat",".fft");
    std::cout << "Saving output fft values to: " << fft_filename.toStdString() << std::endl;
    QFile fftSaveFile(fft_filename);
    if(fftSaveFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream file(&fftSaveFile);
        foreach (double value, spectrumDataFromDFT) {
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
std::vector<Complex> DFT(const std::vector<Complex>& signal){
    const unsigned signal_length = signal.size();
    const Complex j = Complex(0,1);
    const double pi = std::acos(-1);
    if (signal_length <=1 ) return std::vector<Complex>();
    std::vector<Complex> dft(signal_length,Complex(0,0));

    for(unsigned m = 0; m < signal_length; ++m){
        for(unsigned n = 0; n < signal_length; ++n){
            dft[m] += signal[n] * std::exp(j*pi*Complex(-2.0*n*m/signal_length,0));
        }
    }
    return dft;
}

double num2dB(double val){
    return 20*log10(sqrt(val));
}

//void OutputParser::ffTransform(){
    //fft(...) functions require array of complex values
//    cplx_valarray values(m_complex_values.data(),m_complex_values.size());
//    FFT(values);
//    //need for real values so calculating magnitudes
//    m_complex_values.assign(std::begin(values),std::end(values));
//}

void OutputParser::calculateResults()
{
    fourierTransform();
    normalizeSpectrum();
    findHarmonics(10);
    calculateMetrics();
    saveResultsToFiles();
}

void OutputParser::fourierTransform()
{
    std::vector<Complex> m_complex_values;
    foreach (int value, sampledSignal) {
        m_complex_values.push_back(Complex(value,0));
    }

    std::vector<Complex> transformed = DFT(m_complex_values);

    foreach (Complex value, transformed) {
        spectrumDataFromDFT.push_back(std::abs(value));
    }
}

void OutputParser::normalizeSpectrum()
{
    for(unsigned i=0; i<spectrumDataFromDFT.size(); ++i){
        spectrumDataFromDFT[i] = spectrumDataFromDFT[i]*2.0/static_cast<double>(spectrumDataFromDFT.size());
    }
}

void OutputParser::findHarmonics(int N_h)
{
    int N = spectrumDataFromDFT.size();
    double f_sig = Config::instance().getOption("signalFreq").toDouble();
    double f_s = Config::instance().getOption("Fclk").toDouble();
    double f_b = f_s/static_cast<double>(N);
    int m_sig = static_cast<int>(round(f_sig/f_b));
    harmonicIndexes.push_back(m_sig);

    std::vector<int> indexesCandidates;
    for(int k=2; k<=N_h;++k){
        indexesCandidates.push_back((k*m_sig)%N);
    }
    foreach (int index_candidate, indexesCandidates) {
        if(index_candidate < N/2)
            harmonicIndexes.push_back(index_candidate);
        else
            harmonicIndexes.push_back(N-index_candidate);
    }
}

void OutputParser::calculateMetrics()
{
    int N = spectrumDataFromDFT.size();
    double x2_of_harmonics = 0;
    double x2_of_signal = pow(spectrumDataFromDFT[harmonicIndexes[0]],2.);
    double x2_of_spectrum_without_harmonics = 0;
    double x2_of_spectrum_without_signal = 0;
    double max_of_spectrum_x2_without_harmonics = 0;

    std::vector<double> spectrumDataCopy(spectrumDataFromDFT);

    for(int m=1; m<(N/2)-1; ++m){
        if(m != harmonicIndexes[0])
            x2_of_spectrum_without_signal += pow(spectrumDataCopy[m],2.);
        else
            spectrumDataCopy[m] = 0;
    }
    foreach (int harmonic_index, harmonicIndexes) {
        x2_of_harmonics += pow(spectrumDataCopy[harmonic_index],2.);
        spectrumDataCopy[harmonic_index] = 0;
    }

    for(int m = 1; m< (N/2)-1; ++m){
        double tmp = pow(spectrumDataCopy[m],2.);
        x2_of_spectrum_without_harmonics += tmp;

        if(tmp > max_of_spectrum_x2_without_harmonics)
            max_of_spectrum_x2_without_harmonics = tmp;
    }

    THD = num2dB(x2_of_harmonics/x2_of_signal);
    SNHR = num2dB(x2_of_signal/x2_of_spectrum_without_harmonics);
    SFDR = num2dB(x2_of_signal/max_of_spectrum_x2_without_harmonics);
    SINAD = num2dB(x2_of_signal/x2_of_spectrum_without_signal);
    ENOB = (SINAD - 1.76)/6.02;

}

void OutputParser::saveResultsToFiles()
{
    saveValuesToFile();
    saveFftToFile();

    QString infoFileName = sdatFilename;
    infoFileName.replace(".Sdat",".info");
    std::cout << "Saving metrics values to: " << infoFileName.toStdString() << std::endl;
    QFile infoSaveFile(infoFileName);
    if(infoSaveFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream file(&infoSaveFile);
        file << "THD    = " << THD << " dB\n";
        file << "SINAD  = " << SINAD << " dB\n";
        file << "SNHR   = " << SNHR << " dB\n";
        file << "SFDR   = " << SFDR << " dB\n";
        file << "ENOB   = " << ENOB << "\n";
        infoSaveFile.close();
    }else{
        std::cerr << "Error opening a file to save metrics" << std::endl;
    }
}

void OutputParser::cutFrontDummyPoints(unsigned dummy_points){
    if(dummy_points < sampledSignal.size()){
        sampledSignal.erase(sampledSignal.begin(),sampledSignal.begin()+dummy_points);
        sampledTimePoints.erase(sampledTimePoints.begin(),sampledTimePoints.begin()+dummy_points);
    }else{
        std::cout << "Deleting more points than vector contains is impossible" << std::endl;
    }
}

void OutputParser::cutEndDummyPoints(unsigned dummy_points){
    if(dummy_points < sampledSignal.size()){
        sampledSignal.erase(sampledSignal.end()-dummy_points,sampledSignal.end());
        sampledTimePoints.erase(sampledTimePoints.end()-dummy_points,sampledTimePoints.end());
    }else{
        std::cout << "Deleting more points than vector contains is impossible" << std::endl;
    }
}

void OutputParser::limitValuesNumber(unsigned n){
    if(n<sampledSignal.size()){
        cutFrontDummyPoints(sampledSignal.size()-n);
    }else{
        std::cout << "Deleting more points than vector contains is impossible" << std::endl;
    }
}
