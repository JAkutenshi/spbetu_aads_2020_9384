#include <iostream>
#include <cstdlib>
#include "lisp.h"

using namespace std;
using namespace h_list;
lisp lineList(const lisp s);
lisp lineRest(const lisp h, lisp t);

int main()
{
    lisp s1, s2;
    cout << boolalpha;
    cout << "введите list:" << endl;
    read_lisp(s1);
    cout << "введен list: " << endl;
    write_lisp(s1);
    cout << endl;
    s2 = lineList(s1);
    cout << "для списка:" << endl;
    write_lisp(s1);
    cout << endl;
    cout << "линейный список есть:" << endl;
    write_lisp(s2);
    cout << endl;
    destroy(s1);
    destroy(s2);
    cout << "end! " << endl;
    return 0;
}

lisp lineRest(const lisp y, const lisp z)
{
    if (isNull(y))
        return copy_lisp(z);
    else
        return cons(copy_lisp(head(y)), lineRest(tail(y), z));
}

lisp lineList(const lisp s)
{
    if (isNull(s))
        return NULL;
    else if (isAtom(s))
        return cons(make_atom(getAtom(s)), NULL);
    else if (isAtom(head(s)))
        return cons(make_atom(getAtom(head(s))), lineList(tail(s)));
    else
        return lineRest(lineList(head(s)), lineList(tail(s)));
}