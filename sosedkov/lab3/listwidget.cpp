#include "listwidget.h"

ListWidget::ListWidget(QWidget *parent) : QWidget(parent) {
    title = new QLabel("Left-Right-Root order", this);
}

ListWidget::~ListWidget(){
    delete title;
    removeLayout(elements);
}

void ListWidget::drawTreeElements(BinaryTree<char>* tree) {
    if(elements)
        removeLayout(elements);

    elements = new QVBoxLayout;

    draw(tree);
    elements->setAlignment(Qt::AlignTop);
    this->setLayout(elements);
    elements->setContentsMargins(1,20,1,1);
}

void ListWidget::draw(BinaryTree<char>* tree) {
    if(tree->left)
        draw(tree->left);

    if(tree->right)
        draw(tree->right);

    elements->addWidget(new QLabel(QString(tree->getData())));
}

void ListWidget::removeLayout(QVBoxLayout* layout) {
    QLayoutItem * item;
    QWidget * widget;
    while ((item = layout->takeAt(0))) {
        if ((widget = item->widget()) != 0) {widget->hide(); delete widget;}
        else {delete item;}
    }
    delete layout;
    layout = nullptr;
}
