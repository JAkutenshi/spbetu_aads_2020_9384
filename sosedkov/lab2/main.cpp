#include <iostream>
#include <string>
#include <fstream>
#include <algorithm> //std::remove
#include "List.h"

using namespace std;

std::string input();
bool isValid(std::string listString);
string readListFromFile();
string readListFromTerminal();


int main() {
    List* list;
    std::string listString = input();
    
    if(isValid(listString)) {
        list = new List(listString);

        cout << "Enter the character you want to find\n> ";
        char ch = getchar();

        if(list->contains(ch)) cout << "Character in the list\n";
        else cout << "Character is NOT in the list\n";
    }

    return 0;
}


std::string input() { 
    cout << "Lab 2(1) -> проверить иерархический список на наличие в нем заданного элемента (атома) x;\n";
    cout << "1) Input from file ('file.txt' by default)\n";
    cout << "2) Terminal input\n"; 
    cout << "Input type (1, 2): \n> ";
    
    int type = 0;
    do {
        cin >> type;
        if (cin.fail()) {
            cout << "Please enter an integer (1, 2)\n> ";
            cin.clear();
            cin.ignore();
        }     
    } while(type != 1 && type != 2);

    std::string str;

    if(type == 1) str = readListFromFile();
    else if(type == 2) str = readListFromTerminal();

    str.erase(remove(str.begin(), str.end(), ' '), str.end());

    return str;
}

string readListFromFile() {
    string line;
    cin.ignore();
    ifstream infile ("file.txt");
    std::getline(infile, line);
    return line;
}

string readListFromTerminal() {
    cout << "> ";
    string line;
    cin.ignore();
    getline(std::cin, line);
    return line;
}

bool isValid(std::string listString) {
    if(listString.empty()) {
        cout << "String is empty\n";
        return false;
    }

    int openBracketCount = 0;
    bool flag = false;
    for(int i=0; i<listString.size(); i++) {
        if(listString[i] == '(') {
            flag = false;
            openBracketCount++;
        }
        else if(listString[i] == ')') {
            if(flag && openBracketCount-1 >= 0) {
                openBracketCount--;
                if(openBracketCount == 0 && i < listString.size()-1) {
                    cout << "Extra character " << listString[i] << " at pos " << i << endl;
                    return false;
                }
            }
            else {
                cout << "Unexpected character " << listString[i] << " at pos " << i << endl;
                return false;
            }
        }
        else if(isalnum(listString[i])) flag = true;
        else {
            cout << "Unexpected symbol " << listString[i] << " at pos " << i << endl;
            return false;
        }
    }
    if(openBracketCount == 0) return true;
    std::cout << "Not enough ')' in string\n";
    return false;
}
