#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QRadioButton>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "binarytree.h"

class InputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InputWidget(QWidget *parent = nullptr);
    ~InputWidget();
private:
    QHBoxLayout* labels;
    QHBoxLayout* radio_buttons;
    QHBoxLayout* input_form;
    QVBoxLayout* main_layout;
    QLineEdit* input;

    enum TreeInputType {RootLeftRight, LeftRootRight};
    TreeInputType type = RootLeftRight;
    BinaryTree<char>* tree = nullptr;

    void isValid();
    bool isList(QString, int&);
    bool isRoot(QString, int&);
    bool isEmptyList(QString, int&);
    bool readTreeRLR(QString, BinaryTree<char>*&, int&);
    bool readTreeLRR(QString, BinaryTree<char>*&, int&);

signals:
    void treeIsValid(BinaryTree<char>*, int);

};

#endif // INPUTWIDGET_H
