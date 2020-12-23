#include "treeviewwidget.h"
#include <QtMath>


TreeViewWidget::TreeViewWidget(QWidget *parent) : QWidget(parent) {
    scene = new QGraphicsScene(parent);
    view = new QGraphicsView(parent);
    view->resize(parent->width(), parent->height());
//    scene->setSceneRect(view->rect());
    view->setScene(scene);
    view->setAlignment(Qt::AlignTop);

}

TreeViewWidget::~TreeViewWidget() {
    delete scene;
    delete view;
}

void TreeViewWidget::drawTree(AVL_Tree<int>::AvlNode* tree, int height, int offset_x, int offset_y) {
    scene->addRect(QRect(offset_x,offset_y,40,40));
    QGraphicsTextItem* item = scene->addText(QString::number(tree->data));
    item->setPos(offset_x, offset_y);


    item->boundingRect().adjust(offset_x,offset_y,40,40);


    if(tree->leftChild()) {
        drawTree(tree->left, height-1, offset_x-qPow(height, 2)*8, offset_y+90);
    }
    if(tree->rightChild()) {
        drawTree(tree->right, height-1, offset_x+qPow(height, 2)*8, offset_y+90);
    }

}
