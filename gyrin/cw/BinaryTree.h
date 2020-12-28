#ifndef DinamicHuffman_H
#define DinamicHuffman_H
#include <iostream>
#include <QApplication>
#include <string>

template <typename T>
class DinamicHuffman{
private:
    DinamicHuffman* right;
    DinamicHuffman* left;
    T root;
    int freq;
    int lvl = 0;

    int GetFreq(){
        return this->freq;
    }
    DinamicHuffman* GetLeftSon(){
        return this->left;
    }

    void AddNode(T letter, int count){
        this->left = new DinamicHuffman();
        this->right = new DinamicHuffman(letter, count);
        this->root;
        this->freq++;
    }
    void CompareLetter(QChar letter, int count, bool& a){
        count++;
        if (this->left != nullptr && a == true){
            this->left->CompareLetter(letter, count, a);
        }
        if (this->right != nullptr){
            this->right->CompareLetter(letter, count, a);
        }
        if (this->root == letter&& a == true){
            this->freq++;
            a = false;
            return;

        }
        if (this->root == NULL && this->left == nullptr && this->right == nullptr && a == true){
            this->AddNode(letter, count);
            return;
        }
    }

    void UpdateFreq(){
        if (this->left != nullptr){
            this->left->UpdateFreq();
        }
        if (this->right != nullptr){
            this->right->UpdateFreq();
        }
        if (this->right != nullptr && this->left != nullptr){
            this->freq = this->right->GetFreq() + this->left->GetFreq();
        }
    }

    void ChangeNodes(){

        if (this->left != nullptr){
            this->left->ChangeNodes();
        }
        if (this->right != nullptr){
            this->right->ChangeNodes();
        }
        if ((this->right != nullptr) && (this->left != nullptr) && (this->left->GetFreq() > this->right->GetFreq())){
            DinamicHuffman* tmp = new DinamicHuffman();
            tmp = this->left;
            this->left = this->right;
            this->right = tmp;
        }
    }

    void NumReverseOrder(){
        int max = 1;
        CountOfLevels(max);
        int* lvl_count = new int[max-1];
        for (int i = 0; i < max; i++) lvl_count[i] = 0;
        CountOnLevels(lvl_count, max);
        int x = lvl_count[max];
    }

    void CountOfLevels(int& max){
        if (this->left != nullptr){
            this->left->CountOfLevels(max);
        }
        if (this->right != nullptr){
            this->right->CountOfLevels(max);
        }
        if (this->lvl > max){
            max = this->lvl;
        }
    }

    void CountOnLevels(int lvl_count[], int max){
        for (int i = 0; i < max; i++){
            if (this->left != nullptr) {
                this->left->CountOnLevels(lvl_count, max);
            }
            if (this->right != nullptr) {
                this->right->CountOnLevels(lvl_count, max);
            }
            if (this->lvl == i++) {
                lvl_count[i]++;
            }
        }
    }

public:
    DinamicHuffman(){
        this->left = nullptr;
        this->right = nullptr;
        this->root;
        this->freq = 0;
    };

    DinamicHuffman(T letter, int count){
        this->left = nullptr;
        this->right = nullptr;
        this->freq = 1;
        this->root = letter;
        count+=this->lvl;
        this->lvl = count;

    }

    void MakeTree(QString text){
    int count = 0;
        while (text.size() !=0){
            bool a = true;
            CompareLetter(text[0],count,a);
            NumReverseOrder();
            UpdateFreq();
//            ChangeNodes();
            text.remove(0,1);
        }
    }

};
#endif
