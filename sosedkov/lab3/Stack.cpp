#include "Stack.h"
#include <iostream>

Stack::Stack() {}

Stack::~Stack() {
    if(head) {
        Node* tmp = head;
        while (tmp){
            delete tmp;
            tmp = tmp->next;
        }
    }
}

void Stack::push(char value) {
    length++;
    Node* newNode = new Node;
    newNode->data = value;
    if(!head) {
        head = newNode;
        tail = head;
        
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

}

char Stack::pop() {
    char value = tail->data;
    if(this->isEmpty()) {
       delete this;
       throw std::runtime_error("Stack::pop() stack is empty");
    }
    if(this->size() == 1) {
        delete tail;
        length--;
        return value;
    }

    length--;
    tail->prev->next = nullptr;
    Node* tmp = tail->prev;
    delete tail;
    tail = tmp;
    return value;
}

bool Stack::isEmpty() {
    return length == 0;
}

int Stack::size() {
    return length;
}

char Stack::top() {
    return tail->data;
}

void Stack::print() {
    Node* tmp = tail;
    std::cout << "Stack--------------------\n";
    while(tmp) {
        std::cout << tmp->data << "\n";
        tmp = tmp->prev;
    }
    std::cout << "-------------------------\n";
}
