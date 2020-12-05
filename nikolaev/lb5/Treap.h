#ifndef TREAP_H
#define TREAP_H

#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename T>
class Treap
{
public:
    Treap() {};
    Treap(T key, int priority) : key(key), priority(priority), left(nullptr), right(nullptr) {};

    void insert(T key)
    {
        _insert(root, new Treap<T>(key, rand()));
    }

    void print()
    {
        _print(root);
    }

    int find(T key)
    {
        count = 0;
        return _find(root, key);
    }

private:
    void split(Treap* t, T& key, Treap*& left, Treap*& right)
    {
        if (t == nullptr)
        {
            left = right = nullptr;
        }
        else if (key < t->key)
        {
            split(t->left, key, left, t->left);
            right = t;
        }
        else
        {
            split(t->right, key, t->right, right);
            left = t;
        }
    }

    void merge(Treap*& t, Treap* left, Treap* right)
    {
        if (!left || !right)
            t = left ? left : right;
        else if (left->priority >= right->priority)
        {
            merge(left->right, left->right, right);
            t = left;
        }
        else
        {
            merge(right->left, left, right->left);
            t = right;
        }
    }

    void _insert(Treap*& t, Treap* it)
    {
        if (t == nullptr)
        {
            t = it;
            return;
        }

        if (it->priority > t->priority)
        {
            split(t, it->key, it->left, it->right);
            t = it;
        }
        else
        {
            _insert(it->key < t->key ? t->left : t->right, it);
        }
    }

    void _print(Treap*& t, int space = 0, int height = 10)
    {
        if (t == nullptr)
            return;
        space += height;
        _print(t->left, space);
        std::cout << std::endl;
        for (int i = height; i < space; i++)
            std::cout << ' ';
        std::cout << t->key << "(" << t->priority << ")\n";
        std::cout << std::endl;
        _print(t->right, space);
    }

    int _find(Treap*& t, T key)
    {
        if (t != nullptr)
        {
            if (t->key == key)
            {
                count += 1;
                _find(t->left, key);
                _find(t->right, key);
            }
            else if (t->key > key)
            {
                _find(t->left, key);
            }
            else
            {
                _find(t->right, key);
            }
        }
        return count;
    }
private:
    T key;
    int priority;
    Treap* left, * right;
    Treap* root = nullptr;
    size_t count;
};
#endif // TREAP_H