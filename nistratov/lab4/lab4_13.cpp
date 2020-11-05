#include <iostream>
#include <chrono>

template<typename T>
void heapify(T array[], size_t n, int i)
{
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if ((left < n) && (array[left] > array[max]))
        max = left;

    if ((right < n) && (array[right] > array[max]))
        max = right;

    if (max != i)
    {
        std::swap(array[i], array[max]);
        heapify(array, n, max);
    }
}

//"Пирамидальная сортировка"
template<typename T>
void sortHeap(T array[], size_t n)
{
    std::cout << "`````````````````" << std::endl; 
    std::cout << "rearraging by max arg: " << std::endl;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    std::cout << "array: ";
    for (int i = 0; i < n; i++)
        std::cout << array[i] << " ";
    std::cout << std::endl;
    std::cout << "`````````````````" << std::endl; 

    for (int i = n - 1; i > 0; i--)
    {
        std::cout << "swap last with first arg: " << array[i]
                  << " " << array[0] << std::endl;
        std::swap(array[0], array[i]);
        std::cout << "removing last arg: " << array[i] << std::endl;
        heapify(array, i, 0);
    }
    std::cout << "`````````````````" << std::endl << std::endl; 
}

int main()
{
    size_t N;
    std::cin >> N;
    int array[N];
    for (int i = 0; i < N; i++)
        std::cin >> array[i];
    auto start = std::chrono::high_resolution_clock::now();
    sortHeap(array, N);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);

    std::cout << "Sorted array:" << std::endl;
    for (int i = 0; i < N; i++)
        std::cout << array[i] << " ";
    std::cout << std::endl;
    std::cout << "timer : " << std::endl << duration.count() << " microseconds" << std::endl;
}