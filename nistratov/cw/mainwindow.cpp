#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

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

void MainWindow::on_change_clicked()
{
    sWindow= new StartMenu();
    sWindow->show();
    sWindow->setArrSize(ui->arrsize->value());
    sWindow->setPrior(ui->prior->checkState());
    sWindow->random();
}

void MainWindow::on_inputarray_clicked()
{
    inWindow = new input();
    inWindow->setarrsize(ui->arrsize->value());
    inWindow->setPrior(ui->prior->checkState());
    inWindow->show();
}
