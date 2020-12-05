#ifndef UNTITLED12_HASHTABLE_H
#define UNTITLED12_HASHTABLE_H
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

template <class T>
class HashTable{
private:
    struct linkedList{
        T data;
        string hash;
        linkedList* next;
        bool exist = true;
    };

    linkedList* array;
    int size = 0;
    int capacity;
    const float resizeOdd = 0.75;
public:
    int HashFunction2(string &hash){
        int n = stoi(hash);
        hash = std::to_string(n);
        int key = 0, i = 0, remainder;
        while (n != 0) {
            remainder = n % 10;
            n /= 10;
            key += remainder * pow(2, i);
            ++i;
        }
        return key % capacity;
    }

    int HashFunction1(string hash){
        int key = 0;
        for(size_t i = 0;i<hash.size();i++){
            key+=int(hash[i]);
        }
        return key%capacity;
    }

    HashTable(int capacity = 8){
        this->capacity = capacity;
        this->array = new linkedList[capacity];
        for(int i=0 ; i < capacity ; i++)
            array[i].exist = false;
    }

    void append(T data, string hash){

        if(size>= int(resizeOdd*capacity)) resize();

        int key = HashFunction2(hash);

        if(!array[key].exist){
            array[key].data = data;
            array[key].hash = hash;
            array[key].exist = true;
            array[key].next = nullptr;
            size+=1;
        } else {
            linkedList* newNode = new linkedList;
            linkedList* tmp = &array[key];
            newNode->data = data;
            newNode->hash = hash;
            newNode->next = nullptr;
            if(tmp->hash==hash){ tmp->data = data; return;}//если первый элемент будет иметь тот же хэш код, что и новый
            while(tmp->next!= nullptr){
                tmp = tmp->next;
                if(tmp->hash==hash){
                    tmp->data = data;
                    return;
                }
            }
            tmp->next = newNode;
            size+=1;
        }
    }

    void readElements(){
        string tmpHash;
        T tmpData;
        char c;
        while(c!='\n'){
            cin>>tmpHash>>tmpData;
            this->append(tmpData,tmpHash);
            c = getchar();
        }
    }

    void resize(){
        int pastSize = capacity;
        capacity*=2;
        HashTable tmp2(capacity);
        linkedList *tmp1;
        for(int i = 0;i<pastSize;i++){
            if(array[i].exist) {
                tmp2.append(array[i].data, array[i].hash);
                tmp1 = &array[i];
                while (tmp1->next != nullptr) {
                    tmp1 = tmp1->next;
                    tmp2.append(tmp1->data, tmp1->hash);
                }
            }
        }

        swap(array,tmp2.array);
    }

    void decode(string hash2){
        int key = HashFunction2(hash2);
        if(array[key].hash == hash2){ cout<<array[key].data<< ' '; return;}
        linkedList* tmp2 = &array[key];
        while(tmp2->next!=nullptr){
            tmp2 = tmp2->next;
            if(tmp2->hash==hash2){  cout<<tmp2->data<< ' '; return;}
        }
        cout<<"NONE ";
    }

    void printElements(){
        linkedList* tmp = array;
        for(int i = 0;i<capacity;i++){
            cout<<"|"<<i<<"| -> ";
            if(tmp[i].exist) cout<<tmp[i].hash<<" : "<<tmp[i].data;
            else {cout<<"NULL"<<endl; continue;}
            linkedList* tmp2 = &tmp[i];
            while(tmp2->next!=nullptr){
                tmp2 = tmp2->next;
                cout<<" -> "<<tmp2->hash<<" : "<<tmp2->data;
            }
            cout<<"\n";
        }
    }
};
#endif
