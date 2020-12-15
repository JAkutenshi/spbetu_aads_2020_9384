#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "List.h"
template <typename T>
class Coder {
public:
	Coder() {
		this->freq = 0;
		this->root = NULL;
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
		char letter = NULL;
	};

	struct CodedValue {
		std::vector<bool> code;
		char letter = NULL;
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

    void _MakeNodes(priority prior[], int amount, List<Coder*>& ptr) {
        MakeNodes(prior, amount, ptr);
    }

	void _Huffman(List<Coder*>& ptr) {
		Huffman(ptr);
	}

    int _CountOfLetters(std::string tmp){
        return CountOfLetters(tmp);
    }

    void _MakePriority(priority prior[], std::string tmp, int amount) {
        MakePriority(prior, tmp, amount);
    }

    void _WriteCodedValue(Coder<char>* Tree, CodedValue code[]) {
        WriteCodedValue(Tree, code);
    }

private:
	int freq;
	T root;
	Coder* zero;
	Coder* one;

    void MakeNodes(priority prior[], int amount, List<Coder*>& ptr) {
        for (int i = 0; i < amount; i++) {
            Coder* p = new Coder;
            p->root = prior[i].letter;
            p->freq = prior[i].count;
            ptr._Add(p);
        }
    }

	void Huffman(List<Coder*>& ptr) {
		if (ptr.GetCount() != 1) {
			ptr._SortNodes();
			Coder* Left = ptr.Head->x;
			Coder* Right = ptr.Head->Next->x;
			ptr._Pop();
			Coder* p = new Coder(Left, Right);
			ptr._Add(p);
			Huffman(ptr);
		}
	}

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

    int CountOfLetters(std::string tmp) {
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

    void MakePriority(priority prior[], std::string tmp, int amount) {
        for (int i = 0; i < amount; i++) {
            prior[i].letter = tmp[0];
            prior[i].count = Count(prior[i].letter, tmp);
            DeleteLeter(prior[i].letter, tmp);
        }
        Sort(prior, amount);
    }

    int index_1 = 0;
    std::vector<bool> temp;

    void WriteCodedValue(Coder<char>* Tree, CodedValue code[]) {
        if (Tree->GetZero() != NULL) {
            temp.push_back(0);
            WriteCodedValue(Tree->GetZero(), code);
        }
        if (Tree->GetOne() != NULL) {
            temp.push_back(1);
            WriteCodedValue(Tree->GetOne(), code);
        }
        if (Tree->GetZero() == NULL && Tree->GetOne() == NULL) {
            code[index_1].letter = Tree->GetRoot();
            code[index_1].code = temp;
            index_1++;
            temp.pop_back();
        }
    }

};