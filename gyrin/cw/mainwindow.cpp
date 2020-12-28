#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include "BinaryTree.h"
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Dinamic Huffman code"),
                            tr("Your string"), QLineEdit::Normal,
                            "Example", &ok);
    if (!ok) {
    }
    std::string str = text.toStdString();
    str.c_str();
    DinamicHuffman<QChar> a;
    a.MakeTree(text);
}
