#include <iostream>

#ifndef BT_H
#define BT_H



class BT {
public:
	BT();
	BT(char data, BT* l, BT* r);
	BT* left();
	BT* right();
	char RootBT();

	void setRoot(char ch);
	void setLeft(BT* b);
	void setRight(BT* b);

	void createBT(std::string& tmp);
	void replacementBT();

	bool IsNull();

//private:
	BT* l;
	BT* r;
	char data;
};

#endif // !BT_H