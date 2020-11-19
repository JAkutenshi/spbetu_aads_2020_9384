#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator> 
#include <functional>
#include <sstream>
#include <string>

using namespace std;

template<typename T>
auto print(const char* msg, T& vec) {
    cout << msg;
    copy(vec.cbegin(), vec.cend(), ostream_iterator<int>{cout, " "});
    cout << endl;
};

template<typename T>
bool cmp_equal(T a, T b)
{
    return a == b;
}

template<typename T>
bool cmp_more(T a, T b)
{
    return a > b;
}

template<typename T>
T& bingo(T &data, function<bool(typename T::value_type, typename T::value_type)> more, function<bool(typename T::value_type, typename T::value_type)> equal)
{   
    typename T::size_type max = data.size() - 1;
    typename T::value_type nextValue = *max_element(data.begin(), data.end());
    while (max && equal(data[max], nextValue) && max--) {
        cout << "max-- because items are already sorted" << endl;
    }
    cout << "First search for max element" << endl;
    cout << nextValue << endl;
    cout << endl;
    while (max)
    {
        typename T::value_type value = nextValue;
        nextValue = data[max];
        for_each(data.rbegin() + (data.size() - max - 1), data.rend(),
            [&data, &max, &value, &nextValue, more , equal](typename T::value_type& it)
            {
                if (equal(it,value))
                {
                    cout << "swap curent item with data[max]" << endl;
                    cout << "because curent item " << it << " == max value " << value << endl;
                    swap(it, data[max]);
                    --max;
                    cout << "max-- because items after data[max] are already sorted" << endl;
                    cout << endl;
                }
                else if (more(it,nextValue)){
                    cout << "change next value\nbecause value > next value" << endl;
                    cout << endl;
                    nextValue = it;
                }
            });
        while (max && equal(data[max], nextValue) && max--){
            cout << "max-- because items are already sorted" << endl;
        }
    }
    return data;
}

int main()
{
    function<bool(int, int)> more = cmp_more<int>;
    function<bool(int, int)> equal = cmp_equal<int>;
    vector<int> vec;
    char c;
    int n;
    cout << "Read file? Y/N" << endl;
    cin >> c;
    string str;
    if (c == 'Y') {
        cout << "file name - ";
        string name;
        cin >> name;
        ifstream file(name);;
        if (file.is_open()) {
            while (getline(file, str)) {
                istringstream temp(str);
                string num;
                while (getline(temp, num))
                    vec.push_back(stod(num));
            }
        }
    }else if(c == 'N'){
        cout << "input any letter for stop" << endl;
        while(cin >> n)
            vec.push_back(n);
    }else {
        return 0;
    }
    
    print("Before: ", vec);
    bingo(vec, more, equal);
    print("After:  ", vec);
    return 0;
}