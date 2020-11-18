#include <iostream>

#ifndef BT_H
#define BT_H

template <class base>

class BT {
public:
	BT();
	BT(base data, BT* l, BT* r);
	BT* left();
	BT* right();
	base RootBT();

	BT& operator= (const BT &bt);
	void setRoot(char ch);
	void setLeft(BT* b);
	void setRight(BT* b);

	void createBT(std::string& tmp);
	void replacementBT();
	void copyBT(BT<char>* &copy_to, const BT<char>* copy_from) const;

	bool IsNull();

	void destroy();

	BT* l;
	BT* r;
	base data;
};


//std::string CreateStringBT(BT<char>* bt);

#endif // !BT_H

