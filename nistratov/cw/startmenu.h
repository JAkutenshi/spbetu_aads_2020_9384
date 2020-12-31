#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QtCharts>
#include "treap.h"
#include <QLineSeries>
#include <QPainter>
#include <QTextStream>
#include <QElapsedTimer>
#include <QIntValidator>
#include <QFileDialog>
#include <string>
#include <sstream>

namespace Ui {
class StartMenu;
}

class StartMenu : public QWidget
{
    Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

    void start();
    void setArrSize(int n);
    void setPrior(bool n);

    void random();
    void ingen(std::string str);
    template<typename T>
    void generate(T* array, size_t s, std::string info, bool prior);

public slots:
    void on_worst_clicked();
    void on_draw_clicked();
    void on_add_clicked();
    void on_deleteb_clicked();
    void on_adddel_clicked();

private:
    Ui::StartMenu *ui;
    QGraphicsScene* scene, *chart1_scene, *chart2_scene, *chart3_scene;
    QLineSeries *series1, *series2;
    QChart *chart1, *chart2, *chart3;
    QChartView *chartView1, *chartView2, *chartView3;

    Treap<int>* treap;

    QElapsedTimer timer;

    std::string info;
    int* array, *curr_array;
    int arraysize, curr_arraysize, del_arraysize = 0,curr_del = 0,curr_del_last = 0;
    double time_array[100000], del_array[100000];
    bool prior, newprior;

    void setArray(std::string str);
    void setChart();
    void setDelChart();
    void setAddDelChart();
};

#endif // STARTMENU_H
