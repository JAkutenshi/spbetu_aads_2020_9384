#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <QString>
#include <QDebug>

template <class T>
class BinaryTree
{
public:
    BinaryTree() {}

    BinaryTree(T data) {
        this->data = data;
    }

    ~BinaryTree() {
        if(left) delete left;
        if(right) delete right;
    }

    void setData(T data) {
        this->data = data;
    }

    T getData() {
        return this->data;
    }

    int height() {
        int left_h = 0;
        int right_h = 0;
        if(this->left) left_h = left->height();
        if(this->right) right_h = right->height();
        return left_h>right_h? left_h+1 : right_h+1;
    }

    void print(int offset=0) {
        qDebug() << QString(' ').repeated(offset) << (this->data);
        if(this->left)
            this->left->print(offset+2);
        if(this->right)
            this->right->print(offset+2);
    }

    BinaryTree* left = nullptr;
    BinaryTree* right = nullptr;

private:
    T data;

};

#endif // BINARYTREE_H
