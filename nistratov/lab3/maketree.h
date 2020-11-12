#ifndef MAKETREE_H
#define MAKETREE_H

#include "tree.h"
#include <stack>
#include <exception>
#include <algorithm>

BinaryTree<char> *createTree(std::string str);
char split(std::string str, std::string &left_data, std::string &right_data);
void printTree(BinaryTree<char> *symb, std::string& output, int offset);
void calcTree(BinaryTree<char> *tr);
std::string createLRC(std::string str);
void stringchecker(std::string &str);

#endif // MAKETREE_H
