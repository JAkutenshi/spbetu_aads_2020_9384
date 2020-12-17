#include <iostream>
#include <fstream>
#include "hier_list.h"

using namespace std;
using namespace H_list;


int main()
{
	list s;
	char ch;
	char atom_1, atom_2;
	cout << "Choose input method:\n\t1 - from \"input.txt\"\n\t2 - from console\n\t3 - exit\n";
	cin >> ch;
	switch (ch){
	case '1':
		file_readlist(s);
		cout << "Your list:\n\t";
		write_list(s);
		break;
	case '2':
		cout << "Input your list:\n\t";
		read_list(s);
		break;
	case '3':
		return 0;
	default:
		cout << "Wrong argument\n";
		return 0;
	}
	cout << "\nInput atoms you would change:\n\t";
	cin >> atom_1 >> atom_2;
	change(s, atom_1, atom_2);
	cout << "\nEdited list:\n\t";
	write_list(s);
	cout << "\n";
	destroy(s);
	return 0;
}
