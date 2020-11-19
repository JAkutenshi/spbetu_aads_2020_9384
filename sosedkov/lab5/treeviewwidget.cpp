#include "treeviewwidget.h"
#include "QDebug"
TreeViewWidget::TreeViewWidget(QWidget *parent) : QWidget(parent) {
    initUI(parent);
}

void TreeViewWidget::initUI(QWidget* parent) {
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    view->setMinimumSize(parent->width(),550);
    view->setScene(scene);
}

void TreeViewWidget::drawTree(AVL_Tree<int> tree, int offset_x, int offset_y) {
    if(tree.isEmpty()) {
        scene->clear();
//        qDebug() << "CLEAR1";
        return;
    }
    if(tree.getLevel() == 0) {
        scene->clear();
//        qDebug() << "CLEAR2";
    }
    QGraphicsTextItem * item = new QGraphicsTextItem();
    item->setPos(view->width()/2+offset_x*2, offset_y*20);


    scene->addItem(item);


//    qDebug() << "NUMBER" << QString::number(tree.getData());
    item->setPlainText( QString::number(tree.getData()));
//    qDebug() << "POWER" << tree.getHeight();
    int pow = qPow(2, tree.getHeight())*1.5;
//    qDebug() << "POS" << item->pos().x() << item->pos().y();

    if(tree.leftChild()) {
        drawTree(*tree.leftChild(), offset_x-pow, offset_y+1);
    }

    if(tree.rightChild()) {
        drawTree(*tree.rightChild(), offset_x+pow, offset_y+1);
    }
}
