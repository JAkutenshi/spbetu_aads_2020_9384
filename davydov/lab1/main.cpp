#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int permutationNumber = 0;

void permutations(string* arrayOut, string arrayIn, int pos = 0)
{
    if (pos >= arrayIn.size())
    {
        arrayOut[permutationNumber] = arrayIn;
        cout << arrayIn << '\n';
        permutationNumber++;
        return;
    }
    else
    {
        for (int i = pos; i < arrayIn.size(); ++i)
        {
            swap(arrayIn[i], arrayIn[pos]);
            permutations(arrayOut,arrayIn, pos + 1);
            swap(arrayIn[i], arrayIn[pos]);
        }
    }
}

int factorial(int i) //Функция считающая факториал
{
    if(i == 0) return 1;
    else return i*factorial(i-1);
}

void writeInFile(string *arrOut, int sizeOut) // Функция записывает перестановки в файл
{
    std::string filePathOut; // Готовим файл для работы с программой
    std::cout << "Enter output file:\n";
    std::cin >> filePathOut;
    std::ofstream out;
    out.open(filePathOut);

    if (out.is_open())
    {
        for (int i = 0; i < sizeOut; i++)
        {
            out<<arrOut[i];
            out << '\n';
        }
    }
    out.close();
}

int main(){
    string filePathIn; // Готовим файл для работы с программой
    cout << "Enter input file:\n";
    cin >> filePathIn;
    std::ifstream in;
    in.open(filePathIn);
    if(!in.is_open()){ cout<<"No such file";return 1;}
    string arrIn;
    cout<<"Enter number of elements:\n";
    int n;
    cin>>n;
    char c;
    while(in.get(c)){
        if(c!=' ' && c!='\n'){
        arrIn.push_back(c);
        }
    }
    if(n!=arrIn.size()){cout<<"The number of elements does not match"; return 1;}
    int permutationsNumber = factorial(arrIn.size());
    std::string arrOut[permutationsNumber];
    cout<<"Number of permutations:\n"<<permutationsNumber<<endl;
    cout<<"Your permutations:\n";
    permutations(arrOut,arrIn);
    writeInFile(arrOut,permutationsNumber);
    return 0;
}