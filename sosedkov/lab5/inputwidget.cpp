#include "inputwidget.h"
#include "QDebug"
InputWidget::InputWidget(QWidget *parent) : QWidget(parent) {
    this->initUI(parent);

    connect(insert_btn, &QPushButton::pressed, [=]() {
        bool ok;
        int value = insert_input->text().toInt(&ok, 10);
        if(ok) {
            tree.insert(value);
            qDebug() << "PRINT";
            tree.print();
            emit treeChanged(tree,0,0);
        }
        insert_input->clear();
    });

    connect(remove_btn, &QPushButton::pressed, [=]() {
        bool ok;
        int value = remove_input->text().toInt(&ok, 10);
        if(ok) {
            tree.remove(value);
            tree.print();
            emit treeChanged(tree,0,0);
        }
        remove_input->clear();
    });

    connect(find_btn, &QPushButton::pressed, [=]() {
        qDebug() << find_input->text();
        find_input->clear();
    });
}


void InputWidget::initUI(QWidget *parent) {
    input_form = new QHBoxLayout;

    insert_form = new QHBoxLayout;
    insert_input = new QLineEdit;
    insert_btn = new QPushButton("Insert");
    insert_form->addWidget(insert_input);
    insert_form->addWidget(insert_btn);

    remove_form = new QHBoxLayout;
    remove_input = new QLineEdit;
    remove_btn = new QPushButton("Remove");
    remove_form->addWidget(remove_input);
    remove_form->addWidget(remove_btn);

    find_form = new QHBoxLayout;
    find_input = new QLineEdit;
    find_btn = new QPushButton("Find");
    find_form->addWidget(find_input);
    find_form->addWidget(find_btn);

    input_form->addLayout(insert_form);
    input_form->addLayout(remove_form);
    input_form->addLayout(find_form);

    this->setLayout(input_form);

    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, Qt::gray);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->setFixedSize(parent->width(),50);
}

bool InputWidget::isValid(QLineEdit* line) {
    bool ok;
    int value = line->text().toInt(&ok, 10);
    if(ok) {
        return true;
    }
    return false;
}
