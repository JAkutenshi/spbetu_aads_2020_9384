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
            c = '\0';
            string search;
            while (c != '\n') {
                cin >> search;
                table.decode(search);
                c = getchar();
            }
            cout << '\n';
            break;
        }
        case '2': {
            c = '\0';
            string filename;
            string search;
            cout<<"Enter file name"<<endl;
            cin>>filename;
            ifstream in;
            in.open(filename);

            if(!in.is_open()){
                cerr<<"No such file"<<endl;
                return 2;
            }

            cout<<"Decoded text:"<<endl;
            while(in>>search){
                table.decode(search);
            }
            cout<<'\n';
            break;
        }
        default: cout<<"You haven't chose anything"<<endl; return 1;
    }
}
