#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QLabel>
#include <QObject>
#include <QLineEdit>
#include <QTableView>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <map>
#include <queue>
#include <unordered_map>
#include <chrono>
#include <QDebug>
#include <QScatterSeries>

#define EMPTY_STRING ""

class HuffmanTree
{

private:

    QtCharts::QChartView *chartView;
    struct Node{
            char ch;
            char character;
            int frequency;
            Node *left, *right;
        };

        Node* root = nullptr;
        std::map<char, std::string> huffmanCode;
        bool isLeaf(Node* root);
        Node* getNode(char ch, int freq, Node* left, Node* right);
        void encode(Node* root, std::string str = EMPTY_STRING);

        struct comp{
            bool operator()(Node* l, Node* r){
                return l->frequency > r->frequency;
            }
        };

public:
    void buildHuffmanTree(std::string text, QtCharts::QScatterSeries *series1, QtCharts::QScatterSeries *series2, std::vector< std::pair <int,double> > &vect,
                          std::vector< std::pair <int,double> > &vect2, std::vector<int> &unique);
    void decode(Node* root, int &index, std::string str);
};



#endif // HUFFMANTREE_H
