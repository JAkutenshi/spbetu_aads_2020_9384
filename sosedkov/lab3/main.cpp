#include <iostream>
#include <string>
#include <fstream>
#include "Stack.h"

using namespace std;

std::string input();
string readListFromFile();
string readListFromTerminal();

bool is_pair(char, char);
bool is_open_bracket(char);
bool is_closed_bracket(char);



int main() {
    Stack* stack = new Stack();
    std::string listString = input();
    if(!listString.size()) {
        std::cout << "String is empty\n";
        return 1;
    }
    
    for(int i=0; i<listString.size(); i++) {
        if(is_open_bracket(listString[i])) {
            stack->push(listString[i]);
        } 
        else if(is_closed_bracket(listString[i])) {
            if(!stack->isEmpty() && is_pair(listString[i], stack->top())) {
                stack->pop();
            }
            else if(stack->isEmpty()) {
                std::cout << "ERROR at pos " << i << " (Stack is empty)\n";
                return 2;
            }
            else {
                std::cout << "Unexpected character " << listString[i] << " at pos " << i << std::endl;
                return 3;
            }
        }
    }

    if(stack->isEmpty()) {
        std::cout << "OK\n";
    }
    else {
        std::cout << "ERROR: Stack is not empty\n";
        return 4;
    }

    return 0;
}





bool is_pair(char bracket, char pair) {
    if(bracket == ')' && pair == '(') return true;
    else if(bracket == ']' && pair == '[') return true;
    else if(bracket == '}' && pair == '{') return true;
    else return false;
}



bool is_open_bracket(char c) {
    return c == '(' || c  == '[' || c  == '{';
}



bool is_closed_bracket(char c) {
    return c == ')' || c  == ']' || c  == '}';
}



std::string input() { 
    cout << "Lab 3(5) -> Проверить является ли текст правильной скобочной конструкцией\n";
    cout << "1) Input from file ('file.txt' by default)\n";
    cout << "2) Terminal input\n"; 
    cout << "Input type (1, 2): \n> ";
    
    int type = 0;
    do {
        cin >> type;
        if (cin.fail()) {
            cout << "Please enter an integer (1, 2)\n ";
            cin.clear();
            cin.ignore();
        }     
    } while(type != 1 && type != 2);

    std::string str;

    if(type == 1) str = readListFromFile();
    else if(type == 2) str = readListFromTerminal();

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