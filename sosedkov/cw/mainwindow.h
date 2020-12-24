#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "treeviewwidget.h"
#include "graphicwidget.h"
#include <QRandomGenerator>
#include <QVector>
#include <QPushButton>
#include <QLineEdit>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QPushButton* gen_button;
    QLineEdit* gen_input;
    GraphicWidget* g;
};
#endif // MAINWINDOW_H
