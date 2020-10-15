#pragma once

class Stack
{
private:
    struct Node {
        Node* next = nullptr;
        Node* prev = nullptr;;
        char data;
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int length = 0;
public:
    Stack();
    ~Stack();
    void push(char value);
    char pop();
    bool isEmpty();
    int size();
    char top();
    void print();
};