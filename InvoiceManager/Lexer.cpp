#include "Lexer.h"
#include <string>
using namespace std;


int findIndexOfCharInString(char* str, char symbol)//находит индекс символа в строке
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
	if (strlen(to) > count)//убираем часть строки, которая, возможно, осталась после замены старой строки новой
	{
		to[count] = '\0';
	}
}


bool isNumber(string str)// проверка числа(является ли строка числом)
{
	for (int i = 0; i < str.length(); i++)
	{
		int value = (int)str[i];
		if (value > '9' || value < '0')
		{
			return false;
		}
		else if (value == '0' && str.length() > 1 && i == 0)//случай, когда у нас число имеет больше одного символа но начинается с нуля
			return false;
	}

	return true;
}

bool isTitle(const char* title, const char* templ)//templ- константы, объявленные ранее(константы хедера, футера и тд)
{
	if (strncmp(templ, title, strlen(templ)) != 0)// string to char array- переводим стринг в массив чаров
		return false;
	//strncmp - сравнивает символы двух строк. Здесь принимаем на вход:1) символы нормального хедера, 2)символы проверяемого хедера
	//3)количество символов, которые будем проверять(у нас это количество символов в нормальном хедере).
	title += strlen(templ);//перемещаем наш указатель на начало числа в хедере
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
	char* title = new char[2047];// массив символов отвечающий за хедер и футер вместе
	if (stream->eof())
		return false;
	//Ищем header
	stream->getline(title, 2047);//функция считки, которая принимает два параметра: массив, в который считывает
	//и максимальное количество символов для считки(метод языка C, который содержится в string)
	if (!isTitle(title, invoiceContainer->HEADER.c_str()))//"если наша строка не содержит второй аргумент и интовое число то это не заголовок"
		return false;
	// Ищем footer

	while (!stream->eof())
	{
		stream->getline(title, 2047);
	}

	char* totalCost = new char[2047];

	//dividerPosition- указывает позицию точки с запятой, до которой должна быть считана часть футера
	int dividerPosition = findIndexOfCharInString(title, ';');
	if (dividerPosition == -1)
		return false;

	stringCopy(title, totalCost, dividerPosition);
	//Если введенный нами тайтл не является FOOTER_1, то возвращаем false
	if (!isTitle(totalCost, invoiceContainer->FOOTER_1.c_str())) //total cost - это первый футер
		return false;

	//перемещаем указатель на начало FOOTER_2, чтобы работать с ним.
	title += dividerPosition;
	if (!isTitle(title, invoiceContainer->FOOTER_2.c_str()))
		return false;

	return true;
}







