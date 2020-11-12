#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool Check_sin(string sentence, int n) {
  //  char signs[20] = {'!','@','#','$','%','^','&','{','}','[',']','=','?','>','<',',','.','"','`','~'};
    for (int i = 0; i < n - 2;i++) {
        if (isalpha(sentence[i]) && isalpha(sentence[i + 1])) {
            return false;
        }
        if (!isalpha(sentence[i]) && sentence[i] != '(' && sentence[i] != ')' && sentence[i] !='+' && sentence[i] != '*' && sentence[i] != '-') {
            return false;
        }
    
    /*    if (isdigit(sentence[i])) {
            return false;
        }
        for (int j = 0; j < 20; j++) {
            if (sentence[i] == signs[j]) {
                return false;
            }*/
    }
    return true;
}

bool Check(string sentence) {
    int n = sentence.length();
    string a = "", b = "";
    if (isalpha(sentence[0]) && n == 1) {
        return true;
    }
    else {
        if (sentence[0] == '(' && sentence[n - 1] == ')') {
            int count = 1;
            int count_of_open = 0;
            int count_of_close = 0;
            int signs = 0;
            if (!Check_sin(sentence, n)) {
                return false;
            }
            if (sentence[1] == '(') {
                while (signs <= count_of_open && count != n-1) {
                    if (sentence[count] == '(') {
                        count_of_open++;
                    }
                    if (sentence[count] == ')') {
                        count_of_close++;
                    }
                    if (sentence[count] == '+' || sentence[count] == '-' || sentence[count] == '*') {
                        signs++;
                    }
                    if (sentence[count+1] == ')' && (sentence[count] == '+' || sentence[count] == '-' || sentence[count] == '*')) {
                        return false;
                    }
                    if (sentence[count - 1] == '(' && (sentence[count] == '+' || sentence[count] == '-' || sentence[count] == '*')) {
                        return false;
                    }
                    count++;
                }
                if (count_of_close != count_of_open) {
                    return false;
                }
                for (int i = 1; i < count - 1;i++) {
                    a += sentence[i];
                }
            }
            else {
                while (sentence[count] != '+' && sentence[count] != '-' && sentence[count] != '*') {
                    a += sentence[count];
                    if (sentence[count] == ')' && !isalpha(a[1])) {
                        return false;
                    }
                    count++;
                }
            }
            int ptr = count;
            while (count != sentence.length()-1) {
                if ((count == ptr) && (sentence[ptr] == '+' || sentence[ptr] == '-' || sentence[ptr] == '*')) {
                    count++;
                }
                b += sentence[count];
                count++;
            }
            if (Check(a), Check (b)) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
}

int main(){
    string sentence;
    ifstream file;
    ofstream file1("output.txt");
    fstream file2;
    cout << "Result:" << endl;
    file.open("input.txt");
    file2.open("output.txt", fstream::in |fstream::out);
    if (!file.is_open()) {
        cout << "Error opening file (input.txt)" << endl;
        return 0;
    }
    if (!file2.is_open()) {
        cout << "Error opening file (output.txt)" << endl;
        return 0;
    }
    while (!file.eof()) {
        getline(file, sentence);
        if (sentence == "") {

        }
        else{
            if (Check(sentence)) {
                cout << "\t" << sentence << " - True" << endl;
                file2 << sentence << " - True\n";
            }
            else {
                 cout << "\t" << sentence << " - False" << endl;
                 file2 << sentence << " - False\n";
            }
        }
    }
    file.close();
    file2.close();
}
