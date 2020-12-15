#include <iostream>
#include <fstream>
#include <vector>
#include <string>

template<typename T>
void sort_puted_value_to_the_right(T array[], int n, int gran){
    int temp;
    int right;
    int middle;
    int left;
    for (int i = gran; i < n; i++)
        if (array[i - 1] >array[i]) {
            left = gran;
            temp = array[i];
            right = i - 1 ;
            do {
                middle = (left + right) / 2;
                if (array[middle] < temp) {
                    left = middle + 1;
                }
                else {
                    right = middle - 1;
                }
            } while (left <= right);
            for (int j = i - 1; j >= left; j--)
                array[j + 1] = array[j];
            array[left] = temp;
        }
}

template<typename T>
void sort_puted_value_to_the_left(T array[], int n) {
    int temp;
    int right;
    int middle;
    int left;
    for (int i = 1; i < n; i++)
        if (array[i - 1] > array[i]) {
            temp = array[i];
            left = 0;
            right = i - 1;
            do {
                middle = (left + right) / 2;
                if (array[middle] < temp) {
                    left = middle + 1;
                }
                else {
                    right = middle - 1;
                }
            } while (left <= right);
            for (int j = i - 1; j >= left; j--)
                array[j + 1] = array[j];
            array[left] = temp;
        }
}

template<typename T>
void sort(T array[], int n) {
    int* array_temp = new int [n];
    int count = 0;
    int temp = array[0];
    int mid_poz = 0;
    array_temp[0] = array[0];
    for (int i = 1; i < n; i++) {
            if (temp <= array[i]) {
                count++;
                array_temp[count] = array[i];
                sort_puted_value_to_the_right(array_temp, count+1, mid_poz + 1);
            }
            if (temp > array[i]) {
                int x = array[i];
                count++;
                mid_poz++;
                for (int j = count; j > 0; j--) {
                    array_temp[j] = array_temp[j - 1];
                }
                array_temp[0] = x;
                sort_puted_value_to_the_left(array_temp, mid_poz+1);
            }
    }
    for (int i = 0; i < n; i++) {
        array[i] = array_temp[i];
        int u = array_temp[0];
    }
}

int main()
{
    int value;
    std::vector<int> tmp;
	std::ifstream file;
    std::string temp;
    file.open("input.txt");
    if (!file.is_open()) {
        std::cout << "Error: file input.txt isn't open" << std::endl;
        exit(1);
    }
    getline(file, temp);
    if (temp.empty()) {
        std::cout << "Error: empty array";
        exit(2);
    }
    while (file >> value) {
        tmp.push_back(value);
    }
    file.close();
    int count = tmp.size();
    int* array = &tmp[0];
    std::cout << "Your array: ";
    for (int i = 0; i < count; i++) {
        std::cout << array[i] << " ";
    }
    sort(array, count);
    std::cout << "\nSorted array: ";
    for (int i = 0; i < count; i++) {
        std::cout << array[i] << " ";
    }
    return 0;
}
