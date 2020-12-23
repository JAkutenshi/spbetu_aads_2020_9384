#ifndef TREAP_H
#define TREAP_H

#include <iostream>
#include <fstream>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPen>

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

    void drawTree(QGraphicsScene *scene, int w, int h, int depth)
    {
        _drawTree(scene, root, w, h, depth);
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

    void _drawTree(QGraphicsScene *&scene, Treap<T> *tr, float w, float h, float depth)
    {
        QPen pen;
        if (tr == nullptr)
        {
            scene->addEllipse(w, h, 40, 40, pen, QBrush(Qt::red));
            QGraphicsTextItem *null = new QGraphicsTextItem;
            null->setPos(w, h+5);
            null->setPlainText(" NULL");
            scene->addItem(null);
            return ;
        }
        QString text, textRand;
        text = QString::fromStdString(std::to_string(tr->value));
        textRand = QString::fromStdString(std::to_string(tr->R));
        QGraphicsTextItem *let = new QGraphicsTextItem;
        QGraphicsTextItem *letRand = new QGraphicsTextItem;
        let->setPos(w, h+3);
        let->setPlainText(text);
        letRand->setPos(w, h+13);
        letRand->setPlainText(textRand);
        //if (tr->Left != nullptr)
        pen.setBrush(Qt::red);
            scene->addLine(w+15/2, h+15, w-(depth/2)*15, h+70+15, pen);
       // if (tr->Right != nullptr)
                    pen.setBrush(Qt::blue);
            scene->addLine(w+15/2, h+15, w+(depth/2)*15, h+70+15, pen);
        scene->addEllipse(w, h, 40, 40, pen, QBrush(Qt::blue));
        scene->addItem(let);
        scene->addItem(letRand);
        _drawTree(scene, tr->Left, w-(depth/2)*15, h+70, depth/2);
        _drawTree(scene, tr->Right, w+(depth/2)*15, h+70, depth/2);
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
