#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "tree.h"

class Scene : public QGraphicsScene{
public:
    void add_item(Tree*);
    void add_line(Tree*);

private:
    void add_left(Tree*, int, int);
    void add_right(Tree*, int, int);

private:
    int depth;
};

#endif // SCENE_H
