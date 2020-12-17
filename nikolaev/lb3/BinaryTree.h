#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <string>
#include <algorithm>

template <class base>
class BinaryTree {
public:
    BinaryTree();
    base RootBT();
    void printBT();
    void change();
    void createBT(std::string& tmp);
    void destroy();
    bool IsNull();
    ~BinaryTree();

private:
    BinaryTree* l;
    BinaryTree* r;
    base data;
};

#endif