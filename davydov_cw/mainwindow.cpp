#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <iostream>
#include <huffmantree.h>
#include <QScatterSeries>
#include <shannoncode.h>
#include <QActionGroup>
#include <QRadioButton>
#include <QMessageBox>
#include <QCheckBox>
#include <QValueAxis>
#include <cmath>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_2_triggered()
{
    plotResult(QInputDialog::getInt(this, "Ввод", "Введите количетсво символов", 2, 2,126), generateWorstCase);
}

void MainWindow::on_action_triggered()
{
    plotResult(QInputDialog::getInt(this,"Ввод","Введите количество символов", 2, 2), generateAverageCase);
}

void MainWindow::plotResult(int charsAmount, std::string(*generate)(int amount), QString userText){

    //Creating series
    QtCharts::QScatterSeries *seriesHuffmanEncode = new QtCharts::QScatterSeries();
    QtCharts::QScatterSeries *seriesHuffmanDecode = new QtCharts::QScatterSeries();
    QtCharts::QScatterSeries *seriesShannonEncode = new QtCharts::QScatterSeries();
    QtCharts::QScatterSeries *seriesShannonDecode = new QtCharts::QScatterSeries();

    vectHuffEncode.clear();
    vectHuffDecode.clear();
    vectShannonDecode.clear();
    vectShannonEncode.clear();
    numberOfCharacters.clear();

    for(int i = 0;i<userText.size();i++){
        QChar c = userText.at(i);
        qDebug()<<c;
    }

    //filling series
    std::string text;
    srand(time(NULL));
    for(int i = 2; i<charsAmount;i++){
        HuffmanTree huffman;
        ShannonCode shannon;
        if(userText == ""){
            text = generate(i);
        } else {
           for(int j =0; j<i; j++){
               text.push_back(userText[j].toLatin1());
           }
        }

        huffman.buildHuffmanTree(text, seriesHuffmanEncode, seriesHuffmanDecode, vectHuffEncode, vectHuffDecode,numberOfCharacters);
        shannon.encodeDecode(text, seriesShannonEncode, seriesShannonDecode, vectShannonEncode, vectShannonDecode);
        text = "";
    }

    //Creating charts
    QtCharts::QChart *chartHuffmanEncode = getChart(seriesHuffmanEncode, Qt::red,
                                                    "Complexity making Huffman codes (Encoding)",
                                                    "number of characters in text",
                                                    "time in nanoseconds");
    QtCharts::QChart *chartHuffmanDecode = getChart(seriesHuffmanDecode, Qt::red,
                                                    "Complexity Huffman decoding text",
                                                    "number of characters in text",
                                                    "time in nanoseconds");

    QtCharts::QChart *chartShannonEncode = getChart(seriesShannonEncode, Qt::blue,
                                                   "Complexity making Shannon codes (Encoding)",
                                                   "number of characters in text",
                                                   "time in nanoseconds");

    QtCharts::QChart *chartShannonDecode = getChart(seriesShannonDecode, Qt::blue,
                                                    "Complexity Shannon decoding text",
                                                    "number of characters in text",
                                                    "time in nanoseconds");


    QtCharts::QChartView *chartViewHE = new QtCharts::QChartView(chartHuffmanEncode);
    QtCharts::QChartView *chartViewHD = new QtCharts::QChartView(chartHuffmanDecode);
    QtCharts::QChartView *chartViewSE = new QtCharts::QChartView(chartShannonEncode);
    QtCharts::QChartView *chartViewSD = new QtCharts::QChartView(chartShannonDecode);


    QGridLayout *Layout1 = new QGridLayout();
    Layout1->addWidget(chartViewHE,0,0);
    Layout1->addWidget(chartViewHD,0,1);
    Layout1->addWidget(chartViewSE,1,0);
    Layout1->addWidget(chartViewSD,1,1);

   // ui->scrollAreaWidgetContents->setLayout(Layout1);
    QWidget *windowLayot = new QWidget();
    windowLayot->setLayout(Layout1);
    setCentralWidget(windowLayot);
    show();
}

std::string MainWindow::generateAverageCase(int amount){
    int r;
    char c;
    std::string text;
    for(int j = 0; j < amount; j++){
        r = rand() % 95;
        c = ' ' + r;
        text.push_back(c);
    }
    return text;
};

