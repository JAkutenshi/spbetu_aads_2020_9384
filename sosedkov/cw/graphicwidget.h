#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>

class GraphicWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicWidget(QWidget *parent = nullptr);
    void drawStatistics(int data_size=300);
private:
    QPixmap createPixmapGraph(int, int, double, double, double);
    QGraphicsScene* scene;
    QGraphicsView* view;
    QPushButton* gen_button;
    QVBoxLayout* vbox;
    QLineEdit* gen_input;
    int d_size = 300;
signals:

};

#endif // GRAPHICWIDGET_H
