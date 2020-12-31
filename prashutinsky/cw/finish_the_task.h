#ifndef FINISH_THE_TASK_H
#define FINISH_THE_TASK_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class finish_the_task;
}

class finish_the_task : public QDialog
{
    Q_OBJECT

public:
    explicit finish_the_task(QWidget *parent = nullptr);
    ~finish_the_task();

private slots:



    void on_buttonBox_accepted();

private:
    Ui::finish_the_task *ui;
};

#endif // FINISH_THE_TASK_H
