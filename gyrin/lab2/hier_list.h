#include <iostream>
#include <fstream>

using namespace std;

namespace H_list {
	typedef char base;
	struct s_expr;
	struct two_ptr {
		s_expr* hd;
		s_expr* tl;
	};
	struct s_expr {
		bool tag;
		union {
			base atom;
			two_ptr pair;
		}node;
	};
	typedef s_expr* list;

	base getAtom(const list s);
	list head(const list s);
	list tail(const list s);
	list cons(const list h, const list t);
	bool isAtom(const list s);
	bool isNull(const list s);
	void destroy(list s);

	void read_list(list& y);
	void read_s_expr(base prev, list& y);
	void read_seq(list& y);

	void write_list(const list x);
	void write_seq(const list x);

	void file_readlist(list& y);
	void file_read_s_expr(base prev, list& y, ifstream& file);
	void file_read_seq(list& y, ifstream& file);

	void change(list& y, char atom1, char atom2);
}