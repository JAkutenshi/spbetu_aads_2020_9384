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

	void setRoot(char ch);
	void setLeft(BT* b);
	void setRight(BT* b);

	void createBT(std::string& tmp);
	void replacementBT();

	bool IsNull();

//private:
	BT* l;
	BT* r;
	base data;
};

#endif // !BT_H