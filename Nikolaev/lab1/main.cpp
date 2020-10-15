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

bool brackets(std::string expression, int& index);
bool isSquareBrackets(std::string expression, int& index);
bool isRoundBrackets(std::string expression, int& index);
bool isFiguredBrackets(std::string expression, int& index);


bool brackets(std::string expression, int& index)
{
	bool isExpression = false;
	if (expression[index] == '[')
	{
		index += 1;
		isExpression = isSquareBrackets(expression, index);
	}
	else if (expression[index] == '(')
	{
		index += 1;
		isExpression = isRoundBrackets(expression, index);
	}
	else if (expression[index] == '{')
	{
		index += 1;
		isExpression = isFiguredBrackets(expression, index);
	}
	return isExpression;
}

bool isSquareBrackets(std::string expression, int& index)
{
	bool b = false;
	if (expression[index] == '(') {
		index += 1;
		b = isRoundBrackets(expression, index);
		if (b == true) {
			if (expression[index] == '{') {
				index += 1;
				b = isFiguredBrackets(expression, index);
				if (expression[index] == ']')
				{
					b = true;
				}
				else b = false;
			}
			else b = false;
			index += 1;

		}
	}
	else if (expression[index] == '+') {
		b = true;
		index += 1;
		if (expression[index] != ']') {
			b = false;
		}
		index += 1;
	}
	return b;
}

bool isRoundBrackets(std::string expression, int& index)
{
	bool b = false;
	if (expression[index] == '{') {
		index += 1;
		b = isFiguredBrackets(expression, index);
		if (b == true) {
			if (expression[index] == '[') {
				index += 1;
				b = isSquareBrackets(expression, index);
				if (expression[index] == ')')
				{
					b = true;
				}
				else b = false;
			}
			else b = false;
			index += 1;

		}
	}
	else if (expression[index] == '-') {
		b = true;
		index += 1;
		if (expression[index] != ')') {
			b = false;
		}
		index += 1;
	}
	return b;
}

bool isFiguredBrackets(std::string expression, int& index)
{
	bool b = false;
	if (expression[index] == '[') {
		index += 1;
		b = isSquareBrackets(expression, index);
		if (b == true) {
			if (expression[index] == '(') {
				index += 1;
				b = isRoundBrackets(expression, index);
				if (expression[index] == '}')
				{
					b = true;
				}
				else b = false;
			}
			else b = false;
			index += 1;
		}
	}
	else if (expression[index] == '0') {
		b = true;
		index += 1;
		if (expression[index] != '}') {
			b = false;
		}
		index += 1;
	}
	return b;
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
		if (!brackets(expression, index) || expression.length() != index)
		{
			fileOut << std::endl << std::setw(offset) << std::left << expression << std::setw(offset) << std::left << "No";
			//std::cout << " = No\n";
			std::cout << std::endl << std::setw(offset) << std::left << expression << std::setw(offset) << std::left << "No";
		}
		else
		{
			fileOut << std::endl << std::setw(offset) << std::left << expression << std::setw(offset) << std::left << "Yes";
			//std::cout << " = Yes\n";
			std::cout << std::endl <<std::setw(offset) << std::left << expression << std::setw(offset) << std::left << "Yes";
		}


		expression.clear();
		index = 0;
	}

	fileIn.close();
	fileOut.close();

	return 0;
}