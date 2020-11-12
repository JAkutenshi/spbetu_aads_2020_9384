#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "tree.h"

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
    void on_draw_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    void treeDrawer(QGraphicsScene *&scene, BinaryTree<char> *tr, int w, int h, int depth);
};
#endif // MAINWINDOW_H
