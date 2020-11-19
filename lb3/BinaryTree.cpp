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

void BinaryTree<char>::destroy()
{
	if (this != NULL) {
		this->l->destroy();
		this->r->destroy();
		delete this;
	}
}


void BinaryTree<char>::change()
{
	if (!this->l->IsNull() && !this->r->IsNull())
	{
		this->l->change();
		this->r->change();

		/*if (this->l->IsNull() && this->r->IsNull())
		{
			if (this->data == '+' && this->l->data == this->r->data && this->l->data >= 'a' && this->l->data <= 'z' && this->r->data >= 'a' && this->r->data <= 'z')
			{
				this->data = '*';
				this->l->data = '2';
			}
			else if (this->data == '+' && this->l->data == '*' && this->r->data == '*')
			{
				if (this->l->l->data >= '2' && this->l->l->data <= '8' && this->l->r->data >= 'a' && this->l->r->data <= 'z' && this->r->l->data >= '2' && this->r->l->data <= '8' && this->r->r->data >= 'a' && this->r->r->data <= 'z' && this->l->r->data == this->r->r->data)
				{
					this->data = '*';
					this->l->data = (char)((((int)this->l->data - (int)48) * 2) + (int)48);
					this->r->data = this->r->r->data;
				}
				else
				{
					std::cout << "Error! this->data >= 10! Can't transform expression!\n";
				}
			}
		}*/
	}
	if (this->data == '+' && this->l->data == this->r->data && this->l->data >= 'a' && this->l->data <= 'z' && this->r->data >= 'a' && this->r->data <= 'z')
	{
		this->data = '*';
		this->l->data = '2';
	}
	else if (this->data == '+' && this->l->data == '*' && this->r->data == '*')
	{
		if (this->l->l->data >= '2' && this->l->l->data < '8' && this->l->r->data >= 'a' && this->l->r->data <= 'z' && this->r->l->data >= '2' && this->r->l->data < '8' && this->r->r->data >= 'a' && this->r->r->data <= 'z' && this->l->r->data == this->r->r->data)
		{
			this->data = '*';
			this->l->data = (char)((((int)this->l->l->data - (int)48) * 2) + (int)48);
			this->r->data = this->r->r->data;
			this->l->l->destroy();
			this->l->r->destroy();
			this->l->l = nullptr;
			this->l->r = nullptr;
			this->r->l->destroy();
			this->r->r->destroy();
			this->r->l = nullptr;
			this->r->r = nullptr;
		}
		else
		{
			std::cout << "Error! this->data >= 10! Can't transform expression!\n";
		}
	}

	/*if (!this->l->IsNull() && !this->r->IsNull())
	{
		if (this->data == '+' && this->l->data == this->r->data && this->l->data >= 'a' && this->l->data <= 'z' && this->r->data >= 'a' && this->r->data <= 'z')
		{
			this->data = '*';
			this->l->data = '2';
		}
		this->l->change();
		this->r->change();
	}*/
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

template<>
BinaryTree<char>::~BinaryTree()
{
}