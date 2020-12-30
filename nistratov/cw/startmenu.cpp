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
    chart3_scene = new QGraphicsScene(0, 0, 500, 260, this);
    ui->drawview->setScene(scene);
    scene->setSceneRect(scene->itemsBoundingRect());
    chart1 = new QChart();
    chart2 = new QChart();
    chart3 = new QChart();
    srand(time(NULL));
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
    int tmr;
    std::string temparray;
    switch (ui->comboBox_2->currentIndex()) {
    case 0:
        if (newprior){
            int rand1 = rand();
            timer.start();
            treap->insert(temp, rand1);
            tmr = timer.nsecsElapsed();
        }
        else
        {
            int rand1 = rand();
            timer.start();
            treap->insert(temp, rand1%1);
            tmr = timer.nsecsElapsed();

        }
        time_array[curr_arraysize++] = tmr;
        treap->info_expand(temparray);
        setArray(temparray);
        break;
    case 1:
        for (int i = 0; i < temp; i++)
        {
            if (newprior){
                int rand1 = rand();
                int rand2 = rand();
                timer.start();
                treap->insert(rand1, rand2);
                tmr = timer.nsecsElapsed();
            }
            else
            {
                int rand1 = rand();
                int rand2 = rand();
                timer.start();
                treap->insert(rand1, rand2%1);
                tmr = timer.nsecsElapsed();

            }
            if (tmr > time_array[curr_arraysize-1]* 3)
                tmr = time_array[curr_arraysize-1];
            time_array[curr_arraysize++] = tmr;
            treap->info_expand(temparray);
            setArray(temparray);
        }
    }
    setChart();
    scene->clear();
    treap->drawTree(scene, curr_arraysize);
}

void StartMenu::on_deleteb_clicked()
{
    std::string temparray;
    bool exist = false;
    int tmr;
    if (curr_arraysize == 0) return;
    switch (ui->comboBox->currentIndex()) {
    case 0:
        if (ui->delbox->value() > curr_arraysize)
            return;
        for (int i = 0; i < ui->delbox->value(); i++)
        {
            timer.start();
            treap->erase(curr_array[0]);
            tmr = timer.nsecsElapsed();
            curr_arraysize--;
            if (del_arraysize > 5){
            if (tmr > del_array[del_arraysize-1]* 3 && del_array[del_arraysize-1] > 100)
                tmr = del_array[del_arraysize-1];
            }
            del_array[del_arraysize++] = tmr;
            treap->info_expand(temparray);
            setArray(temparray);
        }
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
        treap->info_expand(temparray);
        setArray(temparray);
        break;
    case 2:
        if (ui->delbox->value() > curr_arraysize)
            return;
        for (int i = 0; i < ui->delbox->value(); i++)
        {
            timer.start();
            treap->erase(curr_array[curr_arraysize-1]);
            tmr = timer.nsecsElapsed();
            curr_arraysize--;
            if (del_arraysize > 5){
            if (tmr > del_array[del_arraysize-1]* 3 && del_array[del_arraysize-1] > 100)
                tmr = del_array[del_arraysize-1];
            }
            del_array[del_arraysize++] = tmr;
            treap->info_expand(temparray);
            setArray(temparray);
        }
        break;
    }
    setChart();
    setDelChart();
    scene->clear();
    treap->drawTree(scene, curr_arraysize);
}

