#ifndef MAKETREE_H
#define MAKETREE_H


#include "tree.h"

class maketree
{
public:
    maketree();
    BinaryTree<char> *createTree(std::string str);
    char slit(std::string str, std::string &data1, std::string &data2);
    void printTree(BinaryTree<char> *symb, std::string& output, int offset);
    void calcTree(BinaryTree<char> *tr);

private:
};

#endif // MAKETREE_H
