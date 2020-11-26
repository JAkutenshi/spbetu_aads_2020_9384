#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "HashTable.h"
using namespace std;

HashTable<char> generate(int size){
    HashTable<char> tmp(size);
    srand (time(NULL));
    char characters[] = "abcdefghijklmnopqrstuvwxyz";
    char c;
    cout<<"Random characters:"<<endl;
    for(int i = 0; i<size; i++){
        c = characters[rand() % 26];
        cout<<c<<' ';
        tmp.append(c);
    }
    cout<<"\n";
    return tmp;
}



int main() {
    cout<<"Choose how to create hash table with encoded symbols, there codes - array index:\n1 - create it randomly (from a to z)\n2 - input it manually now"<<endl;
    char c1;
    cin>>c1;

    cout<<"Enter size of hash table:"<<endl;
    int c2;
    cin>>c2;
    getchar();
    HashTable<char> table(c2);

    switch(c1){
        case '1': table = generate(c2); break;
        case '2':
            cout<<"Enter your symbols like this a b c..."<<endl;
            c1 ='\0';
            while(c1!='\n'){
                scanf("%c",&c1);
                if(c1==' ') continue;
                else if(c1 =='\n') break;
                else table.append(c1);
            }
            break;
        default: cout<<"You haven't chose anything"<<endl; return 1;
    }
    cout<<"Your hash table:"<<endl;
    table.printHashTable();

    cout<<"Choose how to enter text:\n1 - from file\n2 - from console"<<endl;
    c1 = '\0';
    cin>>c1;
    getchar();
    c2 = '\0';
    switch(c1){
        case '1':{
            string filePathIn;
            cout<< "Enter input file:"<<endl;
            cin>>filePathIn;
            ifstream in;
            in.open(filePathIn);
            if(!in.is_open()){
                cerr<<"No such file"<<endl;
                return 2;
            }
            cout<<"Decoded text:"<<endl;
            while(in>>c2){
                if(c2 < table.size && c2 >= 0 && table.array[c2] != NULL){
                    cout<<table.array[c2]<<' ';
                } else cout<<"NONE ";
            }
            cout<<'\n';
            break;
        }
        case '2':{
            int size;
            cout<<"How many elements you will enter?\nP.S. Decoded text will be printed print after your codes"<<endl;
            cin>>size;
            c2 = '\0';
            for(int i = 0;i<size;i++){
                scanf("%d",&c2);
                if(c2 < table.size && c2 >= 0 && table.array[c2] != NULL){
                    cout<<table.array[c2]<<' ';
                } else cout<<"NONE ";
            }
            cout<<'\n';
            break;
        }
        default: cout<<"You haven't chose anything"<<endl; break;
    }
    return 0;
}