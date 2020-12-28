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
#include <vector>

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

private:
    Ui::StartMenu *ui;
    QGraphicsScene* scene, *chart1_scene, *chart2_scene;
    QLineSeries *series1, *series2;
    QChart *chart1, *chart2;
    QChartView *chartView1, *chartView2;

    Treap<int>* treap;

    std::vector<int> arrayelem;
    std::string info;
    int* array, *curr_array;
    int arraysize, curr_arraysize, del_arraysize = 0,curr_del = 0,curr_del_last = 0, time_array[10000], del_array[10000];
    bool prior, newprior;

    void setArray(std::string str);
    void setChart();
    void setDelChart();
};

#endif // STARTMENU_H
