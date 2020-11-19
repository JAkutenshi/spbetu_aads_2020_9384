#include <iostream>
#include <chrono>
#include "treap.h"

using namespace std;

int main()
{
    srand(time(0));
    int xs[] = {2, 3, 7, 2, 8, 2,2,3,1,2,5,453464,6,4 ,754,745,67 ,567,5 ,756,7, 7,567,567,5,7};
    char cs[] = {'a', 'g', 's', 'b', 'e', 'c', 'a', 'w', 'd'};
    Treap<int> asd;

    std::cout << "Inserting data:" << std::endl;
    for (size_t t = 0; t < (sizeof(xs)/sizeof(xs[0])); t++)
    {
        std::cout << "Data " << t << ":\nTime spend: ";
        auto start = std::chrono::high_resolution_clock::now();
        asd.insert(asd.root, new Treap<int>(xs[t], rand()));
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
        std::cout << duration.count() << " nanoseconds" << std::endl;
    }
    std::cout << "Find argument and delete it:" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    asd.erase(asd.root, 333);
    //asd.erase(asd.root, 'a');
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
    std::cout << "Time spend: " << duration.count() << " nanoseconds" << std::endl;
    
    asd.print(asd.root);
    std::cout << std::endl;

    std::ofstream file("output.txt");
    if (!file.is_open())
        std::cout << "File error" << std::endl;
    else
        asd.write(asd.root, file);
    file.close();
    return 0;
}
