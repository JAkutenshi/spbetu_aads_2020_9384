#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "static_encode.h"

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

QString MainWindow::VectorToString(vector<char> code){
    QString str;
    for (size_t i = 0; i < code.size(); i++){
        str += code[i];
    }
    return str;
}

QString MainWindow::generateAverageCase(int amount){
    int r;
    char c;
    QString text;
    for(int j = 0; j < amount; j++){
        r = rand() % 95;
        c = ' ' + r;
        text.push_back(c);
    }
    return text;
};

QString MainWindow::generateWorstCase(int amount){
    QString text;

    for(int i = 0; i<amount;i++){
        text += possibleCharacters[i];
    }

    return text;
}

QString MainWindow::generateBestCase(int amount){
    char c;
    int r;
    QString text;
    r = rand() % 95;

    for(int i = 0; i<amount; i++){
        c = ' ' + r;
        text.push_back(c);
    }

    return text;
}

CodeTree* MainWindow::Adaptive_MakeTree(const char* message) {
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

    }
    CodeTree* result = pop(queue);
    destroy_pq(queue);
    return result;
}

char* MainWindow::Adaptive_decode(const CodeTree* tree, vector<char> code) {
    QString ans;
    char* message = new char[MAX_CODE_LEN];
    int index = 0;
    int len = code.size();
    const CodeTree* v = tree;
    for (int i = 0; i < len; ++i) {
        if (code[i] == '0'){
            v = v->left;
        }
        else{
            v = v->right;
        }
        if (is_leaf(v)) {
            message[index++] = v->s.c;
            v = tree;
        }
    }
    //ui->n31->setText(ans);
    message[index] = '\0';
    return message;
}

vector<char> MainWindow::Adaptive_encode(const CodeTree* tree, const char* message){
    vector<char> code;
    const CodeTree** symbols_map = new const CodeTree * [UCHAR_MAX];
    for (int i = 0; i < UCHAR_MAX; ++i) {
        symbols_map[i] = nullptr;
    }
    fill_symbols_map(tree, symbols_map);
    int len = strlen(message);
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
            while (j > 0){
                code.push_back(path[--j]);
            }
        }
    delete[] symbols_map;
    return code;
}

vector<char> Static_encode(Coder<char>::CodedValue code[], QString text, int amount){
    vector<char> code_string;
    for (int i = 0; i < text.size(); i++){
        for (int j = 0; j < amount; j++){
            if (text[i] == code[j].letter){
                for (size_t k = 0; k < code[j].code.size(); k++){
                    if (code[j].code[k] == true){
                        code_string.push_back('1');
                    }
                    if (code[j].code[k] == false){
                        code_string.push_back('0');
                    }
                }
         //       code_string += ' ';
            }
        }
    }
    return code_string;
}



QString Static_decode(Coder<char>* tree, vector<char> code){
    QString decode_string;
    int index = 0;
    const Coder<char>* v = tree;
    for (size_t i = 0; i < code.size(); i++){
        if (code[i] == '0'){
            v = v->zero;
        }
        else{
            v = v->one;
        }
        if (v->one == nullptr && v->zero == nullptr) {
            decode_string[index++] = v->root;
            v = tree;
        }
    }
    return decode_string;
}


QString MainWindow::GetRandomString(int randomStringLength)
{
   //const int randomStringLength = 12; // assuming you want random strings of 12 characters

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}

double MainWindow::StaticEncode_time(QString text){
    int count = 0;
    int index_1 = 0;
    Coder<char> Stree;
    List<Coder<char>*> ptr;
    int amount = Stree.CountOfLetters(text.toStdString());
    Coder<char>::priority* prior = new Coder<char>:: priority[amount];
    Stree.MakePriority(prior, text.toStdString(), amount);
    Stree.MakeNodes(prior, amount, ptr, count);

    auto start = std::chrono::steady_clock::now();

    Stree.Huffman(ptr, count);
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    return std::chrono::duration <double, std::nano> (diff).count();
}

double MainWindow::AdaptiveEncode_time(QString text){
    auto start = std::chrono::steady_clock::now();
    Tree = Adaptive_MakeTree(text.toStdString().c_str());
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    return std::chrono::duration <double, std::nano> (diff).count();
}

double MainWindow::AdaptiveDecode_time(QString text){
    Tree = Adaptive_MakeTree(text.toStdString().c_str());
    vector<char> code = Adaptive_encode(Tree, text.toStdString().c_str());
    auto start = std::chrono::steady_clock::now();
    QString Adaptive_decodee = Adaptive_decode(Tree, code);
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    return std::chrono::duration <double, std::nano> (diff).count();
}


