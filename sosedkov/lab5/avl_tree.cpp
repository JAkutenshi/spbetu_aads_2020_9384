#include "avl_tree.h"

AVL_Tree::AVL_Tree() {

}


bool AVL_Tree::insert(T data) {
    if(!this->left && !this->right) {
        this->value = data;
        return true;
    }

    if(this->value == data) {
        return false;
    }

    if(data < this->value) {
        if(!this->left) {
            this->left = new AVL_Tree();
        }
        left->insert(data);
    }

    if(data > this->value) {
        if(!this->right) {
            this->right = new AVL_Tree();
        }
        right->insert(data);
    }
}
