#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
bool comparator(T a, T b){
    return a>b;
}

template <typename T>
void showInfo(T arr, size_t j){
    cout<< "\""<<arr[j]<<"\", "<< j+1<<" element in array was swapped with \""<< arr[j+1]<<"\", "<< j+2 <<" element in array (";
    cout<<"because \""<<arr[j]<< "\" > \"" << arr[j+1]<<"\")\n"<<endl;
}

template <typename T>
void bubbleSort(T arr[],size_t n, bool(*cmp)(T,T)){
    bool isSorted;
    for (size_t i = 0; i < n-1; i++)
    {
        isSorted = true;
        for (size_t j = 0; j < n-i-1; j++)
        {
            if (cmp(arr[j],arr[j+1]))
            {
                showInfo(arr,j);
                T tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                isSorted = false;
            }

        }

        if (isSorted)
            break;
    }
}

template <typename T>
void oddEvenSort(T arr[], size_t n,bool(*cmp)(T,T)){
    bool isSorted = false;
    if(n == 1){ return;}
    while (!isSorted){
        isSorted = true;

        for (size_t i=1; i<=n-2; i=i+2){
            if (cmp(arr[i],arr[i+1])){
                cout<<"swapping element on even position with element on odd position"<<endl;
                showInfo(arr,i);
                swap(arr[i], arr[i+1]);
                isSorted = false;
            }
        }

        for (size_t i=0; i<=n-2; i=i+2){
            if (cmp(arr[i],arr[i+1])){
                cout<<"swapping element on odd position with element on even position"<<endl;
                showInfo(arr,i);
                swap(arr[i], arr[i+1]);
                isSorted = false;
            }
        }
    }
}

int main(){
    cout<<"Enter number of elements:"<<endl;
    size_t N;
    cin>>N;
    getchar();
    int array[N];
    int array2[N];
    cout<<"Choose way to enter an array:\n1 - from console\n2 - from file"<<endl;
    switch(getchar()){
        case '1' : {
            for(size_t i = 0;i<N;i++){
                cin>> array[i];
                array2[i] = array[i];
            }
            break;
        }
        case '2' : {
            std::string filePathIn;
            std::cout << "Enter input file:\n";
            std::cin >> filePathIn;
            std::ifstream in;
            in.open(filePathIn);
            int number = 0;
            if(in.is_open()){
                for(size_t i = 0;i<N;i++){
                    in >> number;
                    array[i] = number;
                    array2[i] = number;
                }
                break;
            } else cout<<"No such file"<<endl; return 1;
        }
        default: cout<<"You haven't chose anything" <<endl; return 1;
    }

    cout<< "Bubble sort:\n ---------------------------------"<<endl;
    bubbleSort(array,N,comparator);
    cout<<"\nsorted array: ";
    for(int i : array) cout<<i<< ' ';
    cout<< "\n---------------------------------\n\n\n"<<endl;

    cout<<"Odd even sort:\n---------------------------------"<<endl;
    oddEvenSort(array2,N,comparator);
    cout<<"\nsorted array: ";
    for(int i : array2) cout<<i<< ' ';
    cout<< "\n---------------------------------"<<endl;

}