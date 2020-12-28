#include "startmenu.h"
#include "ui_startmenu.h"

StartMenu::StartMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartMenu)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, 800, 800, this);
    chart1_scene = new QGraphicsScene(0, 0, 500, 260, this);
    chart2_scene = new QGraphicsScene(0, 0, 500, 260, this);
    ui->drawview->setScene(scene);
    scene->setSceneRect(scene->itemsBoundingRect());
    chart1 = new QChart();
    chart2 = new QChart();
}

StartMenu::~StartMenu()
{
    delete ui;
}

void StartMenu::start()
{
    ui->textBrowser->clear();
    scene->clear();
    ui->textBrowser->setText("Treap visualization\n");
}

void StartMenu::setArrSize(int n)
{
    arraysize = n;
}

void StartMenu::setPrior(bool n)
{
    prior = n;
}

void StartMenu::random()
{
    start();
    info = "Randomly generated array:\nO(nlogn)\nInserting the keys one at a time\n";
    array = new int[arraysize];
    for (int i = 0; i < arraysize; i++ ) {
        array[i] = rand();
    }
}

void StartMenu::ingen(std::string str)
{
    start();
    info = "Generate treap from input:\nO(nlogn)\nArray:\n";
    std::stringstream ss;
    int tempcnt = 0;
    array = new int[arraysize];
    ss << str;
    for (int i = 0; !ss.eof() && (i < arraysize); i++){
        tempcnt++;
        ss >> array[i];
    }
    setArrSize(tempcnt);
}

void StartMenu::on_worst_clicked()
{
    start();
    info = "Worst Case treap:\nO(n)\nSorted array without rand() or prev.rand < new.rand\n";
    newprior = false;
    int wc[arraysize];
    for (int i = 0; i < arraysize; i++)
        wc[i] = i+1;
    generate<int>(wc, arraysize, info, false);
}

void StartMenu::on_draw_clicked()
{
    start();
    info = "Treap:\n";
    newprior = prior;
    generate<int>(array, arraysize, info, prior);
}

void StartMenu::on_add_clicked()
{
    int temp = ui->spinBox->value();
    QElapsedTimer timer;
    std::string temparray;
    if (newprior){
        timer.start();
        treap->insert(temp, rand());
    }
    else
    {
        timer.start();
        treap->insert(temp, rand()%1);
    }
    int tmr = timer.nsecsElapsed();
    time_array[curr_arraysize++] = tmr;
    treap->info_expand(temparray);
    setArray(temparray);
    setChart();
    scene->clear();
    treap->drawTree(scene, curr_arraysize);
}

void StartMenu::on_deleteb_clicked()
{
    QElapsedTimer timer;
    std::string temparray;
    bool exist = false;
    if (curr_arraysize == 0) return;
    switch (ui->comboBox->currentIndex()) {
    case 0:
        timer.start();
        treap->erase(curr_array[0]);
        del_array[del_arraysize++] = timer.nsecsElapsed();
        curr_arraysize--;
        break;
    case 1:
        for (int i = 0; i < curr_arraysize; i++){
            if (ui->delbox->value() == curr_array[i])
                exist = true;
        }
        if (!exist) return;
        timer.start();
        treap->erase(ui->delbox->value());
        del_array[del_arraysize++] = timer.nsecsElapsed();
        curr_arraysize--;
        break;
    case 2:
        timer.start();
        treap->erase(curr_array[curr_arraysize-1]);
        del_array[del_arraysize++] = timer.nsecsElapsed();
        curr_arraysize--;
        break;
    }
    treap->info_expand(temparray);
    setArray(temparray);
    setChart();
    setDelChart();
    scene->clear();
    treap->drawTree(scene, curr_arraysize);
}

void StartMenu::setArray(std::string str)
{
    std::stringstream ss;
    curr_array = new int[curr_arraysize];
    ss << str;
    for (int i = 0; i < curr_arraysize; i++)
        ss >> curr_array[i];
}

void StartMenu::setChart()
{
    chart1->legend()->hide();
    chart1->removeAllSeries();
    series1 = new QLineSeries();
    for (int i = 0; i < curr_arraysize; i++)
    {
        *series1 << QPoint(i+1, time_array[i]);
    }
    chart1->addSeries(series1);
    chart1->createDefaultAxes();
    chart1->setTitle("Input Chart");
    chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);
    chartView1->resize(500, 260);
    chart1_scene->addWidget(chartView1);
    ui->chart_1->setScene(chart1_scene);
}

void StartMenu::setDelChart()
{
    chart2->legend()->hide();
    chart2->removeAllSeries();
    series2 = new QLineSeries();
    for (int i = 0; i < del_arraysize; i++)
    {
        *series2 << QPoint(i+1, del_array[i]);
    }
    chart2->addSeries(series2);
    chart2->createDefaultAxes();
    chart2->setTitle("Delete Chart");
    chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);
    chartView2->resize(500, 260);
    chart2_scene->addWidget(chartView2);
    ui->chart_2->setScene(chart2_scene);
}

template<typename T>
void StartMenu::generate(T *array, size_t s, std::string info, bool prior)
{
    QElapsedTimer timer;
    std::string temparray;
    int temp = 0, tmr = 0;
    treap = new Treap<int>();
    for (size_t t = 0; t < s; t++)
        {
            if (prior){
                timer.start();
                treap->insert(array[t], rand());
                temp = timer.nsecsElapsed();
            }
            else
            {
                timer.start();
                treap->insert(array[t], rand()%1);
                temp = timer.nsecsElapsed();
            }
            time_array[t] = temp;
            tmr += temp;
        }
    curr_arraysize = arraysize;
    treap->info_expand(info);
    treap->info_expand(temparray);
    setArray(temparray);
    info.append("\nTime spend:");
    info.append(std::to_string(tmr));
    info.append(" nanoseconds");
    ui->textBrowser->setText(QString::fromStdString(info));
    treap->drawTree(scene, arraysize);
    curr_del_last = arraysize;
    setChart();
    chart2->removeAllSeries();
    del_arraysize = 0;
    curr_del = 0;
}
