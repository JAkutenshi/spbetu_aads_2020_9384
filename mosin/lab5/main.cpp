#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "tree.h"

int main(){
    srand(time(0));

    Tree<int> *tree = nullptr;
    
    int count;
    std::cout << "Type count: ";
    std::cin >> count;
    if(count > 0){
        int temp;
        std::cout << "Type data: ";
        for(int i = 0; i < count; i++){
            std::cin >> temp;
            tree ? tree = tree->insert(tree, temp) : tree = new Tree<int>(temp);
        }
        tree->print();
        std::ofstream file("output.txt");
        file.is_open() ? tree->write(file) : throw std::runtime_error("file could not open");
        delete tree;
    }
    return 0;
}
