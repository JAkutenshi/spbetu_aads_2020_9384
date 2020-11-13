#include <iostream>
#include <algorithm>
#include "BinaryTree.h"

BinaryTree<char>::BinaryTree()
{
	this->l = nullptr;
	this->r = nullptr;
}

char BinaryTree<char>::RootBT()
{
	if (this == nullptr) { std::cerr << "Error: RootBT(null) \n"; exit(1); }
	else return data;
}

void BinaryTree<char>::printBT() {
	if (!this->IsNull()) {
		if (!this->l->IsNull() && !this->r->IsNull() && !(this->RootBT() >= 'a' && this->RootBT() <= 'z'))
			std::cout << '(';
		this->l->printBT();
		std::cout << this->RootBT();
		this->r->printBT();
		if (!this->l->IsNull() && !this->r->IsNull() && !(this->RootBT() >= 'a' && this->RootBT() <= 'z'))
			std::cout << ')';
	}
}

void BinaryTree<char>::change()
{
	if (!this->l->IsNull() && !this->r->IsNull())
	{
		if (this->data == '+' && this->l->data == this->r->data && this->l->data >= 'a' && this->l->data <= 'z' && this->r->data >= 'a' && this->r->data <= 'z')
		{
			this->data = '*';
			this->l->data = '2';
		}
		this->l->change();
		this->r->change();
	}
}

void BinaryTree<char>::createBT(std::string& tmp)
{
	if (!tmp.empty())
	{
		if (this->l->IsNull() && this->r->IsNull())
		{
			if (tmp.front() >= 'a' && tmp.front() <= 'z')
			{
				this->data = tmp.front();
				tmp.erase(0, 1);
				this->l = new BinaryTree;
				this->r = new BinaryTree;
			}
			else
			{
				this->data = tmp.front();
				tmp.erase(0, 1);
				this->l = new BinaryTree;
				this->r = new BinaryTree;
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
bool BinaryTree<char>::IsNull()
{
	return (this == nullptr);
}

BinaryTree<char>::~BinaryTree()
{
}