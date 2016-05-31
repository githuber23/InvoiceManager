#define D_SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#include "Lexer.h"
#include <string>
using namespace std;

void Lexer::GetLexems(string s, string * lexems, int * count)
{
	int countOfDividers = std::count(s.begin(), s.end(), ';');//узнаем количество точек с запятой в строке s
	size_t divider;
	for (int i = 0; i < countOfDividers; i++)
	{
		if (countOfDividers == 0)
		{
			 // error. 
		}
		//header situation(если нашло 1 разделитель, значит мы на хедере)
		if (countOfDividers == 1)
		{
			size_t insideDivider = s.find(':');
			lexems[0] = s.substr(0,insideDivider);//Достает всё до первого символа ':' в хедере
			string secondPart = s.substr(insideDivider+1, s.length()- insideDivider-1);//считываем вторую часть строки(после раделителя)
			size_t numberPos = s.find_last_of(' ');//ищем последний пробел
			if (numberPos != string::npos)//если мы нашли хоть какие-то пробелы(npos- не найдено)
			{
				lexems[1] = s.substr(numberPos + 1, s.length() - numberPos-2);//тогда мы присваиваем первому элементу масива вторую подстроку
			}
		}
	}
}
//
//int findIndexOfCharInString(string s, char symbol)//находит индекс символа в строке
//{
//	for (int i = 0; i < s.length(); i++)
//	{
//		if (s[i] == symbol)
//			return i;
//	}
//
//	return -1;
//}
//
//void stringCopy(char* from, char* to, int count)
//{
//	for (int i = 0; i < count; i++)
//	{
//		to[i] = from[i];
//	}
//	if (strlen(to) > count)//убираем часть строки, которая, возможно, осталась после замены старой строки новой
//	{
//		to[count] = '\0';
//	}
//}
//
//
//bool isNumber(string str)// проверка числа(является ли строка числом)
//{
//	for (int i = 0; i < str.length(); i++)
//	{
//		int value = (int)str[i];
//		if (value > '9' || value < '0')
//		{
//			return false;
//		}
//		else if (value == '0' && str.length() > 1 && i == 0)//случай, когда у нас число имеет больше одного символа но начинается с нуля
//			return false;
//	}
//
//	return true;
//}
//
//bool isTitle(const char* title, const char* templ)//templ- константы, объявленные ранее(константы хедера, футера и тд)
//{
//	if (strncmp(templ, title, strlen(templ)) != 0)// string to char array- переводим стринг в массив чаров
//		return false;
//	//strncmp - сравнивает символы двух строк. Здесь принимаем на вход:1) символы нормального хедера, 2)символы проверяемого хедера
//	//3)количество символов, которые будем проверять(у нас это количество символов в нормальном хедере).
//	title += strlen(templ);//перемещаем наш указатель на начало числа в хедере
//	if (!isNumber(title))
//		return false;
//
//	return true;
//}

//
//bool Lexer::IsTitlesExist(string* text, int size)
//{
//	if (size <= 1)
//		return false;
//
//
//	//Ищем header
//	string title = text[0];
//	//и максимальное количество символов для считки(метод языка C, который содержится в string)
//	if (!isTitle(title.c_str(), invoiceContainer->HEADER.c_str()))//"если наша строка не содержит второй аргумент и интовое число то это не заголовок"
//		return false;
//	// Ищем footer
//
//	title = text[size - 1];//проверяем наличие тайтла для последней строки
//
//	//dividerPosition- указывает позицию точки с запятой, до которой должна быть считана часть футера
//	int dividerPosition = findIndexOfCharInString(title, ';');
//	if (dividerPosition == -1)
//		return false;
//
//	char* totalCost = new char[2047];
//	char* totalCountOfRows = new char[2047];
//	title.copy(totalCost, dividerPosition);
//	totalCost[dividerPosition] = '\0';
//	//Если введенный нами тайтл не является FOOTER_1, то возвращаем false
//	if (!isTitle(totalCost, invoiceContainer->FOOTER_1.c_str())) //total cost - это первый футер
//		return false;
//
//	//перемещаем указатель на начало FOOTER_2, чтобы работать с ним.
//	title.copy(totalCountOfRows, title.length() - dividerPosition, dividerPosition);
//	totalCountOfRows[title.length() - dividerPosition] = '\0';
//	if (!isTitle(totalCountOfRows, invoiceContainer->FOOTER_2.c_str()))
//		return false;
//
//	return true;
//}







