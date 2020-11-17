#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "tree.h"

int main(){
    std::string temp;
    std::cout << "Type console to write tree in console or type path to read file\n";
    std::cin >> temp;
    if(temp == "console"){
        Tree<int> tree;
        int count;
        std::cout << "Type count: ";
        std::cin >> count;
        
        std::cout << "Type data: ";
        for(int i = 0; i < count; i++){
            std::cin >> temp;
            tree.insert_node(std::stoi(temp));
        }
        tree.render_node();
        tree.write_node("output.txt");
    }
    
    else{
        std::ifstream file(temp);
        if(file.is_open()){
            while(getline(file, temp)){
                Tree<int> tree;
                std::istringstream str(temp);
                std::string data;
                while(getline(str, data, ' ')){
                    tree.insert_node(std::stoi(data));
                }
                tree.render_node();
                tree.write_node("output.txt");
            }
        }
        else{
            throw std::runtime_error("type valid path\n");
        }
    }

    return 0;
}