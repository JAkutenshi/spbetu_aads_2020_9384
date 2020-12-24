#include "graphicwidget.h"
#include <QtMath>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include "AVL_Tree.h"
#include <QRandomGenerator>
#include <QVector>
#include <QTime>
#include <QGraphicsTextItem>
#include <QGraphicsProxyWidget>

GraphicWidget::GraphicWidget(QWidget *parent) : QWidget(parent) {

    scene = new QGraphicsScene(parent);
    view = new QGraphicsView(parent);
    view->resize(parent->width(), parent->height());
    view->setScene(scene);
//    view->setAlignment(Qt::AlignTop);
    scene->setSceneRect(view->contentsRect());


}

void GraphicWidget::clear() {
    scene->clear();
}

void GraphicWidget::drawStatistics(int data_size) {
    int insert_width = 420;
    int insert_height = 240;
    int x_max = data_size;
    int y_max = 200;
    int random_insertion_time;
    int sorted_insertion_time;
    int random_remove_time;
    int sorted_remove_time;
    QTime q;
    q.start();
    QPixmap insert_operations_pixmap = createPixmapGraph(insert_width, insert_height, x_max, y_max, 17);
    QPixmap insert_operations_sorted_pixmap = insert_operations_pixmap.copy();
    QPixmap remove_operations_pixmap = createPixmapGraph(insert_width, insert_height, x_max, y_max, 12);
    QPixmap remove_operations_sorted_pixmap = remove_operations_pixmap.copy();
    qDebug() << "create time: " << q.elapsed();








    //RANDOM INSERT STATISTICS
    QPainter p(&insert_operations_pixmap);
    QPen pen(QColor(255,0,0));
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(pen);
    AVL_Tree<int> tree;
    QVector<quint32> data(x_max);
    QRandomGenerator::global()->fillRange(data.data(), data.size());
    QTime t;
    t.start();
    for(int i=0; i<data.size(); i++) {
        tree.insert(data[i]);
        float x = i;
        float y = tree.number_of_operations();
        if(x*insert_width/(x_max) > insert_width || (-y*insert_height/y_max)+insert_height > insert_height) {
            break;
        }
        p.drawEllipse(x*insert_width/(x_max), (-y*insert_height/y_max)+insert_height, 3, 3);
    }

    qDebug() << "Random insert time (ms) " << t.elapsed();
    random_insertion_time = t.elapsed();
    p.end();







    //RANDOM REMOVE STATISTICS
    QPainter random_remove_p(&remove_operations_pixmap);
    random_remove_p.setRenderHint(QPainter::Antialiasing, true);
    random_remove_p.setPen(QColor(255,0,0));
    t.start();
    for(int i=0; i<data.size(); i++) {
        tree.remove(data[i]);
        float x = i;
        float y = tree.number_of_operations();
        if(x*insert_width/(x_max) > insert_width || (-y*insert_height/y_max)+insert_height > insert_height) {
            break;
        }
        random_remove_p.drawEllipse(insert_width-x*insert_width/(x_max), (-y*insert_height/y_max)+insert_height, 3, 3);
    }

    qDebug() << "Random remove time (ms) " << t.elapsed();
    random_remove_time = t.elapsed();
    random_remove_p.end();














    //SORTED INSERT STATISTICS
    std::sort(data.begin(), data.end());
    QPainter p2(&insert_operations_sorted_pixmap);
    QPen pen2(QColor(255,0,0));
    p2.setRenderHint(QPainter::Antialiasing, true);
    p2.setPen(pen2);
    t.start();
    for(int i=0; i<data.size(); i++) {
        tree.insert(data[i]);
        float x = i;
        float y = tree.number_of_operations();
        if(x*insert_width/(x_max) > insert_width || (-y*insert_height/y_max)+insert_height > insert_height) {
            break;
        }
        p2.drawEllipse(x*insert_width/(x_max), (-y*insert_height/y_max)+insert_height, 3, 3);
    }
    qDebug() << "Sorted insert time (ms) " << t.elapsed();
    sorted_insertion_time = t.elapsed();
    p2.end();








    //SORTED REMOVE STATISTICS
    QPainter sorted_remove_p(&remove_operations_sorted_pixmap);
    sorted_remove_p.setRenderHint(QPainter::Antialiasing, true);
    sorted_remove_p.setPen(QColor(255,0,0));
    t.start();
    for(int i=0; i<data.size(); i++) {
        tree.remove(data[i]);
        float x = i;
        float y = tree.number_of_operations();
        if(x*insert_width/(x_max) > insert_width || (-y*insert_height/y_max)+insert_height > insert_height) {
            break;
        }
        sorted_remove_p.drawEllipse(insert_width-x*insert_width/(x_max), (-y*insert_height/y_max)+insert_height, 3, 3);
    }

    qDebug() << "Sorted remove time (ms) " << t.elapsed();
    sorted_remove_time = t.elapsed();
    sorted_remove_p.end();








    insert_operations_pixmap = drawLog(insert_operations_pixmap, insert_width,insert_height, x_max, y_max, 17);
    remove_operations_pixmap = drawLog(remove_operations_pixmap, insert_width,insert_height, x_max, y_max, 14);
    insert_operations_sorted_pixmap = drawLog(insert_operations_sorted_pixmap, insert_width,insert_height, x_max, y_max, 17);
    remove_operations_sorted_pixmap = drawLog(remove_operations_sorted_pixmap, insert_width,insert_height, x_max, y_max, 12);

    scene->addPixmap(insert_operations_pixmap)->setPos(10,60);
    scene->addPixmap(remove_operations_pixmap)->setPos(10,insert_height+190);
    scene->addPixmap(insert_operations_sorted_pixmap)->setPos(50+insert_width,60);
    scene->addPixmap(remove_operations_sorted_pixmap)->setPos(50+insert_width,insert_height+190);












    //INSERT TEXT
    QFont titleFont;
    titleFont.setPixelSize(25);
    titleFont.setBold(true);
    titleFont.setFamily("Calibri");


    QFont textFont;
    textFont.setPixelSize(12);
    textFont.setBold(false);
    textFont.setFamily("Calibri");





    QGraphicsTextItem* text = scene->addText("Insert statistics");
    text->setPos(10,0);
    text->setFont(titleFont);


    text = scene->addText(QString("Random data ") + QString("(Total time: ") + QString::number(random_insertion_time) + QString(" ms)"));
    text->setPos(10,40);
    text->setFont(textFont);


    text = scene->addText(QString("Sorted data ") + QString("(Total time: ") + QString::number(sorted_insertion_time) + QString(" ms)"));
    text->setPos(insert_width+50, 40);
    text->setFont(textFont);


    text = scene->addText(QString("x ∈ [0,") + QString::number(x_max) + QString("]"));
    text->setPos(10,insert_height+70);
    text->setFont(textFont);


    text = scene->addText(QString("y ∈ [0,") + QString::number(y_max) + QString("]"));
    text->setPos(10,insert_height+90);
    text->setFont(textFont);


    QPixmap rect_pix(10,10);
    rect_pix.fill(QColor(0,0,255));
    scene->addPixmap(rect_pix)->setPos(90, insert_height+75);
    rect_pix.fill(QColor(255,0,0));
    scene->addPixmap(rect_pix)->setPos(90, insert_height+95);


    text = scene->addText(QString("17log(x)"));
    text->setPos(100, insert_height+70);
    text->setFont(textFont);


    text = scene->addText(QString("number of operations(random data)"));
    text->setPos(100, insert_height+90);
    text->setFont(textFont);



    text = scene->addText(QString("x ∈ [0,") + QString::number(x_max) + QString("]"));
    text->setPos(insert_width+50,insert_height+70);
    text->setFont(textFont);


    text = scene->addText(QString("y ∈ [0,") + QString::number(y_max) + QString("]"));
    text->setPos(insert_width+50,insert_height+90);
    text->setFont(textFont);

    rect_pix.fill(QColor(0,0,255));
    scene->addPixmap(rect_pix)->setPos(insert_width+50+80, insert_height+75);
    rect_pix.fill(QColor(255,0,0));
    scene->addPixmap(rect_pix)->setPos(insert_width+50+80, insert_height+95);


    text = scene->addText(QString("17log(x)"));
    text->setPos(insert_width+50+90, insert_height+70);
    text->setFont(textFont);


    text = scene->addText(QString("number of operations(sorted data)"));
    text->setPos(insert_width+50+90, insert_height+90);
    text->setFont(textFont);









    //REMOVE TEXT
    text = scene->addText("Remove statistics");
    text->setPos(10,insert_height+130);
    text->setFont(titleFont);


    text = scene->addText(QString("Random data ") + QString("(Total time: ") + QString::number(random_remove_time) + QString(" ms)"));
    text->setPos(10,insert_height+170);
    text->setFont(textFont);


    text = scene->addText(QString("Sorted data ") + QString("(Total time: ") + QString::number(sorted_remove_time) + QString(" ms)"));
    text->setPos(insert_width+50, insert_height+170);
    text->setFont(textFont);


    text = scene->addText(QString("x ∈ [0,") + QString::number(x_max) + QString("]"));
    text->setPos(10, 2*insert_height+170+30);
    text->setFont(textFont);

    text = scene->addText(QString("y ∈ [0,") + QString::number(y_max) + QString("]"));
    text->setPos(10, 2*insert_height+170+30+20);
    text->setFont(textFont);


    rect_pix.fill(QColor(0,0,255));
    scene->addPixmap(rect_pix)->setPos(90, 2*insert_height+170+30+5);
    rect_pix.fill(QColor(255,0,0));
    scene->addPixmap(rect_pix)->setPos(90,  2*insert_height+170+30+20+5);


    text = scene->addText(QString("12log(x)"));
    text->setPos(100, 2*insert_height+170+30);
    text->setFont(textFont);


    text = scene->addText(QString("number of operations(random data)"));
    text->setPos(100, 2*insert_height+170+30+20);
    text->setFont(textFont);




    text = scene->addText(QString("x ∈ [0,") + QString::number(x_max) + QString("]"));
    text->setPos(insert_width+50, 2*insert_height+170+30);
    text->setFont(textFont);

    text = scene->addText(QString("y ∈ [0,") + QString::number(y_max) + QString("]"));
    text->setPos(insert_width+50, 2*insert_height+170+30+20);
    text->setFont(textFont);


    rect_pix.fill(QColor(0,0,255));
    scene->addPixmap(rect_pix)->setPos(insert_width+50+80, 2*insert_height+170+30+5);
    rect_pix.fill(QColor(255,0,0));
    scene->addPixmap(rect_pix)->setPos(insert_width+50+80,  2*insert_height+170+30+20+5);

    text = scene->addText(QString("12log(x)"));
    text->setPos(insert_width+50+80+10, 2*insert_height+170+30);
    text->setFont(textFont);


    text = scene->addText(QString("number of operations(random data)"));
    text->setPos(insert_width+50+80+10, 2*insert_height+170+30+20);
    text->setFont(textFont);




    QFont axisTitleFont;
    axisTitleFont.setPixelSize(10);
    axisTitleFont.setBold(true);
    axisTitleFont.setFamily("Calibri");
    //1
    text = scene->addText(QString("y = number of operations"));
    text->setPos(10,60-5); //y-5
    text->setFont(axisTitleFont);

    text = scene->addText(QString("x = data size"));
    text->setPos(10+insert_width-80, 60-19+insert_height); //x+wid-80; y-19+height
    text->setFont(axisTitleFont);

    //2
    text = scene->addText(QString("y = number of operations"));
    text->setPos(10,insert_height+190-5);
    text->setFont(axisTitleFont);

    text = scene->addText(QString("x = data size"));
    text->setPos(10+insert_width-80,insert_height+190-19+insert_height);
    text->setFont(axisTitleFont);

    //3
    text = scene->addText(QString("y = number of operations"));
    text->setPos(50+insert_width,60-5);
    text->setFont(axisTitleFont);

    text = scene->addText(QString("x = data size"));
    text->setPos(50+insert_width+insert_width-80,60-19+insert_height);
    text->setFont(axisTitleFont);

    //4
    text = scene->addText(QString("y = number of operations"));
    text->setPos(50+insert_width,insert_height+190-5);
    text->setFont(axisTitleFont);

    text = scene->addText(QString("x = data size"));
    text->setPos(50+insert_width+insert_width-80,insert_height+190-19+insert_height);
    text->setFont(axisTitleFont);
}



QPixmap GraphicWidget::drawLog(QPixmap graph,int width, int height, double x_max_value, double y_max_value, double log_coeff) {
//    QPixmap graph(width, height);
    QPainter p(&graph);
    p.setRenderHint(QPainter::Antialiasing,true);

    QPen pen(QColor(0,0,0));
    pen.setWidth(4);
    p.setPen(pen);
    p.drawLine(0, 0, 0, height-1);
    p.drawLine(0, height-1, width-1, height-1);

    pen.setColor(QColor(40,77,255));
    pen.setWidth(3);
    p.setPen(pen);
    for(double i=0; i<x_max_value; i+=1) {
        double x = i;
        double y = log_coeff*log(x);
        p.drawPoint(x*width/(x_max_value), (-y*height/y_max_value)+height);
    }
    return graph;
}





QPixmap GraphicWidget::createPixmapGraph(int width, int height, double x_max_value, double y_max_value, double log_coeff) {
    QPixmap graph(width, height);
    QPainter p(&graph);
    graph.fill(QColor(192,192,192));
    p.setRenderHint(QPainter::Antialiasing,true);




    return graph;
}


























