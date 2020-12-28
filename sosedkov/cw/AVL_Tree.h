#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <QDebug>
#include <QTime>
template <class T>
class AVL_Tree
{
public:
    struct AvlNode {
        AvlNode(T data) {
            this->data = data;
        }

        ~AvlNode() {
            if(left) delete left;
            if(right) delete right;
        }

        AvlNode* leftChild() const {
            return this->left;
        }

        AvlNode* rightChild() const {
            return this->right;
        }

        int balance_factor() {
            int left_height = left ? left->height : 0;
            int right_height = right ? right->height : 0;
            return left_height-right_height;
        }


        void update_height() {
            int left_heght = left ? left->height : 0;
            int right_heght = right ? right->height : 0;
            height = std::max(left_heght,right_heght)+1;
        }

        void print(int offset=0) {
            qDebug() << QString(" ").repeated(offset) << this->data << this->height;
            if(left) left->print(offset+2);
            if(right) right->print(offset+2);
        }


        T data;
        int height = 1;
        AvlNode* left = nullptr;
        AvlNode* right = nullptr;

    };



    AVL_Tree() {};

    ~AVL_Tree() {
        if(root) delete root;
    };


    int number_of_operations() const {
        return num_operations;
    }

    int elapsed_time() const {
        return m_seconds;
    }

    void clear() {
        if(root) {
            delete root;
            root = nullptr;
        }
    }

    void insert(T data) {
        num_operations = 0;
        root = insert(data, root);

    }

    void remove(T data) {
        num_operations = 0;
        root = remove(data, root);
    }

    int height() {
        if(!root) return 0;
        return root->height;
    }

    void print(int offset=0) {
        this->root->print();
    }

    AvlNode* getRoot() const {
        return root;
    }

private:
    AvlNode* insert(T data, AvlNode* node) {
        if(!node) {
            num_operations+=2;
            node = new AvlNode(data);
        }
        else if(data > node->data) {
            num_operations++;
            node->right = insert(data, node->right);
        }
        else if(data < node->data) {
            num_operations++;
            node->left = insert(data, node->left);
        }
        num_operations++;
        return balance(node);
    }

    AvlNode* remove(T data, AvlNode* node) {
        if(!node) {
            num_operations++;
            return node;
        }
        else if(data > node->data) {
            num_operations++;
            node->right = remove(data, node->right);
        }
        else if(data < node->data) {
            num_operations++;
            node->left = remove(data, node->left);
        }
        else {
            if(!node->left && !node->right) {
                num_operations+=3;
                delete node;
                node = nullptr;
                return nullptr;
            }
            else if(!node->left || !node->right) {
                num_operations+=3;
                if(node->left) {
                    node->data = node->left->data;
                    delete node->left;
                    node->left = nullptr;
                }
                else {
                    node->data = node->right->data;
                    delete node->right;
                    node->right = nullptr;
                }
            }
            else {
                num_operations+=2;
                AvlNode* tmp = min(node->right);
                node->data = tmp->data;
                node->right = remove(node->data, node->right);
            }
        }
        num_operations++;
        return balance(node);
    }


    AvlNode* min(AvlNode* node) {
        AvlNode* tmp = node;
        while (tmp->left) {
            num_operations++;
            tmp = tmp->left;
        }
        return tmp;
    }

    AvlNode* balance(AvlNode* node) {
        if(!node) return node;
        node->update_height();
        num_operations+=3;
        if(node->balance_factor() >= 2) {
            if(node->left->balance_factor() <= -1) {
                num_operations+=5;
                node->left = rotate_left(node->left);
            }
            node = rotate_right(node);
            num_operations+=5;
        }
        else if(node->balance_factor() <= -2) {
            if(node->right->balance_factor() >= 1) {
                num_operations+=5;
                node->right = rotate_right(node->right);
            }
            node = rotate_left(node);
            num_operations+=5;
        }

        node->update_height();
        num_operations+=5;
        return node;
    }


    AvlNode* rotate_right(AvlNode* node) {
        AvlNode* new_root = node->left;
        node->left = new_root->right;
        new_root->right = node;
        new_root->right->update_height();
        return new_root;
    }


    AvlNode* rotate_left(AvlNode* node) {
        AvlNode* new_root = node->right;
        node->right = new_root->left;
        new_root->left = node;
        new_root->left->update_height();
        return new_root;
    }


    AvlNode* root = nullptr;
    int num_operations = 0;
    int m_seconds = 0;

};





#endif // AVL_TREE_H
