#include "statistic.h"

Statistic::Statistic() : QGroupBox(tr("Statistic")){
    time = new QLineEdit("generation time:");
    time->setReadOnly(true);

    operation_count = new QLineEdit("operation count:");
    operation_count->setReadOnly(true);

    optimal_depth = new QLineEdit("optimal tree depth:");
    optimal_depth->setReadOnly(true);

    depth = new QLineEdit("current depth:");
    depth->setReadOnly(true);

    time_average = new QLineEdit("average find elem time:");
    time_average->setReadOnly(true);

    worst_time = new QLineEdit("worst find case:");
    worst_time->setReadOnly(true);

    layout = new QVBoxLayout;
    layout->addWidget(time);
    layout->addWidget(operation_count);
    layout->addWidget(optimal_depth);
    layout->addWidget(depth);
    layout->addWidget(time_average);
    layout->addWidget(worst_time);
    setLayout(layout);
}

void Statistic::add_info(float all_time, int operation_count, int optimal_depth, int depth, float avg_time, float worst_time){
    time->setText("generation time: " + QString::number(all_time) + " ms");
    this->operation_count->setText("operation count: " + QString::number(operation_count));
    this->optimal_depth->setText("optimal tree depth: " + QString::number(optimal_depth));
    this->depth->setText("current depth: " + QString::number(depth));
    time_average->setText("average find elem time: " + QString::number(avg_time) + " ms");
    this->worst_time->setText("worst find case: " + QString::number(worst_time) + " ms");
}

Statistic::~Statistic(){
    delete time;
    delete operation_count;
    delete optimal_depth;
    delete depth;
    delete time_average;
    delete worst_time;
    delete layout;
}
