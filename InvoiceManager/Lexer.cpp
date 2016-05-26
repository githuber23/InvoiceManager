#define D_SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#include "Lexer.h"
#include <string>
using namespace std;


int findIndexOfCharInString(string s, char symbol)//������� ������ ������� � ������
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == symbol)
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

bool Lexer::IsTitlesExist(string* text, int size)
{
	if (size <= 1)
		return false;


	//���� header
	string title = text[0];
	//� ������������ ���������� �������� ��� ������(����� ����� C, ������� ���������� � string)
	if (!isTitle(title.c_str(), invoiceContainer->HEADER.c_str()))//"���� ���� ������ �� �������� ������ �������� � ������� ����� �� ��� �� ���������"
		return false;
	// ���� footer

	title = text[size - 1];//��������� ������� ������ ��� ��������� ������

	//dividerPosition- ��������� ������� ����� � �������, �� ������� ������ ���� ������� ����� ������
	int dividerPosition = findIndexOfCharInString(title, ';');
	if (dividerPosition == -1)
		return false;

	char* totalCost = new char[2047];
	char* totalCountOfRows = new char[2047];
	title.copy(totalCost, dividerPosition);
	totalCost[dividerPosition] = '\0';
	//���� ��������� ���� ����� �� �������� FOOTER_1, �� ���������� false
	if (!isTitle(totalCost, invoiceContainer->FOOTER_1.c_str())) //total cost - ��� ������ �����
		return false;

	//���������� ��������� �� ������ FOOTER_2, ����� �������� � ���.
	title.copy(totalCountOfRows, title.length() - dividerPosition, dividerPosition);
	totalCountOfRows[title.length() - dividerPosition] = '\0';
	if (!isTitle(totalCountOfRows, invoiceContainer->FOOTER_2.c_str()))
		return false;

	return true;
}







