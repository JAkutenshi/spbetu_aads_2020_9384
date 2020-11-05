#ifndef STACK_H
#define STACK_H

#include <cstring>

template <typename T>
class Stack{
public:
    Stack(){
        this->data = new T[this->memory];
    }

    ~Stack(){
        delete this->data;
    }

    void push(T value){
        if (count == memory){
            memory *= 2;
            T *temp = new T[memory];
            std::memcpy(temp, data, memory * sizeof(T));
            delete this->data;
            data = temp;
        }
        this->data[this->count] = value;
        this->count++;
    }

    T pop(){
        if (!this->empty())
            return this->data[--this->count];
        else
            std::cout << "Stack is empty" << std::endl;

        return (T)NULL;
    }

    T top(){
        if (!this->empty())
            return this->data[this->count - 1];
        else
            std::cout << "Stack is empty" << std::endl;

        return (T)NULL;
    }

    bool empty(){
        return this->count == 0;
    }

private:
    T *data;
    size_t count = 0;
    size_t memory = 10;
};

#endif
