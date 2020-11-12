#include <iostream>
#include <fstream>
#include "hier_list.h"

using namespace std;

namespace H_list {
	list head(const list s) {
		if (s != nullptr)
			if (!isAtom(s))
				return s->node.pair.hd;
			else {
				cout << "Error:Head(atom)\n";
				exit(1);
			}
		else {
			cout << "Error:Head(nil)\n";
			exit(1);
		}
	}
	list tail(const list s) {
		if (s != nullptr) {
			if (s != nullptr)
				if (!isAtom(s)) return s->node.pair.tl;
				else {
					cout << "Error: Tail(atom)\n";
					exit(1);
				}
			else {
				cout << "Error: Tail(nil)\n";
				exit(1);
			}
		}
	}
	bool isAtom(const list s) {
		if (s == nullptr)
			return false;
		else
			return (s->tag);
		}
	bool isNull(const list s) {
		return s == nullptr;
	}
	list cons(const list h, const list t) {
		list p;
		if (isAtom(t)) {
			cout << "Error: cons(*,atom)\n";
			exit(1);
		}
		else {
			p = new s_expr;
			if (p == nullptr) {
				cout << "Memory overloaded\n";
				exit(1);
			}
			p->tag = false;
			p->node.pair.hd = h;
			p->node.pair.tl = t;
			return p;
		}
	}
	list make_atom(const base x) {
		list s;
		s = new s_expr;
		s->tag = true;
		s->node.atom = x;
		return s;
	}
	void destroy(list s){
		if (s != nullptr) {
			if (!isAtom(s)) {
				destroy(head(s));
				destroy(tail(s));
			}
			delete s;
		}
	}
	base getAtom(const list s) {
		if (!isAtom(s)) {
			cout << "Error: getAtom(s) for !isAtom(s) \n";
			exit(1);
		}
		else
			return s->node.atom;
	}
	void read_list(list& y) {
		base x;
		do
			cin >> x;
		while (x == ' ');
		read_s_expr(x, y);
	}
	void read_s_expr(base prev, list& y) {
		if (prev == ')') {
			cout << "! List.Error 1\n";
			exit(1);
		}
		else
			if (prev != '(')
				y = make_atom(prev);
			else read_seq(y);
	}
	void read_seq(list& y) {
		base x;
		list p1, p2;
		if (!(cin >> x)) {
			cout << "! List.Error 2\n";
			exit(2);
		}
		else {
			while (x == ' ')
				cin >> x;
			if (x == ')')
				y = nullptr;
			else{
				read_s_expr(x, p1);
				read_seq(p2);
				y = cons(p1, p2);
			}
		}
	}
	void write_list(const list x) {
		if (isNull(x))
			cout << "Empty list\n";
		else
			if (isAtom(x))
				cout << x->node.atom;
			else {
				cout << '(';
				write_seq(x);
				cout << ')';
			}
	}
	void write_seq(const list x) {
		if (!isNull(x)) {
			write_list(head(x));
			write_seq(tail(x));
		}
	}
	void file_readlist(list& y) {
		string str;
		ifstream file;
		base x;
		file.open("input.txt");
		if (!file.is_open()) {
			cout << "Error opening file (input.txt)\n";
			exit(0);
		}
		do 
			file >> x;
		while (x == ' ');
		file_read_s_expr(x, y, file);
		file.close();
	}
	void file_read_s_expr(base prev, list& y, ifstream& file) {
		if (prev == ')') {
			cout << "! List.Error 1\n";
			exit(1);
		}
		else
			if (prev != '(')
				y = make_atom(prev);
			else file_read_seq(y,file);
	}
	void file_read_seq(list& y, ifstream& file) {
		base x;
		list p1, p2;
		if (!(file >> x)) {
			cout << "! List.Error 2\n";
			exit(2);
		}
		else {
			while (x == ' ')
				file >> x;
			if (x == ')')
				y = nullptr;
			else {
				file_read_s_expr(x, p1, file);
				file_read_seq(p2, file);
				y = cons(p1, p2);
			}
		}
	}
	void change(list& y, char atom1, char atom2) {
		if (!isNull(y)) {
			if (!isAtom(y)) {
				change(y->node.pair.hd, atom1, atom2);
				if (y->node.pair.tl) {
					change(y->node.pair.tl, atom1, atom2);
				}
			}
			else {
				if (y->node.atom == atom1) {
					y->node.atom = atom2;
				}
			}
		}
	}
}