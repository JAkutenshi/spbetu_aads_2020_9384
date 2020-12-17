#include <iostream>
#include <fstream>
#include <string>
#include "BinaryTree.h"

int main() {
    BinaryTree<char> Tree;
    int n, count = 0, amount = 0;
    std::string tmp;
    std::ifstream file;
    file.open("input.txt");
    if (!file.is_open()) {
        std::cout << "Error opening file (input.txt)" << std::endl;
        exit(1);
    }
    getline(file, tmp);
    file.close();
    std::cout << "String: " << tmp << "\n";
    Tree.ConsBT(tmp, count);
    if (!tmp.empty()) {
        std::cout << "Input Error";
        exit(2);
    }
    std::cout << "Nodes: ";
    Tree.PrintBT();
    std::cout << "\nLeaves: ";
    Tree.PrintL();
    std::cout << "\nInput level: ";
    std::cin >> n;
    Tree.PrintNumOfNodes(n);
    return 0;
}