#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "binarytree.h"
#include "listwidget.h"
#include "inputwidget.h"
#include "treeviewwidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private:
     QGraphicsScene* scene;
     QVBoxLayout* main_layout;
     QHBoxLayout* hbox;
     ListWidget* list;
     InputWidget* input;
     TreeViewWidget* view;
signals:

};

#endif // MAINWIDGET_H
