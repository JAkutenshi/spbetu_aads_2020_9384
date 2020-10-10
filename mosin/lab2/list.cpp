#include <iostream>
#include <cstdlib>

using namespace std;

#include "list.h"

namespace h_list{
    list head(const list s){
        if(s){
            if(!isAtom(s))
                return s->node.pair.head;
            else
				error_type(1);
        }
        else
			error_type(2);
    }

    list tail(const list s){
        if(s){
            if(!isAtom(s))
                return s->node.pair.tail;
            else
				error_type(3);
        }
        else
			error_type(4);
    }

    list cons(const list h, const list t){
		list p;
		if(isAtom(t))
			error_type(5);
		else{
			p = new exp;
			if(p == NULL)
				error_type(6);
			else{
				p->tag = false;
				p->node.pair.head = h;
				p->node.pair.tail = t;
				return p;
			}
		}
    }

    list make_atom(const base x){
		list s = new exp;
		s->tag = true;
		s->node.atom = x;
		return s;
	}

    bool isAtom(const list s){
		if(s == NULL)
			return false;
		else
			return (s->tag);
	}

    bool isNull(const list s){
		return s == NULL;
	}

    void destroy(list s){
		if(s){
			if(!isAtom(s)){
				destroy(head(s));
				destroy(tail(s));
			}
			delete s;
		}
	}

    void read_list(list& y){
		base x;
		do
			cin >> x;
		while(x == ' ');
		read_exp(x, y);
	}

	void read_exp(base prev, list& y){
		if(prev == ')'){
			error_type(7);
		}
		else if(prev != '(')
			y = make_atom(prev);
		else
			read_seq(y);
	}

	void read_seq(list& y){
		base x;
		list p1, p2;

		if(!(cin >> x)){
			error_type(8);
		}
		else{
			while(x == ' ')
				cin >> x;
			if(x == ')')
				y = NULL;
			else{
				read_exp(x, p1);
				read_seq(p2);
				y = cons(p1, p2);
			}
		}
	}

    void write_list(const list x){
		if(isNull(x))
			cout << " ()";
		else if(isAtom(x))
			cout << ' ' << x->node.atom;
		else{
			cout << " (";
			write_seq(x);
			cout << " )";
		}
	}

    void write_seq(const list x){
		if(!isNull(x)){
			write_list(head(x));
			write_seq(tail(x));
		}
	}

	void error_type(int err){
		switch(err){
			case 1:
				cerr << "Error: Head(atom)" << endl;
                exit(1);
			case 2:
            	cerr << "Error: Head(NULL)" << endl;
                exit(2);
			case 3:
                cerr << "Error: Tail(atom)" << endl;
                exit(3);
			case 4:
            	cerr << "Error: Tail(NULL)" << endl;
				exit(4);
			case 5:
				cerr << "Error: Cons(*, atom)" << endl;
				exit(5);
			case 6:
				cerr << "Error: Memory not enough" << endl;
				exit(6);
			case 7:
				cerr << " ! List.Error 1 " << endl;
				exit(7);
			case 8:
				cerr << " ! List.Error 2 " << endl;
				exit(8);
			case 9:
        		cout << "Error: type 1 or 2" << endl;
				exit(9);
			case 10:
				cout << "Error: empty list" << endl;
				exit(10);
			case 11:
				cout << "Error: there more then 2 operations" << endl;
				exit(11);
			case 12:
				cout << "Error: bad syntax" << endl;
				exit(12);
			default:
				cout << "Unknown" << endl;
		}
	}
}
