#include <iostream>
#include <fstream>
#include "Builder.h"
#include "Constants.h"
using namespace std;



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

void Builder::checkNote(string title, string value, string* error)//��������� ������ �� ����������� ���
{
	bool isCorrect = false;//��������� ����, ��� �������� false - �� ����� �� ������ else � ������ ����

	if (title == HEADER || title == TOTAL_COUNT_OF_ROWS)
	{
		if (isInt(value))
			isCorrect = true;//������ �� �����, ���� �� ���������
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
		// ��������� 2 � ������ ������ ����� �������
		// false - ����� ���� ������ ��� 2 ����� (�� ������������� ���-�� ������ ����� �������, �� ������ ���� ����� 2)
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
		if (!strcmp(temp, ""))//���������� ������ ������
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
