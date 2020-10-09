#include <iostream>
#include <cstdlib>

using namespace std;

#include "list.h"

namespace h_list{
    list head(const list s){
        if(s){
            if(!isAtom(s)){
                return s->node.pair.head;
            }
            else{
                cerr << "Error: Head(atom)\n";
                exit(1);
            }
        }
        else{
            cerr << "Error: Heid(NULL)\n";
            exit(1);
        }
    }

    list tail(const list s){
        if(s){
            if(!isAtom(s)){
                return s->node.pair.tail;
            }
            else{
                cerr << "Error: Tail(atom)\n";
                exit(1);
            }
        }
        else{
            cerr << "Error: Tail(NULL)\n";
            exit(1);
        }
    }

    list cons(const list h, const list t){
		list p;
		if (isAtom(t)){
			cerr << "Error: Cons(*, atom)\n";
			exit(1);
		}
		else{
			p = new exp;
			if (p == NULL){
				cerr << "Error: Memory not enough\n";
				exit(1);
			}
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
		if (s == NULL)
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
			cerr << " ! List.Error 1 " << endl;
			exit(1);
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
			cerr << " ! List.Error 2 " << endl;
			exit(1);
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
		if (!isNull(x)){
			write_list(head(x));
			write_seq(tail(x));
		}
	}
}