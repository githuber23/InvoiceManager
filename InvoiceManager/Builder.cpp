#include <iostream>
#include <fstream>
#include "Builder.h"
using namespace std;

// Header
const string HEADER = "Total count of cheks";
// Body
const string NUMBER_OF_INVOICE = "Number";
const string QUANTITY = "Quantity of goods";
const string PRICE = "Price of product";
const string COST = "Cost of product";
// Footer
const string TOTAL_COST = "Total cost";
const string TOTAL_COUNT_OF_ROWS = "Total count of rows";
const int LENGTH_OF_INVOICE_NUMBER = 13;

bool Builder::isInt(string value)
{
	try
	{
		// stoi(value) ��������� �������� value � ���� int
		// ���� ���������� �� �������� (���� � value ���� �� �����, �� ������� �����)
		// �� ������������ ���������� ������ �-��� stoi
		int v = stoi(value);
		// ������� � ����� �����
		size_t dot = value.find('.');
		// ���� ����� �������, ������ ����� �� �����
		if (dot != string::npos)
		{
			return false;
		}
	}
	catch (const std::invalid_argument& ia)
	{
		// ���� ���������� �� �������, ������ value - �� �����
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
		// ������� � ����� �����
		size_t dot = value.find('.');
		// ���� ����� �������, ������ ����� �� �����
		if (dot == string::npos)
		{
			return false;
		}

		int expectedCountOfNumberAfterDot = value.length() - dot-1;
		// ������������� ����� ���� ����� �������
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

bool Builder::checkNote(string title, string value)
{
	if (title == HEADER || title == TOTAL_COUNT_OF_ROWS)
	{
		if (isInt(value))
			return true;
		
		return false;
	}
	else if (title == NUMBER_OF_INVOICE)
	{
		if (isNumberOfInvoice(value))
			return true;

		return false;
	}
	else if (title == QUANTITY)
	{
		// ��������� 2 � ������ ������ ����� �������
		// false - ����� ���� ������ ��� 2 ����� (�� ������������� ���-�� ������ ����� �������, �� ������ ���� ����� 2)
		if (isDouble(value, 2, false))
			return true;

		return false;
	}
	else if (title == PRICE)
	{

	}
	else if (title == COST)
	{

	}
	else if (title == TOTAL_COST)
	{

	}
	else
	{
		return false;
	}
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
		stream->getline(temp, 2047);
		string* s = new string(temp);
		string* lexems = new string[10];
		int countOfLexems;
		lexer->GetLexems(*s, lexems, &countOfLexems);
		for (int i = 0; i < countOfLexems; i++)
		{
			cout << lexems[i] << endl;
		}

		for (int i = 0; i < countOfLexems; i+=2)
		{
			checkNote(lexems[i], lexems[i + 1]);
		}

		count++;
	}
}
