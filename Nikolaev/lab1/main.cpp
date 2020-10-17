/*
12. ѕостроить синтаксический анализатор дл€ пон€ти€ скобки.
cкобки::=квадратные | круглые | фигурные
квадратные::=[круглые фигурные] | +
круглые::=(фигурные квадратные) | -
фигурные::={квадратные круглые} | 0
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

bool isSquareBrackets(std::string expression, int& index);
bool isRoundBrackets(std::string expression, int& index);
bool isFiguredBrackets(std::string expression, int& index);

bool isSquareBrackets(std::string expression, int& index)
{
	if (expression[index++] == ']')
		return true;
	else
		index--;

	if (expression[index++] == '+')
		return true;
	else
		index--;

	if (expression[index++] == '[')
	{
		if (isRoundBrackets(expression, index) && isFiguredBrackets(expression, index) && isSquareBrackets(expression, index))
			return true;
	}

	index--;
	return false;
}

bool isRoundBrackets(std::string expression, int& index)
{
	if (expression[index++] == ')')
		return true;
	else
		index--;

	if (expression[index++] == '-')
		return true;
	else
		index--;

	if (expression[index++] == '(')
	{
		if (isFiguredBrackets(expression, index) && isSquareBrackets(expression, index) && isRoundBrackets(expression, index))
		return true;
	}

	index--;
	return false;
}

bool isFiguredBrackets(std::string expression, int& index)
{
	if (expression[index++] == '}')
		return true;
	else
		index--;

	if (expression[index++] == '0')
		return true;
	else
		index--;

	if (expression[index++] == '{')
	{
		if (isSquareBrackets(expression, index) && isRoundBrackets(expression, index) && isFiguredBrackets(expression, index))
			return true;
	}

	index --;
	return false;
}

int main()
{
	int index = 0;
	std::string expression;
	std::string filePath;

	std::cout << "Enter fileIn path: ";
	std::cin >> filePath;

	std::ifstream fileIn(filePath);

	if (!fileIn)
	{
		std::cout << "File cannot be opened!\n";
		return 1;
	}

	int offset = 0;
	while (getline(fileIn, expression))
	{
		if (offset < expression.length())
			offset = expression.length();
	}
	offset += 5;

	fileIn.clear();
	fileIn.seekg(0);

	std::cout << "Enter fileOut Path: ";
	std::cin >> filePath;

	std::ofstream fileOut(filePath);

	while (getline(fileIn, expression))
	{
		if (isSquareBrackets(expression, index) || isRoundBrackets(expression, index) || isFiguredBrackets(expression, index) || expression.length() == index)
		{
			fileOut << std::endl << std::setw(offset) << std::left << expression << std::setw(offset) << std::left << "Yes";
			std::cout << std::endl << std::setw(offset) << std::left << expression << std::setw(offset) << std::left << "Yes";
		}
		else
		{
			fileOut << std::endl << std::setw(offset) << std::left << expression << std::setw(offset) << std::left << "No";
			std::cout << std::endl << std::setw(offset) << std::left << expression << std::setw(offset) << std::left << "No";
		}


		expression.clear();
		index = 0;
	}

	fileIn.close();
	fileOut.close();

	return 0;
}