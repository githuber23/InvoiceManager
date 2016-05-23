#include "Lexer.h"
#include <string>
using namespace std;


int findIndexOfCharInString(char* str, char symbol)//������� ������ ������� � ������
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == symbol)
			return i;
	}

	return -1;
}

void stringCopy(char* from, char* to, int count)
{
	for (int i = 0; i < count; i++)
	{
		to[i] = from[i];
	}
	if (strlen(to) > count)//������� ����� ������, �������, ��������, �������� ����� ������ ������ ������ �����
	{
		to[count] = '\0';
	}
}


bool isNumber(string str)// �������� �����(�������� �� ������ ������)
{
	for (int i = 0; i < str.length(); i++)
	{
		int value = (int)str[i];
		if (value > '9' || value < '0')
		{
			return false;
		}
		else if (value == '0' && str.length() > 1 && i == 0)//������, ����� � ��� ����� ����� ������ ������ ������� �� ���������� � ����
			return false;
	}

	return true;
}

bool isTitle(const char* title, const char* templ)//templ- ���������, ����������� �����(��������� ������, ������ � ��)
{
	if (strncmp(templ, title, strlen(templ)) != 0)// string to char array- ��������� ������ � ������ �����
		return false;
	//strncmp - ���������� ������� ���� �����. ����� ��������� �� ����:1) ������� ����������� ������, 2)������� ������������ ������
	//3)���������� ��������, ������� ����� ���������(� ��� ��� ���������� �������� � ���������� ������).
	title += strlen(templ);//���������� ��� ��������� �� ������ ����� � ������
	if (!isNumber(title))
		return false;

	return true;
}


Lexer::Lexer()
{
	invoiceContainer = new InvoiceContainer();
}

bool Lexer::IsTitlesExist(ifstream* stream)
{
	char* title = new char[2047];// ������ �������� ���������� �� ����� � ����� ������
	if (stream->eof())
		return false;
	//���� header
	stream->getline(title, 2047);//������� ������, ������� ��������� ��� ���������: ������, � ������� ���������
	//� ������������ ���������� �������� ��� ������(����� ����� C, ������� ���������� � string)
	if (!isTitle(title, invoiceContainer->HEADER.c_str()))//"���� ���� ������ �� �������� ������ �������� � ������� ����� �� ��� �� ���������"
		return false;
	// ���� footer

	while (!stream->eof())
	{
		stream->getline(title, 2047);
	}

	char* totalCost = new char[2047];

	//dividerPosition- ��������� ������� ����� � �������, �� ������� ������ ���� ������� ����� ������
	int dividerPosition = findIndexOfCharInString(title, ';');
	if (dividerPosition == -1)
		return false;

	stringCopy(title, totalCost, dividerPosition);
	//���� ��������� ���� ����� �� �������� FOOTER_1, �� ���������� false
	if (!isTitle(totalCost, invoiceContainer->FOOTER_1.c_str())) //total cost - ��� ������ �����
		return false;

	//���������� ��������� �� ������ FOOTER_2, ����� �������� � ���.
	title += dividerPosition;
	if (!isTitle(title, invoiceContainer->FOOTER_2.c_str()))
		return false;

	return true;
}







