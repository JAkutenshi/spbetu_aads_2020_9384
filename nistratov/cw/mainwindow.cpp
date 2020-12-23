#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, 800, 800, this);
    ui->drawview->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    srand(time(NULL));
    ui->textBrowser->clear();
    scene->clear();
    ui->textBrowser->setText("Treap visualization\n");
}

void MainWindow::on_worst_clicked()
{
    start();
    std::string info = "Worst Case treap:\nO(n)\nSorted array without rand() or prev.rand < new.rand\n";
    int wc[] = {1, 2, 3, 4, 5, 6, 7, 8};
    generate<int>(wc, (sizeof(wc)/sizeof(wc[0])), info, false);
}

void MainWindow::on_random_clicked()
{
   start();
   std::string info = "Randomly generated array:\nO(nlogn)\nInserting the keys one at a time\n";
   int rnd[8];
   for (int i = 0; i < 8; i++ ) {
       rnd[i] = rand();
   }
   generate<int>(rnd, 8, info, true);
}

void MainWindow::on_file_clicked()
{
    start();
    std::string info = "Read array from file\n";
    QString fileName = QFileDialog::getOpenFileName(this,
           tr("Open Load File"), "",
           tr("Load File (*.txt)"));
    std::ifstream file(fileName.toStdString());
    std::string array;
    std::getline(file, array);
    std::stringstream ss;
    int val[10];
    ss << array;
    for (int i = 0; i < 10; i++){
        ss >> val[i];
    }
    generate<int>(val, 10, info, true);
}

void MainWindow::on_create_clicked()
{
    start();
    std::string info = "Generate treap from input:\nO(nlogn)\nArray:\n";
    std::string array = qPrintable(ui->lineEdit->text());
    std::stringstream ss;
    int val[1000];
    ss << array;
    int size;
    for (size = 0; !ss.eof(); size++){
        ss >> val[size];
        std::cout << val[size] << std::endl;
    }
    generate<int>(val, size, info, true);
}

template<typename T>
void MainWindow::generate(T *array, size_t s, std::string info, bool prior)
{
    QElapsedTimer timer;
    Treap<T> worstcase;
    timer.start();
    for (size_t t = 0; t < s; t++)
        {
            if (prior)
                worstcase.insert(array[t], rand());
            else
                worstcase.insert(array[t], rand()%1);
        }
    int tmr = timer.nsecsElapsed();
    worstcase.info_expand(info);
    info.append("\nTime spend:");
    info.append(std::to_string(tmr));
    info.append(" nanoseconds");
    ui->textBrowser->setText(QString::fromStdString(info));
    worstcase.drawTree(scene, 400, 100, 20);
}
