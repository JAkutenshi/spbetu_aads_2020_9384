#include <iostream>
#include <fstream>
#include <string>
#include "BT.h"

std::ifstream infile;

void printBT(BT* head);

int main() {
	infile.open("text.txt");
	if (!infile.is_open()) return 4;

	BT head;
	std::string tmp;
	
	infile >> tmp;
	
	head.createBT(tmp);
	head.~BT();
	printBT(&head);
	head.replacementBT();
	std::cout << '\n';
	printBT(&head);
	std::cout << '\n';
	infile.close(); 
	return 0;
}

void printBT(BT* head) {
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

