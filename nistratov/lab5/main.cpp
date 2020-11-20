#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include "treap.h"

using namespace std;

template <typename T>
std::vector<T> inputF()
{
    std::vector<T> array; 
    std::ifstream file("input.txt");
    if (file.is_open())
    {
        T temp;
        while (file >> temp)
            array.push_back(temp);
        
    }
    file.close();
    return array;
}

template <typename T>
std::vector<T> inputT()
{
    std::vector<T> array;
    T temp;
    size_t n = 0;
    std::cout << "Size: " << std::endl;
    std::cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> temp;
        array.push_back(temp);
    }

    return array;
}

int main()
{
    srand(time(0));
    int xs[] = {2, 3, 7, 2, 8, 2,2,3,1,2,5,453464,6,4 ,754,745,67 ,567,5 ,756,7, 7,567,567,5,7};
    char cs[] = {'a', 'g', 's', 'b', 'e', 'c', 'a', 'w', 'd'};
    Treap<int> asd;

    int n = 0;
    vector<int> array;
    std::cout << "Enter input type: 0 - File, 1 - Terminal" << std::endl;
    std::cin >> n;
    switch (n)
    {
    case 0:
        array = inputF<int>();
        break;
    case 1:
        array = inputT<int>();
        break;
    default:
        std::cout << "Error: Wrong input type" << std::endl;
        return 0;
    }

    std::cout << "Inserting data:" << std::endl;
    for (size_t t = 0; t < array.size(); t++)
    {
        std::cout << "Data " << t << ":" << std::endl;;
        auto start = std::chrono::high_resolution_clock::now();
        asd.insert(array[t]);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
        std::cout << "Time spend: " << duration.count() << " nanoseconds" << std::endl;
    }
    std::cout << "Find argument and delete it:" << std::endl;
    int c = 0;
    std::cout << "Argument = ";
    std::cin >> c;
    std::cout << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    asd.erase(c);
    //asd.erase(asd.root, 'a');
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
    std::cout << "Time spend: " << duration.count() << " nanoseconds" << std::endl;
    
    std::cout << "Tree in LCR: " << std::endl;
    asd.print();

    std::ofstream file("output.txt");
    if (!file.is_open())
        std::cout << "File error" << std::endl;
    else
        asd.write(file);
    file.close();
    return 0;
}
