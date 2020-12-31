#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QMainWindow>
#include <QInputDialog>
#include <QGraphicsScene>

#include "treap.h"
#include "graphicsviewzoom.h"

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
    void on_from_file_triggered();

    void on_from_string_triggered();
    
    void on_add_item_triggered();

    void on_delete_item_triggered();

    void on_horizontalSlider_sliderMoved(int position);

    void on_generate_triggered();

    void on_NLR_triggered();

    void on_LNR_triggered();

    void on_LRN_triggered();

private:
    Ui::MainWindow* ui;
    QGraphicsScene* scene;

    Treap<int> treap;

    QVector<std::pair<Treap<int>*, QString>> list;

    graphicsviewzoom* zoom;
};
#endif // MAINWINDOW_H
