#include "mainwindow.h"

#include <QApplication>

#include "AVL_Tree.h"
#include "treeviewwidget.h"
#include "graphicwidget.h"
#include <QRandomGenerator>
#include <QVector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    TreeViewWidget* treeView = new TreeViewWidget(&w);
//    AVL_Tree<int> tree;

//    tree.insert(1);
//    tree.insert(2);
//    tree.insert(3);
//    tree.insert(4);
//    tree.insert(5);
//    tree.insert(6);
//    tree.insert(7);
//    tree.remove(4);
//    tree.remove(5);
//       tree.remove(1);
//    for(int i=0; i<data.size(); i++) {
//        tree.insert(data[i]);
//    }
//    qDebug() << "operations" << data.size() << tree.number_of_operations();
//    treeView->drawTree(tree.getRoot(), tree.height());


    GraphicWidget* g = new GraphicWidget(&w);
    g->drawStatistics();
    w.show();
    return a.exec();
}
