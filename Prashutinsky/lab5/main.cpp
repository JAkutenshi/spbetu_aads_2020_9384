#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "treap.h"

int main()
{
	srand(time(0));
	std::ifstream input("test.txt");
	std::ofstream output("out.txt");
	std::string str;
	treap<char> root;
	char ch;
	int i = 0;
	std::cout << "Choise input(consol(C),file(F)):";
	std::cin >> ch;
	switch (ch)
	{
	case 'F':
	case 'f':

		if (!input.is_open()) {
			std::cerr << "File not open!\n";
			return 1;
			
		}
		input >> str;
		while (str[i] != '\0') {
			root.insert(str[i]);
			i++;
		}
		input.close();
		break;

	case 'C':
	case 'c':
		std::cout << "Enter string:";
		std::cin >> str;
		while (str[i] != '\n' && str[i] != '\0') {
			root.insert(str[i]);
			i++;
		}
		break;
	default:
		std::cout << "Unknown command!\n";
		break;
	}

	std::cout << root.find('f') << '\n';

	std::cout << "Treap is:" << '\n';
	root.print(output);

	
	system("pause");
	return 0;
}