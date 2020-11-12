#include <iostream>
#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	this->l = nullptr;
	this->r = nullptr;
}

BinaryTree* BinaryTree::left()
{
	if (this == nullptr) { std::cerr << "Error: Left(null) \n"; std::exit(1); }
	return this->l;
}

BinaryTree* BinaryTree::right()
{
	if (this == nullptr) { std::cerr << "Error: Right(null) \n"; std::exit(1); }
	return this->r;
}

char BinaryTree::RootBT()
{
	if (this == nullptr) { std::cerr << "Error: RootBT(null) \n"; exit(1); }
	else return data;
}

void BinaryTree::printBT() {
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

void BinaryTree::change()
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

void BinaryTree::createBT(std::string& tmp)
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

bool BinaryTree::IsNull()
{
	return (this == nullptr);
}

BinaryTree::~BinaryTree()
{
}