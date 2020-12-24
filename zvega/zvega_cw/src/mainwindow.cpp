#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    destroy(Tree);
    delete ui;
}


void MainWindow::on_startButtom_clicked()
{
    sceneTask = new QGraphicsScene(0,0,ui->Task->width(),100*20);
    sceneCode = new QGraphicsScene(0,0,ui->code->width()*2,ui->code->height());
    ui->Task->setScene(sceneTask);
    ui->code->setScene(sceneCode);
    taskTable.clear();
    taskCode.clear();
    taskText.clear();

    taskText = ui->lineEdit->text().replace(" ","");
    if(taskText.length() <= 0)
        return;
    Tree = haffman(taskText.toStdString().c_str());
    file.open("control.txt",ios_base::ate);
    taskCode = encode(Tree, taskText.toStdString().c_str());
    sceneCode->addText(taskCode,QFont(taskCode.toStdString().c_str(),20));
    taskText = ui->lineEdit->text().replace(" ","");
    printTree(Tree, 0);
    printTask();
    file << "--------------------------------------->\n";
    file.close();
    scene->setBackgroundBrush(Qt::white);
    scene->clearSelection();
    scene->setSceneRect(scene->itemsBoundingRect());
}

void MainWindow::printTask(){
    file << taskText.toStdString() << endl;
    file << "1.1. Для заданного текста определить число вхождений каждого символа." << endl;
    file << "Ответ: \n" << taskNumL.toStdString() << endl;
    file << "1.2. Построить упорядоченное дерево Хаффмена, имеющее минимальную высоту из всех деревьев Хаффмена.\n Надписать узлы дерева (символ(ы), число вхождений)." << endl;
    file << "Ответ: \n" << "Дерево из программы в файле tree.png" << "\n\n";
    file << "1.3. Выписать код Хаффмена для всех символов, входящих в текст." << endl;
    file << "Ответ: \n" << taskTable.toStdString() << endl;
    file << "1.4. Подсчитать длину закодированного полученным кодом текста." << endl;
    file << "Ответ: \n" << taskCode.toStdString().length() << endl;
}

CodeTree* MainWindow::haffman(const Symbol* symbols, int len)
{
    PriorityQueue<CodeTree*>* queue = create_pq<CodeTree*>(len);
    for (int i = 0; i < len; ++i)
        push(queue, symbols[i].weight, make_leaf(symbols[i]));
    while (sizeQ(queue) > 1) {
        CodeTree* ltree = pop(queue);
        CodeTree* rtree = pop(queue);
        int weight = ltree->s.weight + rtree->s.weight;
        CodeTree* node = make_node(weight, ltree, rtree);
        ltree->parent = node;
        rtree->parent = node;
        push(queue, weight, node);
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
    char* message = new char[MAX_CODE_LEN];
    int index = 0;
    int len = strlen(code);
    const CodeTree* v = tree;
    for (int i = 0; i < len; ++i) {
        if (code[i] == '0')
            v = v->left;
        else
            v = v->right;
        if (is_leaf(v)) {
            message[index++] = v->s.c;
            v = tree;
        }
    }
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
    sceneTask->addText(taskTable,QFont(taskTable,20));
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
                                               "Напишите строку и нажмите ок для построения дерева.\n"
                                               "В узле если это не лист показывается вес узла.\n"
                                               "В листе показывается символ узла, а над ним его вес(число вхождений символа).\n"
                                               "Если узел не лист показывается слева и справа '0' или '1'.\n"
                                               "Задания для контроля в файле 'control.txt'.");
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
    sceneTask = new QGraphicsScene(0,0,ui->Task->width(),100*20);
    sceneCode = new QGraphicsScene(0,0,ui->code->width()*2,ui->code->height());
    ui->Task->setScene(sceneTask);
    ui->code->setScene(sceneCode);
    taskTable.clear();
    taskCode.clear();
    taskText.clear();

    for(int i = 0; i < 30; i++)
            taskText.append(char('a' + rand() % ('z' - 'a')));
    ui->lineEdit->setText(taskText);
    if(taskText.length() <= 0)
        return;
    Tree = haffman(taskText.toStdString().c_str());
    file.open("control.txt",ios_base::ate);
    taskCode = encode(Tree, taskText.toStdString().c_str());
    sceneCode->addText(taskCode,QFont(taskCode.toStdString().c_str(),20));
    taskText = ui->lineEdit->text().replace(" ","");
    printTree(Tree, 0);
    printTask();
    file << "--------------------------------------->\n";
    file.close();
    scene->setBackgroundBrush(Qt::white);
    scene->clearSelection();
    scene->setSceneRect(scene->itemsBoundingRect());
}
