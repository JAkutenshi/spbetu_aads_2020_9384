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
#include "shannoncode.h"
#include <QDebug>
#include <QScatterSeries>
#include <QColor>
#include <cmath>
#include <QLogValueAxis>
#include <QLineEdit>
#include <QIntValidator>
#include <QSpinBox>
#include <QMenuBar>

using namespace QtCharts;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
