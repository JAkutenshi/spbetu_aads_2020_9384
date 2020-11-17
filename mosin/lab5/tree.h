#ifndef TREE_H
#define TREE_H

template <typename T> class Tree;
#include "node.h"

template <typename T>
class Tree{
public:
    Tree();
    void insert_node(T);
    void render_node();
    void write_node(std::string path);

private:
    TreeNode<T> *root;
};

template <typename T>
Tree<T>::Tree() : root(nullptr) {}

template <typename T>
void Tree<T>::insert_node(T data){
    TreeNode<T> *node = new TreeNode<T>(data);
    TreeNode<T> *ptr = this->root;
    TreeNode<T> *temp = nullptr;

    while(ptr){
        temp = ptr;
        if(data < ptr->get_data()){
            ptr = ptr->left;
        }
        else{
            ptr = ptr->right;
        }
    }
    node->parent = temp;
    
    if(!temp){
        this->root = node;
    }
    else if(data < temp->get_data()){
        temp->left = node;
    }
    else{
        temp->right = node;
    }
}

template <typename T>
void Tree<T>::render_node(){
    if(this->root){
        this->root->print_tree();
    }
    else{
        std::cout << "NULL" << std::endl;
    }
}

template <typename T>
void Tree<T>::write_node(std::string path){
    if(this->root){
        std::ofstream file(path, std::ios::app);
        if(file.is_open()){
            this->root->write_tree(file);
            file << std::endl;
        }
        else{
            std::cout << "file " << path << " could not open" << std::endl;
        }
    }
}

#endif