#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "inputwidget.h"
#include "treeviewwidget.h"
#include "avl_tree.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QVBoxLayout* main_layout;
    InputWidget* input_widget;
    TreeViewWidget* tree_view_widget;
    QWidget* main_widget;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

};
#endif // MAINWINDOW_H
