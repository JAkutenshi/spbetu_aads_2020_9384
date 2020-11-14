#include "BT.h"

template<>
BT<char>::BT() {
	this->l = nullptr;
	this->r = nullptr;
}

template<>
BT<char>::BT(char data, BT *l, BT *r) {
	this->data = data;
	this->l = l;
	this->r = r;
}

template<>
BT<char>* BT<char>::left() {
	if (this == nullptr) { std::cerr << "Error: Left(null) \n"; std::exit(1); }
	return this->l;
}

template<>
BT<char>* BT<char>::right() {
	if (this == nullptr) { std::cerr << "Error: Right(null) \n"; std::exit(2); }
	return this->r;
}

template<>
char BT<char>::RootBT(){
	if (this == nullptr) { std::cerr << "Error: RootBT(null) \n"; exit(3); }
	else return data;
}

template<>
void BT<char>::setRoot(char ch) {
	this->data = ch;
}

template<>
void BT<char>::setLeft(BT* b) {
	this->l = b->l;
}

template<>
void BT<char>::setRight(BT* b) {
	this->r = b->r;
}

template<>
void BT<char>::createBT(std::string& tmp)
{
	if (!tmp.empty())
	{
		if (this->l->IsNull() && this->r->IsNull())
		{
			if (tmp.front() >= 'a' && tmp.front() <= 'z')
			{
				this->data = tmp.front();
				tmp.erase(0, 1);
				this->l = new BT;
				this->r = new BT;
			}
			else
			{
				this->data = tmp.front();
				tmp.erase(0, 1);
				this->l = new BT;
				this->r = new BT;
				this->l->createBT(tmp);
				this->r->createBT(tmp);
			}
		}
		else
		{
			this->l->createBT(tmp);
			this->r->createBT(tmp);
		}
	}
}

template<>
void BT<char>::replacementBT() {
	if (!this->IsNull()) {
		if (!this->left()->IsNull() && !this->right()->IsNull() && this->RootBT() == '*') {
			if (this->left()->RootBT() == '+' && !this->left()->left()->IsNull() && !this->left()->right()->IsNull() && (this->right()->RootBT() >= 'a' && this->right()->RootBT() <= 'z')) {
				this->r->l = new BT;
				this->r->r = new BT;
				this->r->l->data = this->r->RootBT();
				this->r->r->data = this->left()->right()->RootBT();
				this->l->r->data = this->l->l->data;
				this->l->l->data = this->right()->RootBT();
				this->r->data = '*';
				this->l->data = '*';
				this->data = '+';
			}
			else if (this->right()->RootBT() == '+' && !this->right()->left()->IsNull() && !this->right()->right()->IsNull() && (this->left()->RootBT() >= 'a' && this->left()->RootBT() <= 'z')) {
				this->l->l = new BT;
				this->l->r = new BT;
				this->l->l->data = this->l->RootBT();
				this->l->r->data = this->right()->right()->RootBT();
				this->r->r->data = this->r->l->data;
				this->r->l->data = this->left()->RootBT();
				this->l->data = '*';
				this->r->data = '*';
				this->data = '+';
			}
		}
		this->left()->replacementBT();
		this->right()->replacementBT();
	}
}
