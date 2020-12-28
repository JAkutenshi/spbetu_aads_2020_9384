#ifndef INPUT_H
#define INPUT_H

#include <QWidget>
#include <QValidator>
#include <QRegExpValidator>
#include "startmenu.h"

namespace Ui {
class input;
}

class input : public QWidget
{
    Q_OBJECT

public:
    explicit input(QWidget *parent = nullptr);
    ~input();
    std::string getline();

    void setarrsize(int n);
    void setPrior(bool n);

public slots:
    void on_ok_clicked();
    void on_closew_clicked();

private:
    Ui::input *ui;
    StartMenu* sWindow;

    int arraysize;
    bool prior;
};

#endif // INPUT_H
