#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "custom_vector.h"
#include <sstream> 

custom_vector<int> input();
custom_vector<int>  readListFromFile();
custom_vector<int>  readListFromTerminal();


int main() {
    // custom_vector<char> char_vector = {'c','b','a','w','g','a','x','f', 'y', 'a', 'z'};
    // char_vector.sort();
    // std::cout << "RESULT: ";
    // char_vector.print();

    // custom_vector<std::string> str_vector = {"a","qwe", "asd", "zxc", "fffff", "rqwe"};
    // str_vector.sort();
    // std::cout << "RESULT: ";
    // str_vector.print();

    custom_vector<int> list = input();
    list.sort();
    std::cout << "RESULT: ";
    list.print();
    return 0;
}


custom_vector<int>  input() { 
    std::cout << "Lab 4(16) Natural merge sort\n";
    std::cout << "1) Input from file ('file.txt' by default)\n";
    std::cout << "2) Terminal input\n"; 
    std::cout << "Input type (1, 2): \n> ";
    
    int type = 0;
    do {
        std::cin >> type;
        if (std::cin.fail()) {
            std::cout << "Please enter an integer (1, 2)\n ";
            std::cin.clear();
            std::cin.ignore();
        }     
    } while(type != 1 && type != 2);

    custom_vector<int> v;

    if(type == 1) v = readListFromFile();
    else if(type == 2) v = readListFromTerminal();
    return v;
}

custom_vector<int> readListFromFile() {
    custom_vector<int> v;
    std::ifstream infile ("file.txt");
    int x;
    while (infile >> x) {
        v.push_back(x);
    }
    return v;
}

custom_vector<int> readListFromTerminal() {
    custom_vector<int> v;
    std::string line;
    int x;
    std::cin.ignore();
    std::getline(std::cin, line);
    std::istringstream iss(line);
    while(iss >> x) {
        std::cout << x << std::endl;
       v.push_back(x);
    }
    return v;
}