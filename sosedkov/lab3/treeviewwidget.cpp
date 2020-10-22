#include "treeviewwidget.h"
#include <QDebug>
TreeViewWidget::TreeViewWidget(QWidget *parent) : QWidget(parent) {
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    view->setMinimumSize(this->width(), this->height());
    view->setScene(scene);
    view->setAlignment(Qt::AlignTop);
}

TreeViewWidget::~TreeViewWidget() {
    delete view;
    delete scene;
}

void TreeViewWidget::drawTree(BinaryTree<char>* tree, int power, int offset_x, int offset_y) {
    if(offset_y == 0) scene->clear();
    QGraphicsTextItem * io = new QGraphicsTextItem();
    io->setPos(view->width()/2+offset_x,offset_y*20);

    io->setPlainText(QString(tree->getData()));
    scene->addItem(io);

    int pow = qPow(2, power)*1.5;

    if(tree->left) {
        drawTree(tree->left, power-1, offset_x-pow, offset_y+1);
    }

    if(tree->right) {
        drawTree(tree->right, power-1, offset_x+pow, offset_y+1);
    }

}
