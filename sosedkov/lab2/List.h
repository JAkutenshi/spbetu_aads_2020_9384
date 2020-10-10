#pragma once
#include <iostream>
using namespace std;

class List {
private:

    struct Node {
        Node() {};
        Node(char s): data(s) {};
        Node* next = nullptr;
        Node* prev = nullptr;;
        List* list = nullptr;
        char data;
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    
public:
    List(std::string listString) {
        createList(listString, this);
    }

    ~List() {
        deleteList();
    }

    void deleteList(List* lst=nullptr) {
        if(lst == nullptr) lst = this;
        Node* tmp = lst->head;
        while(tmp) {
            if(tmp->list) {
                deleteList(tmp->list);
                delete tmp->list;
            }
            tmp = tmp->next;
            delete tmp->prev;
        }
    }

    Node* createNode(List* list, Node* newNode) {
        if(!list->head) {
            list->head = newNode;
            list->tail = list->head;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        return newNode;
    }

    void createList(std::string s, List* list) {
        char symbol = readNextChar(s);

        if(symbol == ' ') return;
        else if(symbol == '(') {
            Node* newNode = createNode(list, new Node());
            newNode->list = new List(s);
        }
        else if(isalnum(symbol)) {
            createNode(list, new Node(symbol));
        }
        else if(symbol == ')') {
            return;
        }
        createList(s, list);
    }

    bool contains(char atom, List* lst = nullptr) {
        if(lst == nullptr) lst = this;
        Node* tmp = lst->head;
        while(tmp) {
            if(tmp->list && contains(atom, tmp->list)) return true;
            else if(!tmp->list && tmp->data == atom) return true;
            tmp = tmp->next;
        }
        return false;
    }

    static char readNextChar(string s) {
        static int str_size = s.size();
        static int index = 0;
        static string last_string = s;
        if(last_string != s) {
            str_size = s.size();
            index = 0;
            last_string = s;
        }
        while(s[index] == ' ' && index < str_size) {
            index++;
        }
        if(index >= str_size) return ' ';
        index++;
        return s[index-1];
    }
};