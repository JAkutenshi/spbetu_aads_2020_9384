#pragma once
#include <stdlib.h>
#include <iostream>
#include "Coder.h"

int count = 0;

template <typename P>
class List{
private:
    void Pop() {
        Node* tmp = Head->Next;
        delete Head;
        Head = tmp;
        count--;
    }

    void Add(P x) {
        Node* temp = new Node;
        temp->Next = NULL;
        temp->x = x;
        count++;

        if (Head != NULL)
        {
            temp->Prev = Tail;
            Tail->Next = temp;
            Tail = temp;
        }
        else
        {
            temp->Prev = NULL;
            Head = Tail = temp;
        }
    }

    void SortNodes() {
        Node* left = Head;
        Node* right = Head->Next;
        Node* temp = new Node;
        while (left->Next) {
            while (right) {
                if ((left->x->GetFreq()) < (right->x->GetFreq())) {
                    temp->x = left->x;
                    left->x = right->x;
                    right->x = temp->x;
                }
                right = right->Next;
            }
            left = left->Next;
            right = left->Next;
        }
    }

public:
    struct Node {
        P x;
        Node* Next, * Prev;
    };
    Node* Head, * Tail;

    List() {
        this->Head = NULL;
        this->Tail = NULL;
    };
    
    int GetCount() {
        return count;
    }

    void _Pop() {
        Pop();
        Pop();
    }

    void _Add(P(x)) {
        Add(x);
    }

    void _SortNodes() {
        SortNodes();
    }
};
