#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

template < typename Data >
class BinaryTree{
public:
    BinaryTree(Data data, BinaryTree *leftNode, BinaryTree *rightNode){
        this->data = data;
        this->leftNode = leftNode;
        this->rightNode = rightNode;
    }
    
    ~BinaryTree(){
        if(!this->getLeftNode()->isNullBinaryTree())
            this->getLeftNode()->~BinaryTree();
        if(!this->getRirghtNode()->isNullBinaryTree())
            this->getRirghtNode()->~BinaryTree();
        if(!this->isNullBinaryTree())
        delete this;
    }
    
    void printBinaryTree(){
        if(!this->isNullBinaryTree()){
            std::cout << this->getRootBinaryTree();
            this->getLeftNode()->printBinaryTree();
            this->getRirghtNode()->printBinaryTree();
        }
    }

    bool isNullBinaryTree(){
        return this == nullptr;
    }

    Data getRootBinaryTree(){
        if(this->isNullBinaryTree()){
            error(1);
            return (Data)NULL;
        }
        else
            return this->data;
    }

    BinaryTree *getLeftNode(){
        if(this->isNullBinaryTree()){
            error(2);
            return nullptr;
        }
        else
            return this->leftNode;
    }

    BinaryTree *getRirghtNode(){
        if(this->isNullBinaryTree()){
            error(3);
            return nullptr;
        }
        else
            return this->rightNode;
    }

    bool isNode(){
        if(this->getLeftNode()->isNullBinaryTree() && this->getRirghtNode()->isNullBinaryTree())
            return false;
        return true;
    }

    void error(unsigned int err){
        switch(err){
            case 1:
                std::cout << "ERROR: IMPOSSIBLE TO GET ROOT - TREE IS NULL" << std::endl;
                break;
            case 2:
                std::cout << "ERROR: IMPOSSIBLE TO GET LEFT NODE - TREE IS NULL" << std::endl;
                break;
            case 3:
                std::cout << "ERROR: IMPOSSIBLE TO GET RIGHT NODE - TREE IS NULL" << std::endl;
                break;
            default:
                std::cout << "ERROR: SOMETHING WRONG" << std::endl;
        }
    }

private:
    Data data;
    BinaryTree *leftNode;
    BinaryTree *rightNode;
};

#endif