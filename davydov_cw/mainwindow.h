#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <huffmantree.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

    void on_action_6_triggered();

private:

    std::vector< std::pair <int,double> > vectHuffEncode;
    std::vector< std::pair <int,double> > vectHuffDecode;
    std::vector< std::pair <int,double> > vectShannonEncode;
    std::vector< std::pair <int,double> > vectShannonDecode;
    std::vector<int> numberOfCharacters;

    static std::string generateAverageCase(int amount);
    static std::string generateWorstCase(int amount);
    static std::string generateBestCase(int amount);
    static std::string generateManuallyCase(int amount);
    QtCharts::QChart * getChart(QtCharts::QScatterSeries *series, QColor color, QString graphName, QString axisXname, QString axisYname);
    QtCharts::QChart * getChartUnite(QtCharts::QScatterSeries *series, QtCharts::QScatterSeries *series2, QString graphName, QString axisXname, QString axisYname);
    QtCharts::QChart * getChartWithComlexity(QtCharts::QScatterSeries *series, QtCharts::QLineSeries *series2,  QString graphName, QString seriesName, QColor color);
    void plotResult(int charsAmount, std::string(*generate)(int), QString userText = "");
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
