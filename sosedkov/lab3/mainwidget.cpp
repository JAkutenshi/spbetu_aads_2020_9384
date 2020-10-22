#include "mainwidget.h"
#include <QtMath>
#include "listwidget.h"


MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    this->resize(800,600);

    view = new TreeViewWidget();
    input = new InputWidget();
    list = new ListWidget();
    main_layout = new QVBoxLayout();
    hbox = new QHBoxLayout();

    hbox->addWidget(view,3);
    hbox->addWidget(list,1);

    main_layout->addWidget(input);
    main_layout->addLayout(hbox, Qt::AlignTop);

    this->setLayout(main_layout);

    connect(input, &InputWidget::treeIsValid, view, [=](BinaryTree<char>* tree, int power){
        view->drawTree(tree, power);
        list->drawTreeElements(tree);
    });
}

MainWidget::~MainWidget() {
    delete view;
    delete input;
    delete list;
    delete hbox;
    delete main_layout;
}
