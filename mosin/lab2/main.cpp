#include <iostream>

#include "list.h"

using namespace std;
using namespace h_list;

bool isCorrectList(const list x, const int op = 0);
bool isOperation(const base x);
bool OprList(const list x);
void OprSeq(const list x);
list reverse(const list s);
list rev(const list s, const list z);


int main(){
    list s;
    int a;
    cout << "Type 1 for prefix form\n";
    cout << "Type 2 for postfix form\n";
    cout << "Command: ";
    cin >> a;
    if(a != 1 && a != 2)
        error_type(9);
    cout << "Type list: ";
    read_list(s);
    write_list(s);
    if(a == 2)
        s = reverse(s);
    if(OprList(s) && isCorrectList(s))
        cout << " True" << endl;
    else
        error_type(12);
    destroy(s);
    return 0;
}

bool isCorrectList(const list x, const int op){
    static int counter = 1;
    counter++;
    if(!isNull(x) && !isAtom(head(x))){
        counter--;
        return isCorrectList(head(x), 0);
    }
    else if(!isNull(x) && !isNull(tail(x)) && isOperation(head(x)->node.atom) && !isOperation(head(tail(x))->node.atom))
        return isCorrectList(tail(x), 1);
    else if(!isNull(x) && !isNull(tail(x)) && !isOperation(head(x)->node.atom) && !isOperation(head(tail(x))->node.atom))
        return isCorrectList(tail(x), op);
    else if(!isNull(x) && isNull(tail(x)) && op && !isOperation(x->node.atom))
        return true;
    else{
        cout << counter << " symbol" << endl;
        return false;
    }
}

bool isOperation(const base x){
    if(x == '+' || x == '-' || x == '*' || x == '/')
        return true;
    return false;
}

bool OprList(const list x){
    static bool add, sub, mul, div = false;
    if(isNull(x)){
        error_type(10);
        return false;
    }
    else if(isAtom(x)){
        if(x->node.atom == '+') add = true;
        else if(x->node.atom == '-') sub = true;
        else if(x->node.atom == '*') mul = true;
        else if(x->node.atom == '/') div = true;
    }
    else
        OprSeq(x);

    if((add && sub && mul) || (add && sub && div) || (add && mul && div) || (sub && mul && div)){
        error_type(11);
        return false;
    }
    return true;
}

void OprSeq(const list x){
    if(!isNull(x)){
        OprList(head(x));
        OprSeq(tail(x));
    }
}

list reverse(const list s){
	return (rev(s, NULL));
}

list rev(const list s, const list z){
	if(isNull(s))
		return (z);
	else if(isAtom(head(s)))
		return (rev(tail(s), cons(head(s), z)));
	else
		return (rev(tail(s), cons(rev(head(s), NULL), z)));
}
