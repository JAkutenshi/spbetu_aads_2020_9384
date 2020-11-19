#ifndef TREE_H
#define TREE_H

template <typename T>
class Tree{
public:
    Tree(T);
    ~Tree();
    Tree<T> *insert(Tree<T> *, T);
    void print(int = 0);
    void write(std::ofstream &);

private:
    Tree<T> *insert_root(Tree<T> *, T);
    Tree<T> *rotate_right(Tree<T> *);
    Tree<T> *rotate_left(Tree<T> *);
    int get_size(Tree<T> *);
    void update_size(Tree<T> *);

private:
    T data;
    int size;
    Tree<T> *left;
    Tree<T> *right;
};

template <typename T>
Tree<T>::Tree(T data) : data(data), size(1), left(nullptr), right(nullptr) {}

template <typename T>
Tree<T>::~Tree(){
    if(left){
        delete left;
    }
    if(right){
        delete right;
    }
}

template <typename T>
Tree<T> *Tree<T>::insert(Tree<T> *ptr, T data){
    static bool print = true;
    if (!ptr){
        std::cout << "create new node, value: " << data << std::endl;
        return new Tree<T>(data);
    }
    if (rand() % (ptr->size + 1) == 0){
        std::cout << "input: " << data << ", action - random with " << (float)1/(ptr->size + 1)*100 << "%" << std::endl;
        return insert_root(ptr, data);
    }
    if (ptr->data > data){
        std::cout << "input: " << data << ", current value in tree: " << ptr->data << ", action - left" << std::endl;
        print = true;
        ptr->left = insert(ptr->left, data);
    }
    else{
        std::cout << "input: " << data << ", current value in tree: " << ptr->data << ", action - right" << std::endl;
        print = true;
        ptr->right = insert(ptr->right, data);
    }
    update_size(ptr);
    if(print){
        std::cout << "tree appearance:" << std::endl;
        this->print();
        print = false;
    }
    return ptr;
}

template <typename T>
void Tree<T>::print(int level){
    if (left){
        left->print(level + 1);
    }
    for (int i = 0; i < level; i++){
        std::cout << '\t';
    }
    std::cout << data << ',' << size << std::endl;
    if (right){
        right->print(level + 1);
    }
}

template <typename T>
void Tree<T>::write(std::ofstream &file){
    if (left){
        left->write(file);
    }
    file << data << " ";
    if (right){
        right->write(file);
    }
}

template <typename T>
Tree<T> *Tree<T>::insert_root(Tree<T> *ptr, T data){
    if (!ptr){
        std::cout << "create new node, value: " << data << std::endl;
        return new Tree<T>(data);
    }
    if (ptr->data > data){
        std::cout << "input: " << data << ", current value in tree: " << ptr->data << ", action - left" << std::endl;
        ptr->left = insert_root(ptr->left, data);
        update_size(ptr);
        return rotate_right(ptr);
    }
    else{
        std::cout << "input: " << data << ", current value in tree: " << ptr->data << ", action - right" << std::endl;
        ptr->right = insert_root(ptr->right, data);
        update_size(ptr);
        return rotate_left(ptr);
    }
}

template <typename T>
Tree<T> *Tree<T>::rotate_right(Tree<T> *ptr){
    Tree<T> *temp = ptr->left;
    if (!temp){
        return ptr;
    }
    ptr->left = temp->right;
    temp->right = ptr;
    temp->size = ptr->size;
    update_size(ptr);
    std::cout << "right rotation:" << std::endl;
    temp->print();
    return temp;
}

template <typename T>
Tree<T> *Tree<T>::rotate_left(Tree<T> *ptr){
    Tree<T> *temp = ptr->right;
    if (!temp){
        return ptr;
    }
    ptr->right = temp->left;
    temp->left = ptr;
    temp->size = ptr->size;
    update_size(ptr);
    std::cout << "left rotation:" << std::endl;
    temp->print();
    return temp;
}

template <typename T>
int Tree<T>::get_size(Tree<T> *ptr){
    if (!ptr){
        return 0;
    }
    return ptr->size;
}

template <typename T>
void Tree<T>::update_size(Tree<T> *ptr){
    ptr->size = get_size(ptr->left) + get_size(ptr->right) + 1;
}

#endif
