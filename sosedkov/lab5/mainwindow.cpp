#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    this->setFixedSize(800,600);
    main_widget = new QWidget(this);
    main_widget->resize(800,600);
    main_layout = new QVBoxLayout();
    input_widget = new InputWidget(this);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    tree_view_widget = new TreeViewWidget(this);
    main_layout->addWidget(input_widget);
    main_layout->addWidget(tree_view_widget);
    main_widget->setLayout(main_layout);

    connect(input_widget, &InputWidget::treeChanged, tree_view_widget, &TreeViewWidget::drawTree);
}

MainWindow::~MainWindow() {

}