double MainWindow::StaticDecode_time(QString text){
    int count = 0;
    int index_1 = 0;
    Coder<char> Stree;
    List<Coder<char>*> ptr;
    int amount = Stree.CountOfLetters(text.toStdString());
    Coder<char>::priority* prior = new Coder<char>:: priority[amount];
    Stree.MakePriority(prior, text.toStdString(), amount);
    Stree.MakeNodes(prior, amount, ptr, count);
    Stree.Huffman(ptr, count);
    Coder<char>* result = ptr.Head->x;
    Coder<char>::CodedValue* Scode = new Coder<char>::CodedValue[amount];
    Stree.WriteCodedValue(result, Scode, index_1);
    auto start = std::chrono::steady_clock::now();
    vector<char> static_code = Static_encode(Scode, text, amount);
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    return std::chrono::duration <double, std::nano> (diff).count();
}


void MainWindow::on_pushButton_clicked()
{
    ui->label->setWordWrap(true);
    ui->label_6->setWordWrap(true);
    QString text = ui->lineEdit->text();
    if (!text.isEmpty()){
        Tree = Adaptive_MakeTree(text.toStdString().c_str());
        vector<char> code = Adaptive_encode(Tree, text.toStdString().c_str());
        QString str_ad = VectorToString(code);
        ui->label->setText(str_ad);
        QString Adaptive_decodee = Adaptive_decode(Tree, code);
        ui->label_6->setText(Adaptive_decodee);

        int count = 0;
        int index_1 = 0;
        Coder<char> Stree;
        List<Coder<char>*> ptr;
        int amount = Stree.CountOfLetters(text.toStdString());
        Coder<char>::priority* prior = new Coder<char>:: priority[amount];
        Stree.MakePriority(prior, text.toStdString(), amount);
        Stree.MakeNodes(prior, amount, ptr, count);
        Stree.Huffman(ptr, count);
        Coder<char>* result = ptr.Head->x;
        Coder<char>::CodedValue* Scode = new Coder<char>::CodedValue[amount];
        Stree.WriteCodedValue(result, Scode, index_1);

        vector<char> static_code = Static_encode(Scode, text, amount);
        QString str = VectorToString(static_code);
        ui->label_5->setText(str);

        ui->label_9->setText(Static_decode(result, static_code));
    }

}


