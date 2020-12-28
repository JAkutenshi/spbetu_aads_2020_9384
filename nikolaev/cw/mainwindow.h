#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QMessageBox>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QGraphicsScene>

#include "treap.h"
#include "graphics_view_zoom.h"

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

    void on_Open_triggered();

    void on_Enter_triggered();

    void on_actionEnter_Key_triggered();

    void on_actionErase_Key_triggered();

    void on_actionGanerate_triggered();

    void on_actionImage_triggered();

    void on_actionPreorder_triggered();

    void on_actionInorder_triggered();

    void on_actionPostorder_triggered();

    void on_actionStep_by_step_analysis_triggered(bool checked);

    void on_pushButton_2_clicked();

private:
    Treap<int> treap;

    Ui::MainWindow *ui;

    Graphics_view_zoom* zoom;
    QGraphicsScene* scene;
};
#endif // MAINWINDOW_H
