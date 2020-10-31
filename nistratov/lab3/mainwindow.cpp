#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tree.h"
#include "maketree.h"
#include <iostream>
#include <string>
#include <QGraphicsTextItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_draw_clicked()
{
    std::string str = qPrintable(ui->input->text());
    BinaryTree<char> *tr = new BinaryTree<char>();
    maketree *qt = new maketree();
    tr = qt->createTree(str);

    if (ui->checkBox->isChecked())
        qt->calcTree(tr);

    scene->clear();
    treeDrawer(scene, tr, 0, 0, 20);
    std::string output = "";
    qt->printTree(tr, output, 0);
    ui->output->setText(QString::fromStdString(output));
}

void MainWindow::treeDrawer(QGraphicsScene *&scene, BinaryTree<char> *tr, int w, int h, int depth)
{
    if (tr == nullptr)
        return ;
    QString text;
    text = tr->getData();
    QGraphicsTextItem *let = new QGraphicsTextItem;
    let->setPos(w, h);
    let->setPlainText(text);
    scene->addEllipse(w-7, h, 15*5/2, 15*5/2);
    if (tr->left != nullptr)
        scene->addLine(w+15/2, h+15, w-(depth/2)*15+15/2, h+70+15);
    if (tr->right != nullptr)
        scene->addLine(w+15/2, h+15, w+(depth/2)*15+15/2, h+70+15);
    scene->addItem(let);
    treeDrawer(scene, tr->left, w-(depth/2)*15, h+70, depth/2);
    treeDrawer(scene, tr->right, w+(depth/2)*15, h+70, depth/2);
}


