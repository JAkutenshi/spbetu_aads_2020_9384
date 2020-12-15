#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Coder.h"
#include "List.h"

int main(){
    Coder<char> b;
    List<Coder<char>*> ptr;
    std::string tmp;
    std::ifstream  file;
    file.open("input.txt");
    getline(file, tmp);
    file.close();
    if (tmp.empty()) {
        std::cout << "Empty String\n";
        exit(1);
    }
    std::cout << "Your string: " << tmp << "\n";
    int amount = b._CountOfLetters(tmp);
    Coder<char>::priority* prior = new Coder<char>::priority[amount];
    b._MakePriority(prior, tmp, amount);
    std::cout << "Priorities: ";
    for (int i = 0; i < amount; i++) {
        if (prior[i].letter != ' ') {
            std::cout << prior[i].letter << "-" << prior[i].count << "; ";
        }
        else {
            std::cout << "SPACE" << "-" << prior[i].count << "; ";
        }
    }
    b._MakeNodes(prior, amount, ptr);
    b._Huffman(ptr);
    Coder<char>* Tree = ptr.Head->x;
    Coder<char>::CodedValue* code = new Coder<char>::CodedValue[amount];
    b._WriteCodedValue(Tree, code);
    std::cout << "\nCode: ";
    for (int i = 0; i < amount; i++) {
        if (code[i].letter != ' ') {
            std::cout << code[i].letter << "-";
            for (size_t n = 0; n < code[i].code.size(); n++) {
                std::cout << code[i].code[n];
            }
            std::cout << "; ";
        }
        else {
            std::cout << "SPACE" << "-";
            for (size_t n = 0; n < code[i].code.size(); n++) {
                std::cout << code[i].code[n];
            }
            std::cout << "; ";
        }
    }
    std::cout << "\nCoded string: ";
    for (size_t i = 0; i < tmp.size(); i++) {
        for (int j = 0; j < amount; j++) {
            if (tmp[i] == code[j].letter) {
                for (size_t n = 0; n < code[j].code.size(); n++) {
                    std::cout << code[j].code[n];
                }
            }
        }
        std::cout << " ";
    }

    return 0;
}
