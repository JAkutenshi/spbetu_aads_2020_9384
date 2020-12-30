#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    scene = new QGraphicsScene(0,0,0,0);
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    QRegExp rx("[A-Z;a-z;0-9]*");
    QRegExpValidator *validator = new QRegExpValidator(rx,this);
    ui->lineEdit->setValidator(validator);
}

MainWindow::~MainWindow()
{
    destroy(Tree);
    delete ui;
}


void MainWindow::on_startButtom_clicked()
{
    taskTable.clear();
    taskCode.clear();
    taskText.clear();
    taskNumL.clear();

    taskText = ui->lineEdit->text().replace(" ","");
    if(taskText.length() <= 0)
        return;
    Tree = haffman(taskText.toStdString().c_str());
    taskCode = encode(Tree, taskText.toStdString().c_str());
    taskText = ui->lineEdit->text().replace(" ","");
    printTree(Tree, 0);
    printTask();
    scene->setBackgroundBrush(Qt::white);
    scene->clearSelection();
    scene->setSceneRect(scene->itemsBoundingRect());
    haffman22(Tree, (height(Tree, 0))-1);
    decode(Tree, taskCode.toStdString().c_str());
}

void MainWindow::printTask(){
    ui->n21->setText(taskNumL);
    ui->n24->setText(taskTable);
    ui->n25->setText(QString().setNum(taskCode.toStdString().length()));
}

CodeTree* MainWindow::haffman(const Symbol* symbols, int len)
{
    PriorityQueue<CodeTree*>* queue = create_pq<CodeTree*>(len);
    for (int i = 0; i < len; ++i){
        push(queue, symbols[i].weight, make_leaf(symbols[i]));
    }
    while (sizeQ(queue) > 1) {
        CodeTree* ltree = pop(queue);
        CodeTree* rtree = pop(queue);
        int weight = ltree->s.weight + rtree->s.weight;
        CodeTree* node = make_node(weight, ltree, rtree);
        ltree->parent = node;
        rtree->parent = node;
        push(queue, weight, node);
        if(ltree->s.c)
            showHaffman +=  QString(ltree->s.c) + " " +QString().setNum(ltree->s.weight) + ";";
        else{
             showHaffman += "\n";
        }

    }
    CodeTree* result = pop(queue);
    destroy_pq(queue);
    return result;
}

CodeTree* MainWindow::haffman(const char* message) {
    Symbol symbols[UCHAR_MAX];
    for (int i = 0; i < UCHAR_MAX; ++i) {
        symbols[i].c = i + CHAR_MIN;
        symbols[i].weight = 0;
    }
    int size = strlen(message);
    for (int i = 0; i < size; ++i)
        symbols[message[i] - CHAR_MIN].weight++;
    std::sort(symbols, symbols + UCHAR_MAX, symbol_greater);
    int len = 0;
    while (symbols[len].weight > 0 && len < UCHAR_MAX) len++;
    return haffman(symbols, len);
}

char* MainWindow::decode(const CodeTree* tree, const char* code) {
    QString ans;
    ans += taskCode + "\n";
    char* message = new char[MAX_CODE_LEN];
    int index = 0;
    int len = strlen(code);
    const CodeTree* v = tree;
    for (int i = 0; i < len; ++i) {
        if (code[i] == '0'){
            ans += "0";
            v = v->left;
        }
        else{
            ans += "1";
            v = v->right;
        }
        if (is_leaf(v)) {
            ans += " - " + QString(v->s.c) + "\n";
            message[index++] = v->s.c;
            v = tree;
        }
    }
    ui->n31->setText(ans);
    message[index] = '\0';
    return message;
}

char* MainWindow::encode(const CodeTree* tree, const char* message){
    char* code = new char[MAX_CODE_LEN];
    const CodeTree** symbols_map = new const CodeTree * [UCHAR_MAX];
    for (int i = 0; i < UCHAR_MAX; ++i) {
        symbols_map[i] = nullptr;
    }
    fill_symbols_map(tree, symbols_map);
    int len = strlen(message);
    int index = 0;
    char path[UCHAR_MAX];
    std::string check;
    for (int i = 0; i < len; ++i) {
        const CodeTree* node = symbols_map[message[i] - CHAR_MIN];
        int j = 0;
        while (!is_root(node)) {
            if (node->parent->left == node)
                path[j++] = '0';
            else
                path[j++] = '1';
            node = node->parent;
        }
        path[j] = '\0';
        while (j > 0) {
            code[index++] = path[--j];
            if (-1 == check.find(symbols_map[message[i] - CHAR_MIN]->s.c)){
                taskTable += path[j];
            }
        }
        if (-1 == check.find(symbols_map[message[i] - CHAR_MIN]->s.c)) {
            check.push_back(symbols_map[message[i] - CHAR_MIN]->s.c);
            taskTable += " - ";
            taskTable += symbols_map[message[i] - CHAR_MIN]->s.c;
            taskTable += "\n";
        }

    }
    code[index] = 0;
    delete[] symbols_map;
    return code;
}

void MainWindow::printTree(CodeTree* Tree, int index){
    int x = 300*15;
    if(Tree){
        if(index == 0){
            scene = new QGraphicsScene(0,0,x,100*10);
            ui->graphicsView->setScene(scene);
            printTreeL(Tree->left, index+1, x/2);
            printTreeR(Tree->right, index+1, x/2);
            scene->addEllipse(x/2,50*(index+1),25,25,QColor(0,0,0),QColor(255,150,255));
            scene->addText(QString().setNum(Tree->s.weight))->setPos(x/2+5,50*(index+1));
            scene->addText(QString("0"))->setPos(x/2+5-25,50*(index+1)-20);
            scene->addText(QString("1"))->setPos(x/2+5+25,50*(index+1)-20);
        }
    }
}

