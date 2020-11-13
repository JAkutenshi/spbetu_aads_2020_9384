#ifndef BINARYTREE_H
#define BINARYTREE_H

template <class base>
class BinaryTree {
public:
    BinaryTree();
    base RootBT();
    void printBT();
    void change();
    void createBT(std::string& tmp);
    bool IsNull();
    ~BinaryTree();

private:
    BinaryTree* l;
    BinaryTree* r;
    base data;
};

#endif