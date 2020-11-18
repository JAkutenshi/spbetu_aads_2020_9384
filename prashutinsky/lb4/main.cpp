#include <iostream>
#include <fstream>
#include <string>
#include "MergeSort.h"

void main()
{
	setlocale(LC_ALL, "Rus");

	std::ifstream input;
	std::string path;
	int c = 0;
	int  n;
	int *A;


	std::cout << "�������� �����������:\n\t 1)�� �������\n\t 2)�� �����\n";
	while (!c) {
		std::cout << ">>>";
		std::cin >> c;
		switch (c)
		{
		case 1:
			std::cout << "������ ������� > ";
			std::cin >> n;
			A = new int[n];
			for (int i = 0; i < n; i++)
			{
				std::cout << i << " ������� > ";
				std::cin >> A[i];
			}
			MergeSort(A, 0, n - 1);
			std::cout << "������������� ������: "; 
			for (int i = 0; i < n; i++)
				std::cout << A[i] << " ";
			std::cout << "\n";
			delete[]A;
			break;

		case 2:
			std::cout << "������� ���� �� �����: ";
			std::cin >> path;
			input.open(path);
			if (input.is_open()) {
				input >> n;
				A = new int[n];
				for (int i = 0; i < n; i++)
				{
					input >> A[i];
				}
				MergeSort(A, 0, n - 1);
				std::cout << "������������� ������: ";
				for (int i = 0; i < n; i++)
					std::cout << A[i] << " ";
				std::cout << "\n";
				delete[]A;
			}
			else {
				std::cout << "���� �� ������!\n";
			}
			input.close();
			break;
		default:
			c = 0;
			break;
		}
	}
	system("pause");
}