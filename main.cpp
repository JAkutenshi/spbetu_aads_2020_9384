#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "treap.h"

int main()
{
	srand(time(0));
	std::ifstream input("test.txt");
	std::string str;
	treap<char> root;
	int i = 0;
	if (!input.is_open()) {
		std::cerr << "File not open!\n";
		return 1;
	}
	
	input >> str;
	
	
	
	while (str[i]!='\0') {
		root.insert(str[i]);
		i++;
	}
	std::cout << root.find('f') << '\n';

	std::cout << "Treap is:" << '\n';
	root.print();

	input.close();
	system("pause>>void");
	return 0;
}