void MainWindow::printTreeL(CodeTree* Tree, int index, int offset){
    if(Tree){
        int x = offset - 4*pow(2,8-index);
        scene->addLine(x + 12.5,50*(index+1)+12.5,offset+12.5,50*index +12.5,QPen(Qt::black,3));
        printTreeL(Tree->left, index+1, x);
        printTreeR(Tree->right, index+1, x);
        scene->addEllipse(x,50*(index+1),25,25,QColor(0,0,0),QColor(255,150,255));
        if(Tree->left || Tree->right){
            scene->addText(QString().setNum(Tree->s.weight))->setPos(x+5,50*(index+1));
            scene->addText(QString("0"))->setPos(x+5-25,50*(index+1)-20);
            scene->addText(QString("1"))->setPos(x+5+25,50*(index+1)-20);
        }
        else{
            scene->addText(QString(Tree->s.c))->setPos(x+5,50*(index+1));
            scene->addText(QString().setNum(Tree->s.weight))->setPos(x+5,50*(index+1)-25);
            taskNumL += QString(Tree->s.c) + " - " + QString().setNum(Tree->s.weight) + "\n";
        }
    }
}

void MainWindow::printTreeR(CodeTree* Tree, int index, int offset){
    if(Tree){
        int x = offset + 4*pow(2,8-index);
        scene->addLine(x + 12.5,50*(index+1)+12.5,offset+12.5,50*index +12.5,QPen(Qt::black,3));
        printTreeL(Tree->left, index+1, x);
        printTreeR(Tree->right, index+1, x);
        scene->addEllipse(x,50*(index+1),25,25,QColor(0,0,0),QColor(255,150,255));
        if(Tree->left || Tree->right){
            scene->addText(QString("0"))->setPos(x+5-25,50*(index+1)-20);
            scene->addText(QString("1"))->setPos(x+5+25,50*(index+1)-20);
            scene->addText(QString().setNum(Tree->s.weight))->setPos(x+5,50*(index+1));
        }
        else{
            scene->addText(QString(Tree->s.c))->setPos(x+5,50*(index+1));
            scene->addText(QString().setNum(Tree->s.weight))->setPos(x+5,50*(index+1)-25);
            taskNumL += QString(Tree->s.c) + " - " + QString().setNum(Tree->s.weight) + "\n";

        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event){
    if(event){
        int h = ui->centralwidget->height();
        int w = ui->centralwidget->width();
        ui->layout->setGeometry(QRect(0,0,w,h));
    }
}

void MainWindow::on_info_clicked()
{
    QMessageBox::information(this, "Info", "Поддерживается только английский.\n"
                                               "Напишите строку и нажмите ок для получения ответов или нажмите 'random string'.\n"
                                               "В узле если это не лист показывается вес узла.\n"
                                               "В листе показывается символ узла, а над ним его вес(число вхождений символа).\n"
                                               "Если узел не лист показывается слева и справа '0' или '1'.\n"
                                               "Можно сохранить картинку дерева.");
}

void MainWindow::on_save_clicked()
{
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    scene->render(&painter);
    image.save("tree.png");
}

void MainWindow::on_random_clicked()
{
    taskTable.clear();
    taskCode.clear();
    taskText.clear();
    taskNumL.clear();

    for(int i = 0; i < 30; i++)
            taskText.append(char('a' + rand() % ('z' - 'a')));
    ui->lineEdit->setText(taskText);
    if(taskText.length() <= 0)
        return;
    Tree = haffman(taskText.toStdString().c_str());
    taskCode = encode(Tree, taskText.toStdString().c_str());
    taskText = ui->lineEdit->text().replace(" ","");
    printTree(Tree, 0);
    printTask();
    scene->setBackgroundBrush(Qt::white);
    scene->clearSelection();
    scene->setSceneRect(scene->itemsBoundingRect());
    haffman22(Tree, (height(Tree, 0))-1);
    decode(Tree, taskCode.toStdString().c_str());
}

void MainWindow::haffman22(CodeTree *Tree, int index){
    QString ans;
    cout << index << endl;
    for(int i = index; i >= 0; i--){
        QString l = haffmanL(Tree->left, i);
        QString r = haffmanL(Tree->right, i);
        ans += l + " " + r + "\n";

    }
    ans += haffmanR(Tree) + "(" + QString().setNum(Tree->s.weight) + ")";
    ui->n22->setText(ans);

}
QString MainWindow::haffmanL(CodeTree *Tree, int index){
    if(!(Tree->left || Tree->right))
        return QString(Tree->s.c) + "(" + QString().setNum(Tree->s.weight)+ ")"  ;
    if(index == 0)
        return haffmanR(Tree) + "(" + QString().setNum(Tree->s.weight)+ ")";// +
                //haffmanR(Tree->left) + "(" + QString().setNum(Tree->left->s.weight)+ ")";
    return haffmanL(Tree->left, index-1)+haffmanL(Tree->right, index-1);

}
QString MainWindow::haffmanR(CodeTree *Tree){
    if(!(Tree->left || Tree->right))
        return QString(Tree->s.c);
    return haffmanR(Tree->left)+haffmanR(Tree->right);
}

int MainWindow::height(CodeTree* Tree, int index){
    if(Tree->left || Tree->right){
        int l = height(Tree->left, index+1);
        int r = height(Tree->right, index+1);
        if(r > l)
            return r;
        return l;
    }
    return index;
}
