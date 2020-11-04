#ifndef TREE_H
#define TREE_H

#include <string>

template <class T>
class BinaryTree
{
public:
    BinaryTree() {};
    BinaryTree(T value) {
        this->data = value;
    }
    ~BinaryTree(){
        delete left;
        delete right;
    }

    T getData()
    {
        return this->data;
    }

    BinaryTree* left = nullptr;
    BinaryTree* right = nullptr;
    T data;
private:
};

#endif // TREE_H
