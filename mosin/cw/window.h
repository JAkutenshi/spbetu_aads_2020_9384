#ifndef WINDOW_H
#define WINDOW_H

#include <QObject>

#include <QWidget>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QGraphicsItem>

#include "scene.h"
#include "tree.h"
#include "statistic.h"
#include "usergen.h"
#include "programgen.h"

#include <iostream>
#include <array>

class Window : public QWidget{
    Q_OBJECT
public:
    Window();
    ~Window();

private slots:
    void user_generate();
    void program_generate();
    void chose_file();

private:
    QGridLayout* layout;
    Scene* scene;
    QGraphicsView* view;
    Tree* tree;
    Statistic* statistic;
    ProgramGen* program_gen;
    UserGen* user_gen;

    int* array;
    int index;
    int array_size;
};

#endif // WINDOW_H
