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
    TreeNode<T>* insert(TreeNode<T> *, T data);
    TreeNode<T>* insert_root(TreeNode<T>*, T data);
    TreeNode<T>* rotate_left(TreeNode<T> *);
    TreeNode<T>* rotate_right(TreeNode<T> *);
    T get_size(TreeNode<T>*);
    int update_size(TreeNode<T>*);

private:
    TreeNode<T> *root;
};

template <typename T>
Tree<T>::Tree() : root(nullptr) {}

template <typename T>
void Tree<T>::insert_node(T data){
    this->root = insert(this->root, data);
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

template <typename T>
TreeNode<T>* Tree<T>::insert(TreeNode<T>* root, T data){
    if(!root){
        return new TreeNode<T>(data);
    }
    if(rand()%(root->size+1) == 0){
        return insert_root(root, data);
    }
    if(root->data > data){
        root->left = insert(root->left, data);
    }
    else{
        root->right = insert(root->right, data);
    }
    root->size = update_size(root);
    return root;
}

template <typename T>
TreeNode<T>* Tree<T>::insert_root(TreeNode<T>* root, T data){
    if(!root){
        return new TreeNode<T>(data);
    }
    if(data < root->data){
        root->left = insert_root(root->left, data);
        return rotate_right(root);
    }
    else{
        root->right = insert_root(root->right, data);
        return rotate_left(root);
    }
}

template <typename T>
TreeNode<T>* Tree<T>::rotate_left(TreeNode<T>* ptr){
    TreeNode<T>* temp = ptr->right;
    if(!temp){
        return ptr;
    }
    ptr->right = temp->left;
    temp->left = ptr;
    temp->size = ptr->size;
    ptr->size = update_size(ptr);
    return temp;
}

template <typename T>
TreeNode<T>* Tree<T>::rotate_right(TreeNode<T>* ptr){
    TreeNode<T>* temp = ptr->left;
    if(!temp){
        return ptr;
    }
    ptr->left = temp->right;
    temp->right = ptr;
    temp->size = ptr->size;
    ptr->size = update_size(ptr);
    return temp;
}

template <typename T>
T Tree<T>::get_size(TreeNode<T>* root){
    if(!root){
        return 0;
    }
    return root->size;
}

template <typename T>
int Tree<T>::update_size(TreeNode<T>* root){
    return get_size(root->left) + get_size(root->right) + 1;
}

#endif
