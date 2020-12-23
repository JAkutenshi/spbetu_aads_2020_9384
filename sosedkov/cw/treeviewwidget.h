#ifndef TREEVIEWWIDGET_H
#define TREEVIEWWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "AVL_Tree.h"
#include <QGraphicsTextItem>
#include <QPainter>

class TreeViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TreeViewWidget(QWidget *parent = nullptr);
    ~TreeViewWidget();
    void drawTree(AVL_Tree<int>::AvlNode* tree, int height=0, int offset_x=0, int offset_y=0);
private:
    QGraphicsScene* scene;
    QGraphicsView* view;
signals:

};

#endif // TREEVIEWWIDGET_H
