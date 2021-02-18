#ifndef STATIC_ENCODE_H
#define STATIC_ENCODE_H
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <QChar>
#include <QString>

std::vector<bool> temp_values;

//int count = 0;

template <typename P>
class List {
private:
    void Pop(int &count) {
        Node* tmp = Head->Next;
        delete Head;
        Head = tmp;
        count--;
    }

    void Add(P x, int& count) {
        Node* temp = new Node;
        temp->Prev = 0;
        temp->x = x;
        temp->Next = Head;
        if (Head != 0)
            Head->Prev = temp;
        if (count == 0)
            Head = Tail = temp;
        else
            Head = temp;
        count++;
    }

    void SortNodes() {
        Node* left = Head;
        Node* right = Head->Next;
        Node* temp = new Node;
        while (left->Next) {
            while (right) {
                if ((left->x->GetFreq()) > (right->x->GetFreq())) {
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

    int GetCount(int& count) {
        return count;
    }

    void _Pop(int& count) {
        Pop(count);
        Pop(count);
    }

    void _Add(P(x), int& count) {
        Add(x, count);
    }

    void _SortNodes() {
        SortNodes();
    }
};

/////////////////////////////////////////////////////////

template <typename T>
class Coder {
public:
    int freq;
    T root;
    Coder* zero;
    Coder* one;

    Coder() {
        this->freq = 0;
        this->root;
        this->zero = nullptr;
        this->one = nullptr;
    }

    Coder(Coder* Left, Coder* Right) {
        this->zero = Left;
        this->one = Right;
        this->freq = Left->GetFreq() + Right->GetFreq();
    }

    struct priority {
        int count = 0;
        char letter;
    };

    struct CodedValue {
        std::vector<bool> code;
        char letter;
    };

    int GetFreq() {
        return this->freq;
    }

    Coder* GetZero() {
        return this->zero;
    }

    Coder* GetOne() {
        return this->one;
    }

    T GetRoot() {
        return this->root;
    }

    void MakeNodes(priority prior[], int amount, List<Coder*>& ptr, int& count) {//
        for (int i = 0; i < amount; i++) {
            Coder* p = new Coder;
            p->root = prior[i].letter;
            p->freq = prior[i].count;
            ptr._Add(p, count);
        }
    }

    int CountOfLetters(std::string tmp) {//
        int arr[95] = { 0 };
        CountingPriority(tmp, arr);
        int amount = 0;
        for (int i = 0; i < 95; i++)
        {
            if (arr[i] != 0) {
                amount++;
            }
        }
        return amount;
    }

    void Huffman(List<Coder*>& ptr, int& count) {//сборка дерева
        if (ptr.GetCount(count) != 1) {
            ptr._SortNodes();
            Coder* Left = ptr.Head->x;
            Coder* Right = ptr.Head->Next->x;
            ptr._Pop(count);
            Coder* p = new Coder(Left, Right);
            ptr._Add(p, count);
            Huffman(ptr, count);
        }
    }

    void MakePriority(priority prior[], std::string tmp, int amount) {//
        for (int i = 0; i < amount; i++) {
            prior[i].letter = tmp[0];
            prior[i].count = Count(prior[i].letter, tmp);
            DeleteLeter(prior[i].letter, tmp);
        }
        Sort(prior, amount);
    }

    void WriteCodedValue(Coder<char>* Tree, CodedValue code[], int& index_1) {//
        if (Tree->GetZero() != NULL) {
            temp_values.push_back(0);
            WriteCodedValue(Tree->GetZero(), code, index_1);
        }
        if (Tree->GetOne() != NULL) {
            temp_values.push_back(1);
            WriteCodedValue(Tree->GetOne(), code, index_1);
        }
        if (Tree->GetZero() == NULL && Tree->GetOne() == NULL) {
            code[index_1].letter = Tree->GetRoot();
            code[index_1].code = temp_values;
            index_1++;
        }
        if (!temp_values.empty()) {
            temp_values.pop_back();
        }
    }

private:
    void CountingPriority(std::string tmp, int arr[]) {
        for (size_t i = 0; i < tmp.size(); i++)
        {
            arr[(int)tmp[i] - 32]++;
        }
    }


    void DeleteLeter(char letter, std::string& tmp) {
        for (size_t i = 0; i <= tmp.length(); i++) {
            if (tmp[i] == letter) {
                tmp.erase(i, 1);
                i--;
            }
        }
    }

    int Count(char letter, std::string tmp) {
        int count = 0;
        for (size_t i = 0; i <= tmp.length(); i++) {
            if (tmp[i] == letter) {
                count++;
            }
        }
        return count;
    }

    void Sort(priority prior[], int amount) {
        int temp1;
        char temp2;
        for (int i = 0; i < amount - 1; i++) {
            for (int j = 0; j < amount - i - 1; j++) {
                if (prior[j].count > prior[j + 1].count) {
                    temp1 = prior[j].count;
                    temp2 = prior[j].letter;
                    prior[j].count = prior[j + 1].count;
                    prior[j].letter = prior[j + 1].letter;
                    prior[j + 1].count = temp1;
                    prior[j + 1].letter = temp2;
                }
            }
        }
    }
};
#endif
