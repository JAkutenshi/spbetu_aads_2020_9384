#include "linear_list.h"

using namespace std;

namespace L_list{

    // рекурсивный вывод
    void printList(List s){
        if (s != nullptr) {
            cout << *s->hd << " (" << int(*s->hd) << ") : ";
            printList(s->tl);
        } else { // s = nil
            cout << "nil\n";
        }
    }

    Base head(List s) {// PreCondition: not null (s)
        if (s != nullptr) return *s->hd;
        else {
            cerr << "Error: head(nil) \n";
            exit(1);
        }
    }

    List tail(List s) {// PreCondition: not null (s)
        if (s != nullptr) return s->tl;
        else {
            cerr << "Error: tail(nil) \n";
            exit(1);
        }
    }

    List cons(Base x, List s) {
        List p;
        p = new node;
        if (p != nullptr) {
            p->hd = new char;
            *p->hd = x;
            p->tl = s;
            return p;
        } else {
            cerr << "Memory not enough\n";
            exit(1);
        }
    }

    void destroy(List s) {
        if (s != nullptr) {
            destroy(tail(s));
            delete s->hd;
            delete s;
            // s = NULL;
        };
    }

    List concat(List s1, List s2) {
        if (s1 == nullptr) return s2;
        else return cons(head(s1), concat(tail(s1), s2));
    }

    void writeInFile(List s){
        std::string filePathOut;
        std::cout << "Enter output file:\n";
        std::cin >> filePathOut;
        std::ofstream out;
        out.open(filePathOut);
        List p = s;
        int i = 0;
        while (p != nullptr) {
            i++;
            out << i << " : " << *p->hd << "(" << int (*p->hd) << ") "<< endl;
            p = p->tl;
        }
    }

    int countElements(List s){
        int count = 0;
        List p = s;
        while (p != nullptr){
            count++;
            p = p->tl;
        }
        return count;
    }
}
