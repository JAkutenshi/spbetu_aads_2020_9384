#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "BT.h"

std::ifstream infile;
template<class base>
void printBT(BT<base>* head);

int main() {
	infile.open("text.txt");
	if (!infile.is_open()) return 4;

	BT<char> head;
	std::string tmp;
	
	infile >> tmp;
	
	head.createBT(tmp);
	printBT(&head);
	head.replacementBT();
	std::cout << '\n';
	printBT(&head);
	std::cout << '\n';
	system("pause");
	infile.close(); 
	return 0;
}

template<class base>
void printBT(BT<base>* head) {
	if (!head->IsNull()) {
		if (!head->left()->IsNull() && !head->right()->IsNull() && !(head->RootBT() >= 'a' && head->RootBT() <= 'z'))
			std::cout << '(';
		printBT(head->left());
		std::cout << head->RootBT();
		printBT(head->right());
		if (!head->left()->IsNull() && !head->right()->IsNull() && !(head->RootBT() >= 'a' && head->RootBT() <= 'z'))
			std::cout << ')';
		
	}
}

