#ifndef TREEVIEWWIDGET_H
#define TREEVIEWWIDGET_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "avl_tree.h"
#include <QGraphicsItem>
#include <QtMath>


class TreeViewWidget : public QWidget
{
    Q_OBJECT

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    void initUI(QWidget*);
public:
    explicit TreeViewWidget(QWidget *parent = nullptr);
    void drawTree(AVL_Tree<int> tree, int offset_x=0, int offset_y=0);
signals:

};

#endif // TREEVIEWWIDGET_H
