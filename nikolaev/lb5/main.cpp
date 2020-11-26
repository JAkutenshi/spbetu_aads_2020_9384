#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "treap.h"

int main()
{
    srand(time(0));
    char nums[] = { "ahsdsfugals" };
    int a = sizeof(nums)/sizeof(char);
    
    Treap<char> root;
    for (char n: nums)
       root.insert(n);
    std::cout << "Constructed Treap:";
    root.print();
    std::cout << '\n';
    std::cout << root.find('a');
    std::cout << '\n';
    root.insert('a');
    std::cout << "Constructed Treap:";
    root.print();
    std::cout << '\n';
    std::cout << root.find('a');

    /*srand(time(0));
    Treap<int> treap;
    std::cout << "File (0) or Console(1)?\n";
    int tmp;
    std::cin >> tmp;
    
    std::vector<int> vec;
    if (tmp == 0)
    {
        std::string path;
        std::cout << "Enter file path: ";
        std::cin >> path;
        std::ifstream file(path);
        if (file.is_open())
        {
            int temp;
            while (file >> temp)
            {
                vec.push_back(temp);
            }
        }
        file.close();
    }
    else if (tmp == 1)
    {
        size_t size;
        std::cout << "Enter size: ";
        std::cin >> size;
    
        int temp;
        for (size_t index = 0; index < size; index++)
        {
            std::cout << "Enter [" << index << "] index: ";
            std::cin >> temp;
            vec.push_back(temp);
        }
    }
    else
    {
        std::cout << "Not supported type!\n";
        return 1;
    }
    
    for (int num : vec)
        treap.insert(num);
    std::cout << "\n===================================\n";
    treap.print();
    std::cout << "\n===================================\n";
    
    for (;;)
    {
        std::cout << "\ninsert (0), find(1), exit(2)?\n";
        std::cin >> tmp;
    
        if (tmp == 0)
        {
            std::cout << "Enter num: ";
            int num;
            std::cin >> num;
            treap.insert(num);
        }
        else if (tmp == 1)
        {
            std::cout << "Enter num: ";
            int num;
            std::cin >> num;
            std::cout << treap.find(num);
        }
        else if (tmp == 2)
        {
            break;
        }
        else
        {
            std::cout << "Not supported type!\n";
        }
    
        std::cout << "\n===================================\n";
        treap.print();
        std::cout << "\n===================================\n";
    
    }
    
    return 0;*/
}