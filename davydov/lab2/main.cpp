#include "hierarchical_list.h"
#include "linear_list.h"

using namespace std;
using namespace H_list;
using namespace L_list;

L_list::List toLinearConvert(const Lisp s);

int main (){

    H_list::Lisp s1;
    L_list::List s2;

    cout<<"Choose way to enter hierarchical List:\n1 - read from console\n2 - read from file"<<endl;
    char c1;
    cin>>c1;
    switch(c1){
        case '1': readLisp(s1); break;
        case '2': readLispFile(s1); break;
        default: cout<<"You haven't choose anything"<<endl; return 1;
    }

    cout<<"Your hierarchical List:"<<endl;
    printLisp(s1);
    cout<<'\n';

    s2 = toLinearConvert(s1);

    cout<<"Number of elements/atoms"<<endl;
    cout << countElements(s2)<<endl;

    cout<<"Your lineal list of hierarchical atoms:"<<endl;
    s2 = toLinearConvert(s1);
    L_list::printList(s2);

    cout<<"Do you want to write it in file?\n1 - yes\nanything else - no"<<endl;
    char c2;
    cin>>c2;
    if(c2 == '1') L_list::writeInFile(s2);
    else cout<<"List was not written to file"<<endl;

    H_list::destroy(s1);
    L_list::destroy(s2);

    return 0;
}

L_list::List toLinearConvert(const Lisp s) {
    if (isNull(s)){
        return nullptr;
    }

    else if (!isAtom(head(s))) {
        return L_list::concat(toLinearConvert(H_list::head(s)), toLinearConvert(H_list::tail(s)));
    }

    if (!isNull(tail(s))) {
        return L_list::cons(getAtom(H_list::head(s)), toLinearConvert(H_list::tail(s)));
    }
    else {
        return L_list::cons(getAtom(H_list::head(s)), nullptr);
    }
}
