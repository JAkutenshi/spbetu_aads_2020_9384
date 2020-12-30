#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QColor>
#include <QString>
#include <QMessageBox>
#include "priority_queue.h"
#include "code_tree.h"
#include <functional>
#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <string>
#include <QPainter>
#include <QRegExpValidator>
#include <QRegExp>

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
    QString taskText;
    QString taskTable;
    QString taskCode;
    QString taskNumL;
    QString showHaffman;
    QString encodeTree(CodeTree *, int);
    void printTree(CodeTree *, int);
    void printTreeL(CodeTree *, int, int);
    void printTreeR(CodeTree *, int, int);

    void haffman22(CodeTree *, int);
    QString haffmanL(CodeTree *, int);
    QString haffmanR(CodeTree *);

    void printTask();
    void resizeEvent(QResizeEvent *event);

    CodeTree* haffman(const Symbol* symbols, int len);
    CodeTree* haffman(const char* message);
    char* decode(const CodeTree* tree, const char* code);
    char* encode(const CodeTree* tree, const char* message);
    QString n22;

    int height(CodeTree *, int index);

    QGraphicsScene *scene;
private slots:
    void on_startButtom_clicked();

    void on_info_clicked();

    void on_save_clicked();

    void on_random_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
