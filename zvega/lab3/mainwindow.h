#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QColor>
#include <QString>
#include "BT.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    BT<char> *Tree;
    QString taskText;
    int h;
    void printLine(BT<char>*&, int);
    void printLineL(BT<char>*&, int, int);
    void printLineR(BT<char>*&, int, int);
    void printTree(BT<char>*&, int);
    void printTreeL(BT<char>*&, int, int);
    void printTreeR(BT<char>*&, int, int);
    bool isList(QString, int&);
    bool isRoot(QString, int&);
    bool isEmptyList(QString, int&);
    bool readTree(QString, BT<char>*&, int&);

    QGraphicsScene *scene;
    QGraphicsScene *sceneTask;
private slots:
    void on_startButtom_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
