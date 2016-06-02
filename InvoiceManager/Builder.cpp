#include <iostream>
#include <fstream>
#include "Builder.h"
#include "Constants.h"
using namespace std;



bool Builder::isInt(string value)
{
	try
	{
		// stoi(value) попробует привести value к типу int
		// если приведение не возможно (если в value есть не цифры, не включа€ точку)
		// то генерируетс€ исключение внутри ф-ции stoi
		int v = stoi(value);
		// находим в числе точку
		size_t dot = value.find('.');
		// если точка найдена, значит число не целое
		if (dot != string::npos)
		{
			return false;
		}
	}
	catch (const std::invalid_argument& ia)
	{
		// если приведение не удалось, значит value - не число
		return false;
	}
}

bool Builder::isNumberOfInvoice(string value)
{
	if (value.length() != LENGTH_OF_INVOICE_NUMBER)
		return false;

	for (int i = 0; i < value.length(); i++)
	{
		if (!(value[i] >= '0' && value[i] <= '9')
			&& !(value[i] >= 'a' && value[i] <= 'z')
			&& !(value[i] >= 'A' && value[i] <= 'Z'))
			return false;
	}

	return true;
}

bool Builder::isDouble(string value, int countOfNumberAfterDot, bool fixed)
{
	try
	{
		// string to double
		double v = stod(value);
		// находим в числе точку
		size_t dot = value.find('.');
		// если точка найдена, значит число не целое
		if (dot == string::npos)
		{
			return false;
		}

		int expectedCountOfNumberAfterDot = value.length() - dot-1;
		// фиксированное число цифр после зап€той
		if (fixed)
		{
			if (expectedCountOfNumberAfterDot != countOfNumberAfterDot)
				return false;
		}
		else
		{
			if (expectedCountOfNumberAfterDot > countOfNumberAfterDot)
				return false;
		}
	}
	catch (const std::invalid_argument& ia)
	{
		return false;
	}
}

void Builder::checkNote(string title, string value, string* error)//ѕ–овер€ем записи на соответсвие ЅЌ‘
{
	bool isCorrect = false;//благодар€ тому, что значение false - мы можем не писать else в нижних ифах

	if (title == HEADER || title == TOTAL_COUNT_OF_ROWS)
	{
		if (isInt(value))
			isCorrect = true;//ошибки не будет, если всЄ правильно
	}
	else if (title == NAME_OF_INVOICE)
	{
		if (value.length() > 0)
			isCorrect = true;
	}
	else if (title == NUMBER_OF_INVOICE)
	{
		if (isNumberOfInvoice(value))
			isCorrect = true;
	}
	else if (title == QUANTITY)
	{
		// принимаем 2 и меньше знаков после зап€той
		// false - может быть меньше чем 2 знака (не фиксированное кол-во знаков после зап€той, но меньше либо равно 2)
		if (isDouble(value, 2, false))
			isCorrect = true;
	}
	else if (title == PRICE || title == COST || title == TOTAL_COST)
	{
		if(isDouble(value, 2,true))
			isCorrect = true;
	}
	else
	{
		*error = "Semantic error. For '" + title + "' title is wrong";
		return;
	}

	if (!isCorrect)
		*error = "Syntax error. For '" + title + "' value '" + value + "' is wrong";
}

Builder::Builder()
{
	invoiceContainer = new InvoiceContainer();
	lexer = new Lexer();
}

void Builder::ReadFile(string fileName)
{
	ifstream* stream = new ifstream(fileName);
	int count = 0;
	char* temp = new char[2047];
	while (!stream->eof())
	{
		count++;
		stream->getline(temp, 2047);
		if (!strcmp(temp, ""))//игнорируем пустые строки
			continue;

		string* s = new string(temp);
		string* lexems = new string[10];
		int countOfLexems;
		lexer->GetLexems(*s, lexems, &countOfLexems);

		for (int i = 0; i < countOfLexems; i+=2)
		{
			string error = "";
			checkNote(lexems[i], lexems[i + 1], &error);
			if (error != "")
			{
				cout << error << endl;
				cout << "Error is situated on " << count << " row" << endl;
				return;
			}
		}
	}
}
