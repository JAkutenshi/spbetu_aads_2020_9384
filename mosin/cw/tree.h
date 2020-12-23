#ifndef TREE_H
#define TREE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QString>

class Tree : public QGraphicsItem{
public:
    Tree(int);
//    ~Tree();
    Tree* insert(Tree* , int);
    Tree* get_left();
    Tree* get_right();
    int get_depth(Tree*);
    int get_operation_count(Tree*);
    float average_find_time(Tree*, float = 0);
    float worst_find_time(Tree*, float = 0);

public:
    QRectF boundingRect() const override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

private:
    Tree* insert_root(Tree* , int);
    Tree* rotate_right(Tree*);
    Tree* rotate_left(Tree*);
    int get_size(Tree*);
    void update_size(Tree*);

private:
    int data;
    int size;
    Tree* left;
    Tree* right;
    int op_count;

    qreal radius;

};

#endif // TREE_H