void MainWindow::on_pushButton_2_clicked()
{
    QChart *chrt = new QChart();
    QChart *chrt1 = new QChart();
    QChart *chrt2 = new QChart();
    QChart *chrt3 = new QChart();
    QChart *chrt4 = new QChart();
    QChart *chrt5 = new QChart();

    ui->widget->setChart(chrt); // связь графика с элементом отображения
    ui->widget_2->setChart(chrt1);
    ui->widget_3->setChart(chrt2);
    ui->widget_4->setChart(chrt3);
    ui->widget_5->setChart(chrt4);
    ui->widget_6->setChart(chrt5);

    chrt->setTitle("Middle case encode");
    chrt1->setTitle("Middle case decode");
    chrt2->setTitle("Worst case encode");
    chrt3->setTitle("Worst case decode");
    chrt4->setTitle("Best case encode");
    chrt5->setTitle("Best case decode");

    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Data");
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Time");
    QValueAxis *axisX1 = new QValueAxis;
    axisX1->setTitleText("Data");
    QValueAxis *axisY1 = new QValueAxis;
    axisY1->setTitleText("Time");
    QValueAxis *axisX2 = new QValueAxis;
    axisX2->setTitleText("Data");
    QValueAxis *axisY2 = new QValueAxis;
    axisY2->setTitleText("Time");
    QValueAxis *axisX3 = new QValueAxis;
    axisX3->setTitleText("Data");
    QValueAxis *axisY3 = new QValueAxis;
    axisY3->setTitleText("Time");
    QValueAxis *axisX4 = new QValueAxis;
    axisX4->setTitleText("Data");
    QValueAxis *axisY4 = new QValueAxis;
    axisY4->setTitleText("Time");
    QValueAxis *axisX5 = new QValueAxis;
    axisX5->setTitleText("Data");
    QValueAxis *axisY5 = new QValueAxis;
    axisY5->setTitleText("Time");

    QScatterSeries* series1 = new QScatterSeries(); //for middle encode
    series1->setName("Static Encode");
    series1->setMarkerSize(5);
    QScatterSeries* series2 = new QScatterSeries();
    series2->setName("Adaptive Encode");
    series2->setMarkerSize(5);

    QScatterSeries* series3 = new QScatterSeries(); //for middle decode
    series3->setName("Static Decode");
    series3->setMarkerSize(5);
    QScatterSeries* series4 = new QScatterSeries();
    series4->setName("Adaptive Decode");
    series4->setMarkerSize(5);

    QScatterSeries* series5 = new QScatterSeries(); //for worst encode
    series5->setName("Static Encode");
    series5->setMarkerSize(5);
    QScatterSeries* series6 = new QScatterSeries();
    series6->setName("Adaptive Encode");
    series6->setMarkerSize(5);

    QScatterSeries* series7 = new QScatterSeries(); //for worst decode
    series7->setName("Static Decode");
    series7->setMarkerSize(5);
    QScatterSeries* series8 = new QScatterSeries();
    series8->setName("Adaptive Decode");
    series8->setMarkerSize(5);

    QScatterSeries* series9 = new QScatterSeries(); //for best encode
    series9->setName("Static Encode");
    series9->setMarkerSize(5);
    QScatterSeries* series10 = new QScatterSeries();
    series10->setName("Adaptive Encode");
    series10->setMarkerSize(5);

    QScatterSeries* series11 = new QScatterSeries(); //for best decode
    series11->setName("Static Decode");
    series11->setMarkerSize(7);
    QScatterSeries* series12 = new QScatterSeries();
    series12->setName("Adaptive Decode");
    series12->setMarkerSize(7);


    QLineSeries* seriesLog1 = new QLineSeries();
    seriesLog1->setName("O(log(n))");
    QLineSeries* seriesLog2 = new QLineSeries();
    seriesLog2->setName("O(log(n))");
    QLineSeries* seriesPowN = new QLineSeries;
    seriesPowN->setName("O(n^2)");
    QLineSeries* seriesPowN2 = new QLineSeries;
    seriesPowN2->setName("O(n^2)");
    // построение графиков функций
    for(size_t i = 2; i<300; i ++)
    {
        QString text = generateAverageCase(i);
        seriesLog1->append(i, log(i));
        seriesLog2->append(i, log(i));
        series1->append(i, StaticEncode_time(text));
        series2->append(i, AdaptiveEncode_time(text));
        series3->append(i, StaticDecode_time(text));
        series4->append(i, AdaptiveDecode_time(text));
    }

    for(size_t i = 2; i < possibleCharacters.size(); i ++)
    {
        QString text = generateWorstCase(i);
            seriesPowN->append(i, pow(i,2));
            seriesPowN2->append(i, pow(i,2));
            series5->append(i, StaticEncode_time(text));
            series6->append(i, AdaptiveEncode_time(text));
            series7->append(i, StaticDecode_time(text));
            series8->append(i, AdaptiveDecode_time(text));
    }

    for(size_t i = 2; i<200; i ++)
    {
        QString text = generateBestCase(i);
       // seriesLog->append(i, log(i));
            series9->append(i, StaticEncode_time(text));
            series10->append(i, AdaptiveEncode_time(text));
            series11->append(i, StaticDecode_time(text));
            series12->append(i, AdaptiveDecode_time(text));
    }


    chrt->addSeries(series1);
    chrt->addSeries(series2);
    chrt->addSeries(seriesLog1);

    chrt1->addSeries(series3);
    chrt1->addSeries(series4);
    chrt1->addSeries(seriesLog2);

    chrt2->addSeries(series5);
    chrt2->addSeries(series6);
    chrt2->addSeries(seriesPowN);

    chrt3->addSeries(series7);
    chrt3->addSeries(series8);
    chrt3->addSeries(seriesPowN2);

    chrt4->addSeries(series9);
    chrt4->addSeries(series10);

    chrt5->addSeries(series11);
    chrt5->addSeries(series12);

    // устанавливаем оси для каждого графика

    chrt->setAxisX(axisX, series1);
    chrt->setAxisY(axisY, series1);

    chrt1->setAxisX(axisX1, series3);
    chrt1->setAxisY(axisY1, series3);

    chrt2->setAxisX(axisX2, series5);
    chrt2->setAxisY(axisY2, series5);

    chrt3->setAxisX(axisX3, series7);
    chrt3->setAxisY(axisY3, series7);

    chrt4->setAxisX(axisX4, series9);
    chrt4->setAxisY(axisY4, series9);

    chrt5->setAxisX(axisX5, series11);
    chrt5->setAxisY(axisY5, series11);

//////////////////
}
