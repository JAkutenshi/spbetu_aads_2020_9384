#include "BT.h"

BT<char>::BT() {
	this->l = nullptr;
	this->r = nullptr;
}

BT<char>::BT(char data, BT *l, BT *r) {
	this->data = data;
	this->l = l;
	this->r = r;
}

BT<char>& BT<char>::operator= (const BT &bt) {
	if (this != &bt) {
		this->l = bt.l;
		this->r = bt.r;
		this->data = bt.data;
	}
	return *this;
}

BT<char>* BT<char>::left() {
	if (this == nullptr) { std::cerr << "Error: Left(null) \n"; std::exit(1); }
	return this->l;
}

BT<char>* BT<char>::right() {
	if (this == nullptr) { std::cerr << "Error: Right(null) \n"; std::exit(2); }
	return this->r;
}

char BT<char>::RootBT(){
	if (this == nullptr) { std::cerr << "Error: RootBT(null) \n"; exit(3); }
	else return data;
}

void BT<char>::setRoot(char ch) {
	this->data = ch;
}

void BT<char>::setLeft(BT* b) {
	this->l = b->l;
}


void BT<char>::setRight(BT* b) {
	this->r = b->r;
}

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

void BT<char>::replacementBT() {
	if (!this->IsNull()) {
		if (!this->left()->IsNull() && !this->right()->IsNull() && this->RootBT() == '*') {
			if (this->left()->RootBT() == '+' && !this->left()->left()->IsNull() && !this->left()->right()->IsNull() && (this->right()->RootBT() >= 'a' && this->right()->RootBT() <= 'z')) {
				char buff = this->right()->RootBT();
				this->r->l = new BT;
				this->r->r = this->l->l;
				this->l->l = new BT;
				this->data = '+';
				this->r->data = '*';
				this->l->data = '*';
				this->l->l->data = buff;
				this->r->l->data = buff;
			}
			else if (this->right()->RootBT() == '+' && !this->right()->left()->IsNull() && !this->right()->right()->IsNull() && (this->left()->RootBT() >= 'a' && this->left()->RootBT() <= 'z')) {
				char buff = this->left()->RootBT();
				this->l->l = new BT;
				this->l->r = this->l->l;
				this->r->l = new BT;
				this->data = '+';
				this->l->data = '*';
				this->r->data = '*';
				this->r->l->data = buff;
				this->l->l->data = buff;
			}
		}
		this->left()->replacementBT();
		this->right()->replacementBT();

	}
}

template<>
void BT<char>::copyBT(BT<char>* &copy_to, const BT<char>* copy_from) const
{
	if (copy_from == NULL) {
		copy_to = NULL;
	}
	else {
		copy_to = new BT<char>;
		copy_to->data = copy_from->data;
		copyBT(copy_to->l, copy_from->l);
		copyBT(copy_to->r, copy_from->r);/*
		copy_helper(copy_to->parent, copy_from->parent);*/
	}
}

template<>
bool BT<char>::IsNull() {
	return (this == nullptr);
}

template<>
void BT<char>::destroy()
{
	if (this != NULL) {
		this->l->destroy();
		this->r->destroy();
		delete this;
	}
}