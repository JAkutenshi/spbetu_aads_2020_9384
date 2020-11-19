#ifndef TREAP_H
#define TREAP_H

#include <iostream>
#include <fstream>

template <typename T>
class Treap
{
public:
    Treap() {};
    Treap(T value, int R) : value(value), R(R), Left(nullptr), Right(nullptr) {};

    void split(Treap* t, Treap *&left, Treap *&right, T& val)
    {
        if (t == nullptr)
        {
            left = nullptr;
            right = nullptr;
            return;
        }
        else if (t->value > val)
        {
            std::cout << "split: value > new data, go right" << std::endl;
            split(t->Left, left, t->Left, val);
            right = t;
        }
        else
        {
            std::cout << "split: value < new data, go left" << std::endl;
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
            std::cout << "merge: random value of left data >= random value of right data" << std::endl;
            merge(left->Right, left->Right, right);
            t = left;
        }
        else{
            std::cout << "merge: random value of left data < random value of right data" << std::endl;
            merge(right->Left, left, right->Left);
            t = right;
        }
    }

    void insert(Treap*& t, Treap* v)
    {
        if (!t)
            t = v;
        else if (v->R > t->R)
        {
            std::cout << "insert: Random value of new Data higher" << std::endl;
            split(t, v->Left, v->Right, v->value);
            t = v;
        }
        else if (v->value < t->value)
        {
            std::cout << "insert: new data < node data" << std::endl;
            insert(t->Left, v);
        }
        else
        {
            std::cout << "insert: new data > node data" << std::endl;
            insert(t->Right, v);
        }
    }

    void erase (Treap*& t, T key)
    {
        if (!t) return;
        if (t->value == key){
            std::cout << "erase: Value: " << key << " found!" << std::endl;
            merge(t, t->Left, t->Right);
        }
        else if (t->value > key)
            erase(t->Left, key);
        else
            erase(t->Right, key);
    }

    void print(Treap *&t)
    {
        if (!t) return;
        print(t->Left);
        std::cout << t->value <<' ';
        print(t->Right);
    }

    void write(Treap *&t, std::ofstream &file)
    {
        if (!t) return;
        write(t->Left, file);
        file << t->value << ' ';
        write(t->Right, file);
    }

    T value;
    int R;

    Treap *Left, *Right;
    Treap *root = nullptr;
};

#endif // TREAP_H
