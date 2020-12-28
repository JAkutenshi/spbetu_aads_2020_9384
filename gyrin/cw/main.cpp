#include "mainwindow.h"
#include <fstream>
#include <string>
#include <QApplication>
#include "BinaryTree.h"


//
// пока что работает только кнопка ввода строки для кодировки
// результат пока что не выводит
//
// построение дерева не доделано
//

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
