#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QColor>
#include <QString>
#include "priority_queue.h"
#include "code_tree.h"
#include <functional>
#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    CodeTree *Tree;
    CodeTree *TreeWithoutSpace;
    QString taskText;
    QString taskTable;
    QString taskCode;
    ofstream file;
    void printLine(CodeTree *, int);
    void printLineL(CodeTree *, int, int);
    void printLineR(CodeTree *, int, int);
    void printTree(CodeTree *, int);
    void printTreeL(CodeTree *, int, int);
    void printTreeR(CodeTree *, int, int);
    void printTask();

    CodeTree* haffman(const Symbol* symbols, int len);
    CodeTree* haffman(const char* message);
    char* decode(const CodeTree* tree, const char* code);
    char* encode(const CodeTree* tree, const char* message);




    QGraphicsScene *scene;
    QGraphicsScene *sceneTask;
private slots:
    void on_startButtom_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
