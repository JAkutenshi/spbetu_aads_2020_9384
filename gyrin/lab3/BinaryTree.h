#pragma once
int amount = 0;
template <typename T>
class BinaryTree {
private:
	T root;
	BinaryTree* left;
	BinaryTree* right;
	int level;

	void NumOfNodes(int n) {

		if (!this->left->isNull()) {
			this->left->NumOfNodes(n);
		}
		if (!this->right->isNull()) {
			this->right->NumOfNodes(n);
		}
		if (this->level == n) {
			amount++;
		}
	}

	bool isNull() {
		return this == nullptr;
	}

public:
	BinaryTree()
	{
		this->left = nullptr;
		this->right = nullptr;
		this->level = 1;
	}

	void PrintBT() {
		if (!this->isNull()) {
			std::cout << this->root;
			this->left->PrintBT();
			this->right->PrintBT();
		}
	}

	void ConsBT(std::string& tmp, int count) {
		if (!tmp.empty()) {
			if (tmp.front() == '(' && (tmp[1] == '/' || tmp[1] == ' ')) {
				if (tmp[2] != ')') {
					std::cout << "Input Error";
					exit(-2);
				}
				this->level = NULL;
				tmp.erase(0, 3);
				return;
			}
			else if (tmp.front() == '(' && tmp[1]) {
				this->root = tmp[1];
				count += this->level;
				this->level = count;
				tmp.erase(0, 2);
				if (tmp.front() == '(') {
					this->left = new BinaryTree;
					this->left->ConsBT(tmp,count);
				}
				if (!tmp.empty() && tmp.front() == '(') {
					this->right = new BinaryTree;
					this->right->ConsBT(tmp,count);
				}
				if (!tmp.empty()) {
					if (tmp.front() == ')'){
						tmp.erase(0, 1);
					}
				}
				else {
					std::cout << "Input Error";
					exit(-1);
				}
			}
			else {
				std::cout << "Input Error";
				exit(1);
			}
		}
	}

	void PrintL() {
		if (this->left->isNull() && this->right->isNull()) {
			std::cout << this->root;
		}
		else {
			if (!this->left->isNull()) {
				this->left->PrintL();
			}
			if (!this->right->isNull()) {
				this->right->PrintL();
			}
		}
	}

	void PrintNumOfNodes(int n) {
		NumOfNodes(n);
		std::cout << "Nodes on " << n << " level: " << amount;
	}

};
