#ifndef TREAP_H
#define TREAP_H

#include <iostream>


template <typename base>
class treap
{
public:
	treap():key(0), priority(0), left(nullptr), right(nullptr) {};
	treap(base key, int priority) : key(key), priority(priority), left(nullptr), right(nullptr) {};

	void insert(base key)
	{
		InsertTree(root, new treap<base>(key, rand()));
	}

	int find(base key)
	{
		count = 0;
		return FindTree(root, key);
	}

	void print()
	{
		PrintTree(root, 0);
	}

	int HeightTree() {
		if (this->left && this->right)
			return this->left->HeightTree() > this->right->HeightTree() ? 1 + this->left->HeightTree() : 1 + this->right->HeightTree();
		else if (this->left) {
			return 1 + this->left->HeightTree();
		}
		else if (this->right) {
			return 1 + this->right->HeightTree();
		}
		else return 1;
	}

private:
	void split(treap* t, base& key, treap*& left, treap*& right)
	{
		if (t == nullptr)
		{
			left = right = nullptr;
		}
		else if (key < t->key)
		{
			split(t->left, key, left, t->left);
			right = t;
		}
		else
		{
			split(t->right, key, t->right, right);
			left = t;
		}
	}

	void merge(treap*& t, treap* left, treap* right)
	{
		if (!left || !right)
			t = left ? left : right;
		else if (left->priority >= right->priority)
		{
			merge(left->right, left->right, right);
			t = left;
		}
		else
		{
			merge(right->left, left, right->left);
			t = right;
		}
	}

	void InsertTree(treap*& t, treap* it)
	{
		if (t == nullptr)
		{
			t = it;
			return;
		}

		if (it->priority > t->priority)
		{
			split(t, it->key, it->left, it->right);
			t = it;
		}
		else
		{
			InsertTree(it->key < t->key ? t->left : t->right, it);
		}
	}

	int FindTree(treap*& t, base key)
	{
		if (t != nullptr)
		{
			if (t->key == key)
			{
				count += 1;
				FindTree(t->left, key);
				FindTree(t->right, key);
			}
			else if (t->key > key)
			{
				FindTree(t->left, key);
			}
			else
			{
				FindTree(t->right, key);
			}
		}
		return count;
	}

	void PrintTree(treap*& t, int level)
	{
		if (t)
		{
			if (!t) return;
			level += 5;
			PrintTree(t->left, level);
			for (int i = 0; i < level; i++) std::cout << " ";
			if(t->left && t->right)
				std::cout << t->key << '<' <<std::endl;
			else if (t->left)
				std::cout << t->key << '/' << std::endl;
			else if (t->right)
				std::cout << t->key << '\\' << std::endl;
			else
				std::cout << t->key << std::endl;
			PrintTree(t->right, level);
			level -= 5;
			return;
		}
	}

	base key;
	int priority;
	treap* left, *right;
	treap* root = nullptr;
	size_t count;
};
#endif // treap_H