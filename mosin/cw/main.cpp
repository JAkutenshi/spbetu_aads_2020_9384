#include "window.h"

#include <QApplication>

int main(int argc, char** argv){
    srand(time(0));
    QApplication a(argc, argv);
    Window* w = new Window;
    w->show();
    return a.exec();
}
