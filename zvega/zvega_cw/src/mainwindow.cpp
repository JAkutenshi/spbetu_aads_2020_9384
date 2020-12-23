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
    destroy(Tree);
    delete ui;
}


void MainWindow::on_startButtom_clicked()
{
    sceneTask = new QGraphicsScene(0,0,ui->Task->width()*1.5,100*20);
    ui->Task->setScene(sceneTask);

    taskText = ui->lineEdit->text().replace(" ","");
    if(taskText.length() <= 0)
        return;
    Tree = haffman(taskText.toStdString().c_str());
    file.open("control.txt",ios_base::app);
    file << "Start string:" << endl;
    file << taskText.toStdString() << endl;
    file << "Table:" << endl;
    taskCode = encode(Tree, taskText.toStdString().c_str());
    file << "Code:" << endl;
    file << taskCode.toStdString() << endl;
    ui->textTask->setText(taskCode);
    file << endl <<"Chose one task from group and save answer. \n№1 binary code, №2 tree(or table) from program, №3 start string\n\n" << endl;
    //file << decode(Tree, code) << endl;
    taskText = ui->lineEdit->text().replace(" ","");
    printTree(Tree, 0);
    printTask();
    file << "--------------------------------------->\n";
    file.close();
}

void MainWindow::printTask(){
    file << endl;
    file << "№1 Encode sentence:" << endl;
    file << this->taskText.toStdString().c_str() << endl;
    file << taskTable.toStdString() << endl;
    file << "№2 Print tree:" << endl;
    file << taskText.toStdString() << "\n\n";
    file << "№3 Decode sentence:" << endl;
    file << taskCode.toStdString() << endl;
    file << taskTable.toStdString() << endl;
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
                file << path[j];
                taskTable += path[j];
            }
        }
        if (-1 == check.find(symbols_map[message[i] - CHAR_MIN]->s.c)) {
            check.push_back(symbols_map[message[i] - CHAR_MIN]->s.c);
            file << " - " << symbols_map[message[i] - CHAR_MIN]->s.c << std::endl;
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
    int x = 300*10;
    if(Tree){
        if(index == 0){
            scene = new QGraphicsScene(0,0,300*10,100*10);
            ui->graphicsView->setScene(scene);
            printTreeL(Tree->left, index+1, x/2);
            printTreeR(Tree->right, index+1, x/2);
            scene->addEllipse(x/2,50*(index+1),25,25,QColor(0,0,0),QColor(255,150,255));
            scene->addText(QString(Tree->s.c))->setPos(x/2+5,50*(index+1));
        }
    }
}

void MainWindow::printTreeL(CodeTree* Tree, int index, int offset){
    if(Tree){
        int x = offset - (15-index)*25/index;
        scene->addLine(x + 12.5,50*(index+1)+12.5,offset+12.5,50*index +12.5,QPen(Qt::black,3));
        printTreeL(Tree->left, index+1, x);
        printTreeR(Tree->right, index+1, x);
        scene->addEllipse(x,50*(index+1),25,25,QColor(0,0,0),QColor(255,150,255));
        scene->addText(QString(Tree->s.c))->setPos(x+5,50*(index+1));
    }
}

void MainWindow::printTreeR(CodeTree* Tree, int index, int offset){
    if(Tree){
        int x = offset + (15-index)*25/index;
        scene->addLine(x + 12.5,50*(index+1)+12.5,offset+12.5,50*index +12.5,QPen(Qt::black,3));
        printTreeL(Tree->left, index+1, x);
        printTreeR(Tree->right, index+1, x);
        scene->addEllipse(x,50*(index+1),25,25,QColor(0,0,0),QColor(255,150,255));
        scene->addText(QString(Tree->s.c))->setPos(x+5,50*(index+1));
    }
}
