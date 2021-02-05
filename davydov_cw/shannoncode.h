#ifndef SHANNONCODE_H
#define SHANNONCODE_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <QScatterSeries>
#include <unordered_map>
#include <ctime>
#include <QLineSeries>
#define EMPTY_STRING ""

class ShannonCode
{
public:
    void encodeDecode(std::string text, QtCharts::QScatterSeries *series1,QtCharts::QScatterSeries *series2, std::vector< std::pair <int,double> > &vect,
                std::vector< std::pair <int,double> > &vect2);
private:

    void buildFunc(std::map<char, int> map1, std::string code, int W2);
    std::map<char, std::string> shannon_code;
    std::map<std::string, char> shannon_code1;
    void decode(std::string text);
};

#endif // SHANNONCODE_H
