#include <iostream>
#include <cmath>
#include <ctime>
#include "stack.h"

void solitareSort(int *, size_t);

int main(){
    size_t count;
    int *array;
    std::string temp;
    std::cout << "Type C to write array in console or R to rand: ";
    std::cin >> temp;
    if (temp == "C"){
        std::cout << "Type count of array: ";
        std::cin >> count;
        array = new int[count];
        std::cout << "Type array: ";
        for (size_t i = 0; i < count; i++)
            std::cin >> array[i];
    }
    else if (temp == "R"){
        size_t remainder;
        std::cout << "Type count of array: ";
        std::cin >> count;
        std::cout << "Type max num in rand arr: ";
        std::cin >> remainder;
        array = new int[count];
        for (size_t i = 0; i < count; i++)
            array[i] = rand() % remainder - rand() % remainder;
    }

    std::cout << "Array: ";
    for (size_t i = 0; i < count; i++)
        std::cout << array[i] << ' ';
    std::cout << std::endl;

    clock_t start = clock();
    solitareSort(array, count);
    clock_t end = clock();

    std::cout << "Sort array: ";
    for (size_t i = 0; i < count; i++)
        std::cout << array[i] << ' ';
    std::cout << std::endl;

    std::cout << "TIME = " << (double)(end - start) / CLOCKS_PER_SEC << " s" << std::endl;
    delete[] array;
    return 0;
}

void solitareSort(int *array, size_t count){
    if (count < 2)
        return;

    Stack<int> *heap = new Stack<int>[count];
    Stack<int> row;
    int size = 1;

    heap[0].push(array[0]);
    for (int i = 1; i < count; i++){
        for (int j = 0; j < size; j++){
            if (array[i] <= heap[j].top()){
                heap[j].push(array[i]);
                break;
            }
            else if (j == size - 1){
                heap[size++].push(array[i]);
                break;
            }
        }

        std::cout << "HEAP = ";
        for (int j = 0; j < size; j++)
            std::cout << heap[j].top() << " ";
        std::cout << std::endl;
    }
    std::cout << "HEAP COUNT = " << size << std::endl;
    std::cout << "-----" << std::endl;

    for (int i = size - 1; i >= 0; i--)
        row.push(heap[i].pop());

    std::cout << "ROW top = " << row.top() << std::endl;
    std::cout << "HEAP = ";
    for (int j = 0; j < size; j++)
        if (!heap[j].empty())
            std::cout << heap[j].top() << " ";
    std::cout << std::endl;
    std::cout << "-----" << std::endl;

    array[0] = row.pop();
    int removed = 1;
    for (int i = 1; i < count; i++){
        int min, index = 0;
        for (int i = 0; i < size; i++){
            if (!heap[i].empty()){
                min = heap[i].top();
                index = i;
                break;
            }
            else{
                index = -1;
            }
        }

        if (index != -1){
            for (int j = 0; j < removed; j++){
                if (!heap[j].empty() && heap[j].top() <= min){
                    min = heap[j].top();
                    index = j;
                }
            }
            std::cout << "MIN = " << min << " INDEX = " << index << std::endl;
        }

        if (!row.empty()){
            if (min <= row.top() && index != -1)
                row.push(heap[index].pop());
            else
                removed++;
        }
        else{
            row.push(heap[index].pop());
        }

        std::cout << "ROW top = " << row.top() << std::endl;
        array[i] = row.pop();
    }

    delete[] heap;
}