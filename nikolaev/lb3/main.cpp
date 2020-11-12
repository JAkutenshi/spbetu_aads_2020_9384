#include <iostream>
#include <fstream>
#include <string>
#include "BinaryTree.h"

int main()
{
	BinaryTree bt;

	std::string tmp;
	std::cout << "Enter BT or FileName.txt: ";
	std::cin >> tmp;

	if (tmp.find(".txt", tmp.length() - 4) != std::string::npos)
	{
		std::ifstream in;
		in.open(tmp);
		std::getline(in, tmp);
		in.close();
	}

	bt.createBT(tmp);
	bt.printBT();

	std::cout << '\n';

	bt.change();
	bt.printBT();

	return 0;
}