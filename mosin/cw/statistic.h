#ifndef STATISTIC_H
#define STATISTIC_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>

class Statistic  : public QGroupBox{
public:
    Statistic();
    ~Statistic();
    void add_info(float, int, int, int, float, float);

private:
    QVBoxLayout* layout;
    QLineEdit* time;
    QLineEdit* operation_count;
    QLineEdit* optimal_depth;
    QLineEdit* depth;
    QLineEdit* time_average;
    QLineEdit* worst_time;
};

#endif // STATISTIC_H
