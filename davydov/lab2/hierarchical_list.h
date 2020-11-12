#ifndef LINKED_LIST_FINAL_HIERARCHICAL_LIST_H
#define LINKED_LIST_FINAL_HIERARCHICAL_LIST_H
#include <iostream>
#include <fstream>

using namespace std;

namespace H_list{

    typedef char Base;	// базовый тип элементов (атомов)

    struct S_expr;
    struct  two_ptr
    {
        S_expr *hd;
        S_expr *tl;
    } ;

    struct S_expr {
        bool tag; // true: atom, false: pair
        union
        {
            Base atom;
            two_ptr pair;
        } node;
    };

    typedef S_expr *Lisp;

    // создание списка
    Lisp head (const Lisp s);
    Lisp tail (const Lisp s);
    Lisp cons (const Lisp h, const Lisp t);
    Lisp makeAtom (const Base x);
    Base getAtom (const Lisp s);
    bool isAtom (const Lisp s);
    bool isNull (const Lisp s);
    void destroy (Lisp s);

    // чтение из файла
    void readLispFile(Lisp& y);
    void readS_exprFile (Base prev, Lisp& y, ifstream &infile);
    void readSeqFile (Lisp& y, ifstream &infile);

    // чтение с консоли:
    void readLisp (Lisp& y);
    void readS_expr (Base prev, Lisp& y);
    void readSeq (Lisp& y);

    // функции вывода:
    void printLisp (const Lisp x);
    void printSeq (const Lisp x);

    //копирование списка
    Lisp copyLisp (const Lisp x);
}
#endif
