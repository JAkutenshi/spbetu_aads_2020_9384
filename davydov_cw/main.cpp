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
#include "mainwindow.h"
#include "huffmantree.h"
#include <QDebug>
#include <QScatterSeries>
#include <QColor>
#include <cmath>
#include <QLogValueAxis>
std::string generate(int size){
    std::string text;
    char c;
    int r;
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        r = rand() % 58;
        c = 'A' + r;
        text.push_back(c);
    }
    return text;
};

using namespace QtCharts;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    std::string text;
    QScatterSeries *series1 = new QScatterSeries();
    QScatterSeries *series2 = new QScatterSeries();
    QScatterSeries *series3 = new QScatterSeries();

    for(int i = 20; i < 500;i++){
        text = generate(i);
        HuffmanTree k;
        k.buildHuffmanTree(text,series1,series2,series3);
    }

    series1->setMarkerSize(7);
    series2->setMarkerSize(7);
    series3->setMarkerSize(7);
    series2->setColor(Qt::red);
    series3->setColor(Qt::green);

    QChart *chart3 = new QChart();
    chart3->legend()->hide();
    chart3->addSeries(series3);
    chart3->setTitle("Complexity decoding");
    QValueAxis *axisX3 = new QValueAxis();
    QValueAxis *axisY3= new QValueAxis();
    axisX3->setTitleText("number of characters in text");
    axisY3->setTitleText("time in milliseconds");
    chart3->addAxis(axisX3, Qt::AlignBottom);
    chart3->addAxis(axisY3, Qt::AlignLeft);
    series3->attachAxis(axisX3);
    series3->attachAxis(axisY3);


    QChart *chart2 = new QChart();
    chart2->legend()->hide();
    chart2->addSeries(series2);
    chart2->setTitle("Complexity making Huffman codes");
    QValueAxis *axisX2 = new QValueAxis();
    QValueAxis *axisY2= new QValueAxis();
    axisX2->setTitleText("number of characters in text");
    axisY2->setTitleText("time in milliseconds");
    chart2->addAxis(axisX2, Qt::AlignBottom);
    chart2->addAxis(axisY2, Qt::AlignLeft);
    series2->attachAxis(axisX2);
    series2->attachAxis(axisY2);

    QChart *chart1 = new QChart();
    chart1->legend()->hide();
    chart1->addSeries(series1);
    chart1->setTitle("Complexity building a Huffman tree");
    QValueAxis *axisX1 = new QValueAxis();
    QValueAxis *axisY1 = new QValueAxis();
    axisX1->setTitleText("number of characters in text");
    axisY1->setTitleText("time in milliseconds");
    chart1->addAxis(axisX1, Qt::AlignBottom);
    chart1->addAxis(axisY1, Qt::AlignLeft);
    series1->attachAxis(axisX1);
    series1->attachAxis(axisY1);

    QWidget *window = new QWidget();
    window->resize(1000,1000);

    QChartView *chartView1 = new QChartView(chart1);
    QChartView *chartView2 = new QChartView(chart2);
    QChartView *chartView3 = new QChartView(chart3);

    QHBoxLayout *Layout = new QHBoxLayout();
    Layout->addWidget(chartView1);
    Layout->addWidget(chartView2);
    Layout->addWidget(chartView3);

    window->setLayout(Layout);
    window->show();
    return a.exec();
}
