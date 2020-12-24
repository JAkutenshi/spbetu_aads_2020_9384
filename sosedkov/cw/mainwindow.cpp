#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
//    this->setFixedSize(800,700);
    this->setFixedSize(900,790);
    g = new GraphicWidget(this);
    gen_button = new QPushButton("Generate", this);
    gen_button->setGeometry(600,740, 100,30);
    gen_input = new QLineEdit(this);
    gen_input->setPlaceholderText("Data size (300 by deafult)");
    gen_input->setGeometry(200,740, 400,30);

    connect(gen_button, &QPushButton::clicked,  [=]() {
        QString str = gen_input->text();
        bool ok;
        int dec = str.toInt(&ok, 10);
        if(ok && dec > 0) {
            g->clear();
            g->drawStatistics(dec);
        }
    });
}

MainWindow::~MainWindow() {

}

