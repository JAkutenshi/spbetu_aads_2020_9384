#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "treap.h"
#include <QTextStream>
#include <QElapsedTimer>
#include <QIntValidator>
#include <QFileDialog>
#include <string>
#include <sstream>
#include "startmenu.h"
#include "input.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_change_clicked();
    void on_inputarray_clicked();

private:
    Ui::MainWindow *ui;
    StartMenu* sWindow;
    input* inWindow;
};
#endif // MAINWINDOW_H
