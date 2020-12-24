#include "mainwindow.h"

#include <QApplication>

#include "AVL_Tree.h"
#include "treeviewwidget.h"
#include "graphicwidget.h"
#include <QRandomGenerator>
#include <QVector>
#include <QPushButton>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    GraphicWidget* g = new GraphicWidget(&w);


//    QPushButton* gen_button = new QPushButton("Generate", &w);
//    gen_button->setGeometry(400,740, 100,30);
//    QLineEdit* gen_input = new QLineEdit(&w);
//    gen_input->setPlaceholderText("Data size (300 by deafult)");
//    gen_input->setGeometry(0,740, 400,30);

//    connect(gen_button, &QPushButton::clicked,  [=]() {
//        QString str = gen_input->text();
//        bool ok;
//        int dec = str.toInt(&ok, 10);
//        if(ok && dec > 0) {
//            g->clear();
//            g->drawStatistics(dec);
//        }
//    });


    w.show();
    return a.exec();
}
