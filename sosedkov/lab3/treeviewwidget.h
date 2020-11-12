#ifndef TREEVIEWWIDGET_H
#define TREEVIEWWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QtMath>
#include "binarytree.h"

class TreeViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TreeViewWidget(QWidget *parent = nullptr);
    ~TreeViewWidget();
    void drawTree(BinaryTree<char>* tree, int power=3, int offset_x=0, int offset_y=0);
private:
    QGraphicsScene* scene;
    QGraphicsView* view;
signals:


};

#endif // TREEVIEWWIDGET_H
