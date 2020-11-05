#ifndef BT_H
#define BT_H

template <class T>
class BT{
public:
    BT() {}

    BT(T data) {
        this->data = data;
    }

    ~BT() {
        if(left)
            delete left;
        if(right)
            delete right;
    }

    T returnData() {
        return data;
    }

    int height() {
        int left_h = 0;
        int right_h = 0;
        if(this->left)
            left_h = left->height();
        if(this->right)
            right_h = right->height();
        return left_h>right_h? left_h+1 : right_h+1;
    }
    BT* left = nullptr;
    BT* right = nullptr;
private:
    T data;
};

#endif // BT_H
