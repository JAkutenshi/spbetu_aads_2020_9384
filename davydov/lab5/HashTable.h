#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
template <class T>
class HashTable{
public:
    T *array;
    int size;

    HashTable(int size){
        this->size = size;
        this->array = new T[size];
        for(int i=0 ; i < size ; i++)
            array[i] = NULL;
    }

    void append(T data){
        int key = (int)data % size;
        if(array[key] == NULL){
            array[key] = data;
        } else{
            int oldKey = key;
            while(array[key]!=NULL){
                if(array[key] == data){
                    return;
                }
                key++;
                key%=size;
                if(oldKey == key){
                    T *tmp = new T[size+1];
                    for(int i=0;i<size;i++) {
                        tmp[i] = array[i];
                    }
                    delete[] array;
                    this->array = tmp;
                    array[size] = data;
                    size+=1;
                    return;
                }
            }
            array[key] = data;
        }
    }

    void printHashTable(){
        for(int i= 0;i<size;i++){
            cout<<i<<": ";
            if(array[i] == NULL) cout<<"NULL"<<endl;
            else cout<<array[i]<<" (ascii code "<<int(array[i])<<')'<<endl;
        }
    }
};
#endif
