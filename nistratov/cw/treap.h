#ifndef TREAP_H
#define TREAP_H

#include <iostream>
#include <fstream>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPen>
#include <math.h>

template <typename T>
class Treap
{
public:
    Treap() {};
    Treap(T value, int R) : value(value), R(R), Left(nullptr), Right(nullptr) {};

    void erase(T val)
    {
        _erase(root, val);
    }

    void insert(T val, int r)
    {
        _insert(root, new Treap<T>(val, r));
    }

    void print(std::ostream& streamOut)
    {
        _print(root, streamOut);
    }

    void write(std::ofstream &file)
    {
        _write(root, file);
    }

    void drawTree(QGraphicsScene *scene, int size)
    {
        sz = 2*std::log2(size);
        draw(scene, root, 0);
    }

    void info_expand(std::string &str)
    {
        _info_expand(root, str);
    }
private:

    T value;
    int R;

    Treap *Left, *Right;
    Treap* root = nullptr;
    int sz;
    void split(Treap* t, Treap *&left, Treap *&right, T& val)
    {
        if (t == nullptr)
        {
            left = nullptr;
            right = nullptr;
        }
        else if (t->value > val)
        {
            split(t->Left, left, t->Left, val);
            right = t;
        }
        else
        {
            split(t->Right, t->Right, right, val);
            left = t;
        }
    }

    void merge(Treap*& t, Treap* left, Treap* right)
    {
        if (!left){
            t = right;
            return;
        }
        if (!right){
            t = left;
            return;
        }
        if (left->R >= right->R){
            merge(left->Right, left->Right, right);
            t = left;
        }
        else{
            merge(right->Left, left, right->Left);
            t = right;
        }
    }

        void _insert(Treap*& t, Treap* v)
    {
        if (!t)
            t = v;
        else if (v->R > t->R)
        {
            split(t, v->Left, v->Right, v->value);
            t = v;
        }
        else
        {
            _insert (v->value < t->value ? t->Left : t->Right, v);
        }
    }

    void _erase (Treap*& t, T key)
    {
        if (!t) return;
        if (t->value == key){
            merge(t, t->Left, t->Right);
        }
        else if (t->value > key)
            _erase(t->Left, key);
        else
            _erase(t->Right, key);
    }

    void _print(Treap *&t, std::ostream& streamOut)
    {
        if (t == nullptr){
            streamOut << std::endl;
            return;
    }
        _print(t->Left, streamOut);
        streamOut << t->value <<' ';
        _print(t->Right, streamOut);
    }

    void draw(QGraphicsScene *scene, Treap<T> *tr, int index)
    {
        int x = 800;
        if (tr){
            if(index == 0){
                drawL(scene, tr->Left, index+1, x/2);
                drawR(scene, tr->Right, index+1, x/2);
                scene->addEllipse(x/2,50*(index+1),40,40,QColor(0,0,0),QColor(255,150,255));
                scene->addText(QString().setNum(tr->value))->setPos(x/2+2,50*(index+1));
                scene->addText(QString().setNum(tr->R))->setPos(x/2+2,50*(index+1)+10);
            }
        }
    }

    void drawL(QGraphicsScene *scene, Treap<T> *tr, int index, int offset)
    {
        if (tr){
            int x = offset - 8*pow(2,sz-index);
            scene->addLine(x + 12.5,50*(index+1)+12.5,offset+12.5,50*index +12.5,QPen(Qt::black,3));
            drawL(scene, tr->Left, index+1, x);
            drawR(scene, tr->Right, index+1, x);
            scene->addEllipse(x,50*(index+1),40,40,QColor(0,0,0),QColor(255,150,255));
            scene->addText(QString().setNum(tr->value))->setPos(x+2,50*(index+1));
            scene->addText(QString().setNum(tr->R))->setPos(x+2,50*(index+1)+10);
        }
    }

    void drawR(QGraphicsScene *scene, Treap<T> *tr, int index, int offset)
    {
        if (tr){
            int x = offset + 8*pow(2,sz-index);
            scene->addLine(x + 12.5,50*(index+1)+12.5,offset+12.5,50*index +12.5,QPen(Qt::black,3));
            drawL(scene, tr->Left, index+1, x);
            drawR(scene, tr->Right, index+1, x);
            scene->addEllipse(x,50*(index+1),40,40,QColor(0,0,0),QColor(255,150,255));
            scene->addText(QString().setNum(tr->value))->setPos(x+2,50*(index+1));
            scene->addText(QString().setNum(tr->R))->setPos(x+2,50*(index+1)+10);
        }
    }
    void _info_expand(Treap *t, std::string &str)
    {
        if (t == nullptr){
            return;
    }
        _info_expand(t->Left, str);
        str.append(std::to_string(t->value));
        str.append(" ");
        _info_expand(t->Right, str);
    }
};

#endif // TREAP_H
