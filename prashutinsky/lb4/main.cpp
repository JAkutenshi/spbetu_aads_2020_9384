#include <iostream>
#include <fstream>
#include <string>

template<typename base>
void Merge(base *A, int first, int last)
{
	int middle = 0, start = 0, final = 0;
	int n = last - first + 1;
	base *mas = new base[n];
	middle = (first + last) / 2;
	start = first;
	final = middle + 1;
	for (int j = first; j <= last; j++)
		if ((start <= middle) && ((final > last) || (A[start] < A[final])))
		{
			mas[j - first] = A[start];
			start++;
		}
		else
		{
			mas[j - first] = A[final];
			final++;
		}

	for (int j = first; j <= last; j++) A[j] = mas[j - first];
	delete[]mas;
}

template<typename base>
void MergeSort(base *A, int first, int last)
{
	if (first < last)
	{
		MergeSort(A, first, (first + last) / 2);
		MergeSort(A, (first + last) / 2 + 1, last);
		Merge(A, first, last);
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");

	std::ifstream input;
	std::string path;
	int c = 0;
	int  n;
	int *A;
	//���������� � ���������� ������������ �����
	/*std::ifstream imput;
	double *D = new double[100];
	imput.open("double.txt");
	
	for (int i = 0; i < 100; i++)
	{
		imput >> D[i];
	}
	for (int i = 0; i < 100; i++)
	{
		std::cout << D[i] << ' ';
	}
	MergeSort(D, 0, 100 - 1);
	std::cout << "\n\n";
	for (int i = 0; i < 100; i++)
	{
		std::cout << D[i] << ' ';
	}*/

	//���������� � ���������� ��������
	/*std::ifstream i�put;
	char *� = new char[100];
	i�put.open("char.txt");

	for (int i = 0; i < 100; i++)
	{
		i�put >> �[i];
	}
	for (int i = 0; i < 100; i++)
	{
		std::cout << �[i] << ' ';
	}
	MergeSort(�, 0, 100 - 1);
	std::cout << "\n\n";
	for (int i = 0; i < 100; i++)
	{
		std::cout << �[i] << ' ';
	}*/

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
	return 0;
}