#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QLabel>
#include "binarytree.h"
#include <QVBoxLayout>
class ListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ListWidget(QWidget *parent = nullptr);
    ~ListWidget();
    void drawTreeElements(BinaryTree<char>*);
private:
    void removeLayout(QVBoxLayout*);
    void draw(BinaryTree<char>*);
    QLabel* title;
    QVBoxLayout* elements = nullptr;
signals:

};

#endif // LISTWIDGET_H
