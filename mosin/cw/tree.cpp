#include "tree.h"

Tree::Tree(int data) : data(data), size(1), left(nullptr), right(nullptr), radius(50), op_count(0) {}

//Tree::~Tree(){
//    'if(left){
//        delete left;
//    }
//    if(right){
//        delete right;
//    }'
//}

Tree* Tree::insert(Tree *ptr, int data){
    if (!ptr){
        op_count++;
        return new Tree(data);
    }
    if (rand() % (ptr->size + 1) == 0){
        return insert_root(ptr, data);
    }
    if (ptr->data > data){
        op_count++;
        ptr->left = insert(ptr->left, data);
    }
    else{
        op_count++;
        ptr->right = insert(ptr->right, data);
    }
    update_size(ptr);
    return ptr;
}

Tree* Tree::get_left(){
    return left;
}

Tree* Tree::get_right(){
    return right;
}

int Tree::get_depth(Tree *tree){
    if(tree){
        int lchild = get_depth(tree->get_left());
        int rchild = get_depth(tree->get_right());
        if(lchild <= rchild){
            return rchild + 1;
        }
        else{
            return lchild + 1;
        }
    }
    else{
        return 0;
    }
}

int Tree::get_operation_count(Tree *tree){
    if(tree){
        return op_count+get_operation_count(tree->get_left())+get_operation_count(tree->get_right());
    }
    else{
        return 0;
    }
}

float Tree::average_find_time(Tree *, float){
    ;
}

float Tree::worst_find_time(Tree *, float){
    ;
}

QRectF Tree::boundingRect() const{
    return QRect(0,0,radius,radius);
}

void Tree::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
        painter->drawEllipse(boundingRect());
        painter->drawText(boundingRect().center(), QString::number(data));
    }

Tree* Tree::insert_root(Tree *ptr, int data){
    if (!ptr){
        op_count++;
        return new Tree(data);
    }
    if (ptr->data > data){
        op_count+=2;
        ptr->left = insert_root(ptr->left, data);
        update_size(ptr);
        return rotate_right(ptr);
    }
    else{
        op_count+=2;
        ptr->right = insert_root(ptr->right, data);
        update_size(ptr);
        return rotate_left(ptr);
    }
}

Tree* Tree::rotate_right(Tree* ptr){
    Tree* temp = ptr->left;
    if (!temp){
        return ptr;
    }
    ptr->left = temp->right;
    temp->right = ptr;
    temp->size = ptr->size;
    update_size(ptr);
    return temp;
}

Tree* Tree::rotate_left(Tree* ptr){
    Tree* temp = ptr->right;
    if (!temp){
        return ptr;
    }
    ptr->right = temp->left;
    temp->left = ptr;
    temp->size = ptr->size;
    update_size(ptr);
    return temp;
}

int Tree::get_size(Tree* ptr){
    if (!ptr){
        return 0;
    }
    return ptr->size;
}

void Tree::update_size(Tree* ptr){
    ptr->size = get_size(ptr->left) + get_size(ptr->right) + 1;
}
