#include "finish_the_task.h"
#include "ui_finish_the_task.h"

finish_the_task::finish_the_task(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::finish_the_task)
{
    ui->setupUi(this);
}

finish_the_task::~finish_the_task()
{
    delete ui;
}

void finish_the_task::on_buttonBox_accepted()
{

}
