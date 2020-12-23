#include "scene.h"
#include <cmath>
#include <iostream>

void Scene::add_item(Tree* tree){
    if(tree){
        tree->setPos(0,0);
        addItem(tree);
        add_left(tree->get_left(), 0, 0);
        add_right(tree->get_right(), 0, 0);
    }
}

void Scene::add_line(Tree *tree){
    if(tree){
        if(tree->get_left()){
            addLine(tree->x()+25*tree->scale(), tree->y(), tree->get_left()->x()+25*tree->scale(), tree->get_left()->y());
            add_line(tree->get_left());
        }
        if(tree->get_right()){
            addLine(tree->x()+25*tree->scale(), tree->y(), tree->get_right()->x()+25*tree->scale(), tree->get_right()->y());
            add_line(tree->get_right());
        }
    }
}

void Scene::add_left(Tree *tree, int x, int y){
    if(tree){
        int new_x = x - 50*tree->get_depth(tree);
        int new_y = y + 50;
        tree->setPos(new_x, new_y);
        addItem(tree);
        add_left(tree->get_left(), new_x, new_y);
        add_right(tree->get_right(), new_x, new_y);
    }
}

void Scene::add_right(Tree *tree, int x, int y){
    if(tree){
        int new_x = x + 50*tree->get_depth(tree);
        int new_y = y + 50;
        tree->setPos(new_x, new_y);
        addItem(tree);
        add_left(tree->get_left(), new_x, new_y);
        add_right(tree->get_right(), new_x, new_y);
    }
}