std::string MainWindow::generateWorstCase(int amount){
    char c;
    int r;
    std::vector<char> symbols;
    std::string text;
    for(int i = 0; i <= 126; i++){
        c = 0 + i;
        symbols.push_back(c);
    }

    for(int i = 0; i<amount;i++){
        r = rand() % symbols.size();
        c = symbols[r];
        text.push_back(c);
        symbols.erase(symbols.begin() + r);
    }

    return text;
}

std::string MainWindow::generateBestCase(int amount){
    char c;
    int r;
    std::string text;
    r = rand() % 95;

    for(int i = 0; i<amount; i++){
        c = ' ' + r;
        text.push_back(c);
    }

    return text;
}

QtCharts::QChart * MainWindow::getChart(QtCharts::QScatterSeries *series, QColor color, QString graphName, QString axisXname, QString axisYname){

    QtCharts::QChart *chart = new QtCharts::QChart();
    series->setMarkerSize(5);
    series->setColor(color);
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle(graphName);
    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis();
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisX->setTitleText(axisXname);
    axisY->setTitleText(axisYname);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    return chart;
};

QtCharts::QChart * MainWindow::getChartUnite(QtCharts::QScatterSeries *series, QtCharts::QScatterSeries *series2, QString graphName, QString axisXname, QString axisYname){
    QtCharts::QChart *chart = new QtCharts::QChart();
    series->setMarkerSize(5);
    series->setColor(Qt::red);
    series->setName("Huffman");
    series2->setMarkerSize(6);
    series2->setColor(Qt::blue);
    series2->setName("Shannon");
    chart->addSeries(series);
    chart->addSeries(series2);
    chart->setTitle(graphName);
    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis();
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    QtCharts::QValueAxis *axisY2 = new QtCharts::QValueAxis();
    axisX->setTitleText(axisXname);
    axisY->setTitleText(axisYname);
    axisY2->setTitleText("time in nanoseconds (Shannon)");
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addAxis(axisY2, Qt::AlignRight);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    series2->attachAxis(axisX);
    series2->attachAxis(axisY2);
    return chart;
}

void MainWindow::on_action_3_triggered()
{
    plotResult(QInputDialog::getInt(this, "Ввод", "Введите количество символов", 2, 2), generateBestCase);
}

void MainWindow::on_action_4_triggered()
{
    QString text = QInputDialog::getText(this, "Ввод", "Введите строчку");
    plotResult(text.size(), nullptr,text);
}

void MainWindow::on_action_5_triggered()
{
    //Creating charts
    QtCharts::QScatterSeries *seriesHuffmanEncode = new QtCharts::QScatterSeries();
    QtCharts::QScatterSeries *seriesHuffmanDecode = new QtCharts::QScatterSeries();
    QtCharts::QScatterSeries *seriesShannonEncode = new QtCharts::QScatterSeries();
    QtCharts::QScatterSeries *seriesShannonDecode = new QtCharts::QScatterSeries();

    for(int i = 0;i<vectHuffEncode.size();i++){
        seriesHuffmanEncode->append(vectHuffEncode[i].first,vectHuffEncode[i].second);
        seriesHuffmanDecode->append(vectHuffDecode[i].first,vectHuffDecode[i].second);
        seriesShannonEncode->append(vectShannonEncode[i].first,vectShannonEncode[i].second);
        seriesShannonDecode->append(vectShannonDecode[i].first,vectShannonDecode[i].second);
    }

    QtCharts::QChart *chartHSEncode = getChartUnite(seriesHuffmanEncode, seriesShannonEncode,
                                                    "Complexity Huffman and Shannon encoding",
                                                    "number of characters in text",
                                                    "time in nanoseconds");
    QtCharts::QChart *chartHSDecode = getChartUnite(seriesHuffmanDecode, seriesShannonDecode,
                                                    "Complexity Huffman and Shannon decoding",
                                                    "number of characters in text",
                                                    "time in nanoseconds");

    QtCharts::QChartView *chartViewHSE = new QtCharts::QChartView(chartHSEncode);
    QtCharts::QChartView *chartViewHSD = new QtCharts::QChartView(chartHSDecode);
    QGridLayout *Layout1 = new QGridLayout();
    Layout1->addWidget(chartViewHSE,0,0);
    Layout1->addWidget(chartViewHSD,0,1);

   // ui->scrollAreaWidgetContents->setLayout(Layout1);
    QWidget *windowLayot = new QWidget();
    windowLayot->setLayout(Layout1);
    setCentralWidget(windowLayot);
    show();
}

