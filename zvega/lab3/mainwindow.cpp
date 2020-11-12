#include "mainwindow.h"
#include "ui_mainwindow.h"




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


void MainWindow::on_startButtom_clicked()
{
    QString text = ui->lineEdit->text().replace(" ", "");
    if(text[0] != '('){
        QMessageBox::warning(this, "Input error", "Start tree '('");
        return;
    }
    int index = 0;
    if(readTree(text, Tree, index) && index == text.size()) {
        h = Tree->height();
        printTree(Tree, 0);
        printLine(Tree, 0);
        ui->textTask->setText(taskText.replace(" ", ""));
    }else{
        QMessageBox::warning(this, "Input error", "Invalid tree");
        return;
    }
    if(Tree) {
        delete Tree;
        Tree = nullptr;
    }
}

bool MainWindow::readTree(QString text, BT<char>*& node, int& index) {
    if(isList(text, index)) {
        if(isRoot(text, index))
            node = new BT<char>(text.toStdString()[index-1]);
        else if(isEmptyList(text, index))
            return true;
        else
            return false;

        if(isEmptyList(text,index))
            return true;

        return readTree(text, node->left, index) &&
               readTree(text, node->right, index) &&
               isEmptyList(text,index);

    }
    else return false;
}

bool MainWindow::isList(QString text, int& index) {
    if(text[index] == '(') {
        index++;
        return true;
    }
    return false;
}

bool MainWindow::isRoot(QString text, int& index) {
    if(index == 0) return false;
    if(text[index].isLetterOrNumber()) {
        index++;
        return true;
    }
    return false;
}

bool MainWindow::isEmptyList(QString text, int& index) {
    if(text[index] == ')') {
        if(index==1) return false;
        index++;
        return true;
    }
    return false;
}

void MainWindow::printTree(BT<char>*& Tree, int index){
    int x = 300*h;
    if(Tree){
        if(index == 0){
            scene = new QGraphicsScene(0,0,300*h,100*h);
            ui->graphicsView->setScene(scene);
            printTreeL(Tree->left, index+1, x/2);
            printTreeR(Tree->right, index+1, x/2);
            scene->addEllipse(x/2,50*(index+1),25,25,QColor(0,0,0),QColor(255,150,255));
            scene->addText(QString(Tree->returnData()))->setPos(x/2+5,50*(index+1));
        }
    }
}

void MainWindow::printTreeL(BT<char>*& Tree, int index, int offset){
    if(Tree){
        int x = offset - h*50/index;
        scene->addLine(x + 12.5,50*(index+1)+12.5,offset+12.5,50*index +12.5,QPen(Qt::black,3));
        printTreeL(Tree->left, index+1, x);
        printTreeR(Tree->right, index+1, x);
        scene->addEllipse(x,50*(index+1),25,25,QColor(0,0,0),QColor(255,150,255));
        scene->addText(QString(Tree->returnData()))->setPos(x+5,50*(index+1));
    }
}

void MainWindow::printTreeR(BT<char>*& Tree, int index, int offset){
    if(Tree){
        int x = offset + h*50/index;
        scene->addLine(x + 12.5,50*(index+1)+12.5,offset+12.5,50*index +12.5,QPen(Qt::black,3));
        printTreeL(Tree->left, index+1, x);
        printTreeR(Tree->right, index+1, x);
        scene->addEllipse(x,50*(index+1),25,25,QColor(0,0,0),QColor(255,150,255));
        scene->addText(QString(Tree->returnData()))->setPos(x+5,50*(index+1));
    }
}

void MainWindow::printLine(BT<char>*& Tree, int index){
    int x = ui->Task->width()-25;
    if(Tree){
        if(index == 0){
            sceneTask = new QGraphicsScene(0,0,ui->Task->width()-2,100*h);
            ui->Task->setScene(sceneTask);
            sceneTask->addEllipse(x/2,25*(index+1),25,25,QColor(0,0,0),QColor(255,150,255));
            sceneTask->addText(QString(Tree->returnData()))->setPos(x/2+5,25*(index+1));
            taskText[0] = Tree->returnData();
            printLineL(Tree->left,index+1,2);
            printLineR(Tree->right,index+1,3);
        }
    }
}
void MainWindow::printLineL(BT<char>*& Tree, int index, int offset){
    int x = ui->Task->width()-25;
    if(Tree){
            sceneTask->addEllipse(x/2,25*offset,25,25,QColor(0,0,0),QColor(255,150,255));
            sceneTask->addText(QString(Tree->returnData()))->setPos(x/2+5,25*offset);
            taskText[offset-1] = Tree->returnData();
            printLineL(Tree->left,index+1,offset*2);
            printLineR(Tree->right,index+1,offset*2+1);

    }
}

void MainWindow::printLineR(BT<char>*& Tree, int index, int offset){
    int x = ui->Task->width()-25;
    if(Tree){
            sceneTask->addEllipse(x/2,25*offset,25,25,QColor(0,0,0),QColor(255,150,255));
            sceneTask->addText(QString(Tree->returnData()))->setPos(x/2+5,25*offset);
            taskText[offset-1] = Tree->returnData();
            printLineL(Tree->left,index+1,offset*2);
            printLineR(Tree->right,index+1,offset*2+1);

    }
}
