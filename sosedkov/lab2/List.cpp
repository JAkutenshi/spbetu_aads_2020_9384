#include "List.h"

static char readNextChar(string s) {
    static int str_size = s.size();
    static int index = 0;
    static string last_string = s;
    if(last_string != s) {
        str_size = s.size();
        index = 0;
        last_string = s;
    }
    if(index >= str_size) return ' ';
    index++;
    return s[index-1];
}

List::List(std::string listString) {
    char symbol = readNextChar(listString);
    while(symbol != ' ') {
        if(symbol == ' ') return;
        else if(symbol == '(') {
            Node* newNode = createNode(new Node());
            newNode->list = new List(listString);
        }
        else if(isalnum(symbol)) {
            createNode(new Node(symbol));
        }
        else if(symbol == ')') {
            return;
        }
        symbol = readNextChar(listString);
    }
}

List::~List() {
    Node* tmp = this->head;
    while(tmp) {
        if(tmp->list) {
            delete tmp->list;
        }
        tmp = tmp->next;
        delete tmp->prev;
    }
}


Node* List::createNode(Node* newNode) {
    if(!this->head) {
        this->head = newNode;
        this->tail = this->head;
    }
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    return newNode;
}



bool List::contains(char atom, List* lst) {
    if(lst == nullptr) lst = this;
    Node* tmp = lst->head;
    while(tmp) {
        if(tmp->list && contains(atom, tmp->list)) return true;
        else if(!tmp->list && tmp->data == atom) return true;
        tmp = tmp->next;
    }
    return false;
}