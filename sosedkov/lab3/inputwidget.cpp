#include "inputwidget.h"

InputWidget::InputWidget(QWidget *parent) : QWidget(parent) {
    QLabel* rootLeftRightLabel = new QLabel("Root-Left-Right (a(Tree)(Tree))");
    QLabel* leftRootRightLabel = new QLabel("Left-Root-Right ((Tree)a(Tree))");
    QRadioButton* rootLeftRightBtn = new QRadioButton();
    QRadioButton* leftRootRightBtn = new QRadioButton();
    input = new QLineEdit();
    QPushButton* accept = new QPushButton("Accept");

    rootLeftRightBtn->setChecked(true);
    input->setPlaceholderText("Root-Left-Right: ( a (b) (c) )       Left-Root-Right: ( (b) a (c) )");

    main_layout = new QVBoxLayout;
    labels = new QHBoxLayout;
    radio_buttons = new QHBoxLayout;
    input_form = new QHBoxLayout;

    labels->addWidget(rootLeftRightLabel);
    labels->addWidget(leftRootRightLabel);

    labels->itemAt(0)->setAlignment(Qt::AlignCenter);
    labels->itemAt(1)->setAlignment(Qt::AlignCenter);

    radio_buttons->addWidget(rootLeftRightBtn);
    radio_buttons->addWidget(leftRootRightBtn);

    radio_buttons->itemAt(0)->setAlignment(Qt::AlignCenter);
    radio_buttons->itemAt(1)->setAlignment(Qt::AlignCenter);

    input_form->addWidget(input);
    input_form->addWidget(accept);

    main_layout->addLayout(labels);
    main_layout->addLayout(radio_buttons);
    main_layout->addLayout(input_form);
    main_layout->setAlignment(Qt::AlignTop);

    this->setLayout(main_layout);

    connect(accept, &QPushButton::pressed, this, &InputWidget::isValid);
    connect(rootLeftRightBtn, &QRadioButton::clicked,  [=](){
        this->type = RootLeftRight;
    });
    connect(leftRootRightBtn, &QRadioButton::clicked,  [=](){
        this->type  = LeftRootRight;
    });
}

InputWidget::~InputWidget() {
    QLayoutItem * item;
    QWidget * widget;
    while ((item = main_layout->takeAt(0))) {
        if ((widget = item->widget()) != 0) {widget->hide(); delete widget;}
        else {delete item;}
    }
    delete main_layout;
}






void InputWidget::isValid() {
    QString text = input->text();
    text.replace(" ", "");
    int index = 0;
    bool ok = (type == RootLeftRight)?
                readTreeRLR(text, tree, index) :
                readTreeLRR(text, tree, index);

    if(ok && index == text.size()) {
        qDebug() << "Valid tree";
        tree->print();
        qDebug() << tree->height();
        emit treeIsValid(tree, tree->height());
    }
    else qDebug() << "Invalid tree";

    if(tree) {
        delete tree;
        tree = nullptr;
    }
}



//KLP
bool InputWidget::readTreeRLR(QString text, BinaryTree<char>*& node, int& index) {
    if(isList(text, index)) {
        if(isRoot(text, index))
            node = new BinaryTree<char>(text.toStdString()[index-1]);
        else if(isEmptyList(text, index))
            return true;
        else
            return false;

        if(isEmptyList(text,index))
            return true;

        return readTreeRLR(text, node->left, index) &&
               readTreeRLR(text, node->right, index) &&
               isEmptyList(text,index);

    }
    else return false;
}



//LKP
bool InputWidget::readTreeLRR(QString text, BinaryTree<char>*& node, int& index) {
    if(isList(text,index)) {
        if(isEmptyList(text, index)) //EMPTY LIST
            return true;

        node = new BinaryTree<char>();
        if(!readTreeLRR(text, node->left, index)) //ISLIST
            return false;

        if(isRoot(text, index)) // IS ROOT
            node->setData(text.toStdString()[index-1]);

        if(isEmptyList(text, index))
            return true;

        return readTreeLRR(text, node->right, index) && isEmptyList(text,index);

    }
    else if(text[index].isLetterOrNumber())
        return true;

    else return false;
}


bool InputWidget::isList(QString text, int& index) {
    if(text[index] == '(') {
        index++;
        return true;
    }
    return false;
}

bool InputWidget::isRoot(QString text, int& index) {
    if(index == 0) return false;
    if(text[index].isLetterOrNumber()) {
        index++;
        return true;
    }
    return false;
}

bool InputWidget::isEmptyList(QString text, int& index) {
    if(text[index] == ')') {
        if(index==1) return false;
        index++;
        return true;
    }
    return false;
}
