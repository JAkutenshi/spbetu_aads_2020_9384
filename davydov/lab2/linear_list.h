#ifndef LINKED_LIST_FINAL_LINEAR_LIST_H
#define LINKED_LIST_FINAL_LINEAR_LIST_H
#include <iostream>
#include <fstream>

namespace L_list{

    typedef char Base;
    struct node {
        Base *hd;
        node *tl;
        // constructor
        node ()
        {hd = nullptr; tl = nullptr;
        }
    };
    typedef node *List;

    //создание списка
    Base head (List s);
    List tail (List s);
    List cons (Base x, List s);
    void destroy (List s);

    //объединение двух списков
    List concat (List s1, List s2);

    //вывод в консоль
    void printList (List s);

    //запись в файл
    void writeInFile(List s);

    int countElements(List s);
}
#endif
