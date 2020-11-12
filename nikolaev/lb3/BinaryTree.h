#ifndef BINARYTREE_H
#define BINARYTREE_H

class BinaryTree {
public:
    BinaryTree();
    BinaryTree* left();
    BinaryTree* right();
    char RootBT();
    //BinaryTree* consBT(char tmp);
    void printBT();
    void change();
    void createBT(std::string& tmp);
    bool IsNull();
    ~BinaryTree();

private:
    BinaryTree* l;
    BinaryTree* r;
    char data;
};

#endif