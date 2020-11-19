#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include "avl_tree.h"

class InputWidget : public QWidget
{
    Q_OBJECT

private:
    void initUI(QWidget*);
    bool isValid(QLineEdit*);
    QHBoxLayout* input_form;
    QHBoxLayout* insert_form;
    QHBoxLayout* remove_form;
    QHBoxLayout* find_form;
    QLineEdit* insert_input;
    QLineEdit* remove_input;
    QLineEdit* find_input;
    QPushButton* insert_btn;
    QPushButton* remove_btn;
    QPushButton* find_btn;
    AVL_Tree<int> tree;
public:
    explicit InputWidget(QWidget *parent = nullptr);

signals:
    void treeChanged(AVL_Tree<int>,int,int);
};

#endif // INPUTWIDGET_H
