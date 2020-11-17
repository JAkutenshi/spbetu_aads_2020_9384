#ifndef NODE_H
#define NODE_H

template <typename T>
class TreeNode{
    friend class Tree<T>;
public:
    TreeNode(T);
    ~TreeNode();
    T get_data();

protected:
    void print_tree(int = 0);
    void write_tree(std::ofstream&);

protected:
    T data;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
};

template <typename T>
TreeNode<T>::TreeNode(T data) : data(data), parent(nullptr), left(nullptr), right(nullptr) {}

template <typename T>
T TreeNode<T>::get_data(){
    return data;
}

template <typename T>
void TreeNode<T>::print_tree(int level){
    if(this->left){
        this->left->print_tree(level+1);
    }

    for(int i = 0; i < level; i++){
        std::cout << '\t';
    }
    std::cout << this->data << std::endl;
    
    if(this->right){
        this->right->print_tree(level+1);
    }
}

template <typename T>
void TreeNode<T>::write_tree(std::ofstream &file){
    if(this->left){
        this->left->write_tree(file);
    }
    file << this->data << " ";
    if(this->right){
        this->right->write_tree(file);
    }
}

#endif