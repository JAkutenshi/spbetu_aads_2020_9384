#include <iostream>
#include <cstdlib>
#include "h_list.h"

using namespace std;
using namespace h_list;

int main()
{
	lisp expr;
	cout << "Enter list:" << "\n";
	read_lisp(expr);
	cout << "Introduced list: " << "\n";
	write_lisp(expr);
	cout << "\n";
	expr = h_list::reverse(expr);
	cout << "Reversed list:" << "\n";
	write_lisp(expr); cout << "\n";
	return 0;
}
	