void StartMenu::on_adddel_clicked()
{
    int tmr, tmr2;
    std::string temparray;
    for (int i = 0; i < 1000; i++){
        if (newprior){
            tmr2 = rand();
            timer.restart();
            treap->insert(tmr2, rand());
            tmr = timer.nsecsElapsed();
            time_array[curr_arraysize++] = tmr;
            treap->info_expand(temparray);
            setArray(temparray);
            timer.restart();
            treap->erase(tmr2);
            tmr2 = timer.nsecsElapsed();
            if (tmr > time_array[curr_arraysize-1]* 5)
                tmr = time_array[curr_arraysize-1];
            if (tmr2 > del_array[del_arraysize-1]* 5)
                tmr = del_array[del_arraysize-1];
        }
        else
        {
            int rand1 = rand();
            int rand2 = rand();
            timer.restart();
            treap->insert(rand1, rand2%1);
            tmr = timer.nsecsElapsed();
            timer.restart();
            treap->erase(rand1);
            tmr2 = timer.nsecsElapsed();
            if (tmr > time_array[curr_arraysize-1]* 3)
                tmr = time_array[curr_arraysize-1];
            if (tmr2 > del_array[del_arraysize-1]* 3)
                tmr = del_array[del_arraysize-1];

        }
        time_array[curr_arraysize++] = tmr;
        del_array[del_arraysize++] = tmr2;
    }
    setAddDelChart();
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
    chart1 = new QChart();
    chart1->legend()->hide();
    chart1->removeAllSeries();
    series1 = new QLineSeries();
    for (int i = 0; i < curr_arraysize; i++)
    {
        *series1 << QPointF(i+1, time_array[i]);
    }
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    axisX->setTitleText("Elements");
    axisY->setTitleText("Time spend (nsec)");
    chart1->addSeries(series1);
    chart1->addAxis(axisX, Qt::AlignBottom);
    chart1->addAxis(axisY, Qt::AlignLeft);
    series1->attachAxis(axisX);
    series1->attachAxis(axisY);
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
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    axisX->setTitleText("Elements deleted");
    axisY->setTitleText("Time spend (nsec)");
    chart2->addSeries(series2);
    chart2->addAxis(axisX, Qt::AlignBottom);
    chart2->addAxis(axisY, Qt::AlignLeft);
    series2->attachAxis(axisX);
    series2->attachAxis(axisY);
    chart2->createDefaultAxes();
    chart2->setTitle("Delete Chart");
    chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);
    chartView2->resize(500, 260);
    chart2_scene->addWidget(chartView2);
    ui->chart_2->setScene(chart2_scene);
}

void StartMenu::setAddDelChart()
{
    chart3 = new QChart();
    chart3->legend()->show();
    chart3->removeAllSeries();
    series1 = new QLineSeries();
    series2 = new QLineSeries();
    for (int i = 0; i < 1000; i++)
    {
        *series1 << QPointF(i+1, time_array[i]);
    }
    for (int i = 0; i < 1000; i++)
    {
        *series2 << QPointF(i+1, del_array[i]);
    }
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    axisX->setTitleText("Elements added and deleted");
    axisY->setTitleText("Time spend (nsec)");
    series1->setName("add");
    series1->setBrush(Qt::red);
    series2->setName("del");
    chart3->addSeries(series1);
    chart3->addSeries(series2);
    chart3->addAxis(axisX, Qt::AlignBottom);
    chart3->addAxis(axisY, Qt::AlignLeft);
    series1->attachAxis(axisX);
    series1->attachAxis(axisY);
    series2->attachAxis(axisX);
    series2->attachAxis(axisY);
    chart3->setTitle("Add/Del Chart");
    chartView3 = new QChartView(chart3);
    chartView3->setRenderHint(QPainter::Antialiasing);
    chartView3->resize(500, 260);
    chart3_scene->addWidget(chartView3);
    ui->chart_3->setScene(chart3_scene);
}

template<typename T>
void StartMenu::generate(T *array, size_t s, std::string info, bool prior)
{
    std::string temparray;
    double temp = 0, tmr = 0;
    treap = new Treap<int>();
    curr_arraysize = 0;
    for (size_t t = 0; t < s; t++)
        {
            if (prior){
                int rand1 = rand();
                int rand2 = rand();
                timer.start();
                treap->insert(array[t], rand2);
                tmr = timer.nsecsElapsed();
            }
            else
            {
                int rand1 = rand();
                int rand2 = rand();
                timer.start();
                treap->insert(array[t], rand2%1);
                tmr = timer.nsecsElapsed();

            }
            if (curr_arraysize > 5){
            if (tmr > time_array[curr_arraysize-1]* 3 && time_array[curr_arraysize-1] > 100)
                tmr = time_array[curr_arraysize-1];
            }
            time_array[curr_arraysize++] = tmr;
            treap->info_expand(temparray);
            setArray(temparray);
        }
        setChart();
    treap->info_expand(info);
    info.append("\nTime spend:");
    info.append(std::to_string(tmr));
    info.append(" nanoseconds");
    ui->textBrowser->setText(QString::fromStdString(info));
    treap->drawTree(scene, arraysize);
    curr_del_last = arraysize;
    chart2->removeAllSeries();
    del_arraysize = 0;
    curr_del = 0;
}
