#pragma once
#include <iostream>
using namespace std;

struct Node;

class List {
private:

    Node* head = nullptr;
    Node* tail = nullptr;
    Node* createNode(Node* newNode);

public:
    List(std::string listString);
    ~List();
    bool contains(char atom, List* list=nullptr);
};


struct Node {
    Node() {};
    Node(char s): data(s) {};
    Node* next = nullptr;
    Node* prev = nullptr;;
    List* list = nullptr;
    char data;
};
