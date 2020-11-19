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

    void erase(T val)
    {
        _erase(root, val);
    }

    void insert(T val)
    {
        _insert(root, new Treap<int>(val, rand()));
    }

    void print()
    {
        _print(root);
    }

    void write(std::ofstream &file)
    {
        _write(root, file);
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

        void _insert(Treap*& t, Treap* v)
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
            _insert(t->Left, v);
        }
        else
        {
            std::cout << "insert: new data > node data" << std::endl;
            _insert(t->Right, v);
        }
    }

    void _erase (Treap*& t, T key)
    {
        if (!t) return;
        if (t->value == key){
            std::cout << "erase: Value: " << key << " found!" << std::endl;
            merge(t, t->Left, t->Right);
        }
        else if (t->value > key)
            _erase(t->Left, key);
        else
            _erase(t->Right, key);
    }

    void _print(Treap *&t)
    {
        if (!t) return;
        _print(t->Left);
        std::cout << t->value <<' ';
        _print(t->Right);
    }

    void _write(Treap *&t, std::ofstream &file)
    {
        if (!t) return;
        _write(t->Left, file);
        file << t->value << ' ';
        _write(t->Right, file);
    }
};

#endif // TREAP_H