void MainWindow::on_action_6_triggered()
{
    QtCharts::QScatterSeries *seriesHuffmanEncode = new QtCharts::QScatterSeries();
    QtCharts::QScatterSeries *seriesHuffmanDecode = new QtCharts::QScatterSeries();
    QtCharts::QScatterSeries *seriesShannonEncode = new QtCharts::QScatterSeries();
    QtCharts::QScatterSeries *seriesShannonDecode = new QtCharts::QScatterSeries();

    QtCharts::QLineSeries *HEcomplexity = new QtCharts::QLineSeries();
    QtCharts::QLineSeries *HDcomplexity = new QtCharts::QLineSeries();
    QtCharts::QLineSeries *SEcomplexity = new QtCharts::QLineSeries();
    QtCharts::QLineSeries *SDcomplexity = new QtCharts::QLineSeries();

    for(int i = 0;i<vectHuffEncode.size();i++){
        seriesHuffmanEncode->append(vectHuffEncode[i].first,vectHuffEncode[i].second);
        seriesHuffmanDecode->append(vectHuffDecode[i].first,vectHuffDecode[i].second);
        seriesShannonEncode->append(vectShannonEncode[i].first,vectShannonEncode[i].second);
        seriesShannonDecode->append(vectShannonDecode[i].first,vectShannonDecode[i].second);

        HEcomplexity->append(vectHuffEncode[i].first,log(vectHuffEncode[i].first));
        HDcomplexity->append(vectHuffDecode[i].first,log(vectHuffDecode[i].first));
        SEcomplexity->append(vectShannonEncode[i].first, numberOfCharacters[i]*vectShannonEncode[i].first);
        SDcomplexity->append(vectShannonDecode[i].first,log(vectShannonDecode[i].first));
    }

    QtCharts::QChart *chartHE = getChartWithComlexity(seriesHuffmanEncode,HEcomplexity,"Huffman encoding", "O(logn)",Qt::red);
    QtCharts::QChart *chartHD = getChartWithComlexity(seriesHuffmanDecode,HDcomplexity,"Huffman decoding", "O(logn)",Qt::red);
    QtCharts::QChart *chartSE = getChartWithComlexity(seriesShannonEncode,SEcomplexity,"Shannon encoding", "O(n*W)",Qt::blue);
    QtCharts::QChart *chartSD = getChartWithComlexity(seriesShannonDecode,SDcomplexity,"Shannon decoding", "O(logn)",Qt::blue);

    QtCharts::QChartView *chartViewHE = new QtCharts::QChartView(chartHE);
    QtCharts::QChartView *chartViewHD = new QtCharts::QChartView(chartHD);
    QtCharts::QChartView *chartViewSE = new QtCharts::QChartView(chartSE);
    QtCharts::QChartView *chartViewSD = new QtCharts::QChartView(chartSD);


    QGridLayout *Layout1 = new QGridLayout();
    Layout1->addWidget(chartViewHE,0,0);
    Layout1->addWidget(chartViewHD,0,1);
    Layout1->addWidget(chartViewSE,1,0);
    Layout1->addWidget(chartViewSD,1,1);

   // ui->scrollAreaWidgetContents->setLayout(Layout1);
    QWidget *windowLayot = new QWidget();
    windowLayot->setLayout(Layout1);
    setCentralWidget(windowLayot);
    show();
}



QtCharts::QChart * MainWindow::getChartWithComlexity(QtCharts::QScatterSeries *series, QtCharts::QLineSeries *series2,  QString graphName, QString seriesName, QColor color){
    QtCharts::QChart *chart = new QtCharts::QChart();
    QPen pen = series2->pen();
    pen.setWidth(3);
    pen.setBrush(QBrush(Qt::green));
    series2->setPen(pen);
    series2->setName(seriesName);

    series->setColor(color);
    series->setName(graphName);
    series->setMarkerSize(5);

    chart->addSeries(series);
    chart->addSeries(series2);
    chart->setTitle(graphName);

    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis();
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    QtCharts::QValueAxis *axisY1 = new QtCharts::QValueAxis();

    axisX->setTitleText("number of characters in text");
    axisY->setTitleText("time in nanoseconds");
    axisY1->setTitleText("time of comlexity graph");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addAxis(axisY1, Qt::AlignRight);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    series2->attachAxis(axisX);
    series2->attachAxis(axisY1);
    return chart;
};
