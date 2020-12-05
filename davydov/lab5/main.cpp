#include <iostream>
#include <string>
#include "HashTable.h"
#include <fstream>

int main(){

    HashTable<string> table;
    cout<<R"(Enter your elements like this: "hash code" space "information", example: 1101 cat 1000 dog)"<<endl;
    table.readElements();
    cout<<"Your hashTable:"<<endl;
    table.printElements();

    cout<<"Choose how to enter encoded information:\n1 - from console\n2 - from file"<<endl;
    char c;
    cin>>c;
    getchar();
    switch(c){
        case '1': {
            cout<<"Enter your information:"<<endl;
            string text;
            string search;
            cin>>text;
            for(int i = 0;i<text.size();i++){
                search.push_back(text[i]);
                if(table.check(search)){
                    table.decode(search);
                    search = "";
                }
            }
            break;
        }
        case '2': {
            string filename;
            string search;
            string text;
            cout<<"Enter file name"<<endl;
            cin>>filename;
            ifstream in;
            in.open(filename);

            if(!in.is_open()){
                cerr<<"No such file"<<endl;
                return 2;
            }

            cout<<"Decoded text:"<<endl;
            getline(in,text);
            for(int i = 0;i<text.size();i++){
                search.push_back(text[i]);
                if(table.check(search)){
                    table.decode(search);
                    search = "";
                }
            }
            break;
        }
        default: cout<<"You haven't chose anything"<<endl; return 1;
    }
}
