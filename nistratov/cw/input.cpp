#include "input.h"
#include "ui_input.h"

input::input(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::input)
{
    ui->setupUi(this);
    QRegExp rx("[0-9 ]*");
    QValidator* validator = new QRegExpValidator(rx, this);
    sWindow = new StartMenu();
    ui->text->setValidator(validator);
}

input::~input()
{
    delete ui;
}

std::string input::getline()
{
    return qPrintable(ui->text->text());
}

void input::setarrsize(int n)
{
    arraysize = n;
}

void input::setPrior(bool n)
{
    prior = n;
}

void input::on_ok_clicked()
{
    std::string temp = getline();
    sWindow->setArrSize(arraysize);
    sWindow->setPrior(prior);
    sWindow->ingen(temp);
    sWindow->show();
    this->close();
}

void input::on_closew_clicked()
{
    this->close();
}
