#define D_SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#include "Lexer.h"
#include <string>
using namespace std;

void Lexer::GetLexems(string s, string * lexems, int * count)
{
	int countOfDividers = std::count(s.begin(), s.end(), ';');//узнаем количество точек с запятой в строке s
	size_t divider;

	string str = s;
	for (int i = 0, j = 0; i < countOfDividers; i++, j+=2)
	{
		size_t insideDivider = str.find_first_of(';');
		lexems[j] = str.substr(0, insideDivider);
		str = str.substr(insideDivider + 1, str.length() - insideDivider);
		//делим подфразу на заглавие и число(номер накладной)
		insideDivider = lexems[j].find_first_of(':');
		string firstPart = lexems[j].substr(0, insideDivider);//Достает всё до первого символа ':' в хедере
		string secondPart = lexems[j].substr(insideDivider + 1, lexems[j].length() - insideDivider - 1);
		// Имена будут на каждых парных местах. Значения будут на каждых непарных
		lexems[j] = firstPart;
		lexems[j+1] = secondPart;


		// Удаляем пробелы
		do
		{
			if (lexems[j][0] == ' ')
				lexems[j] = lexems[j].substr(1, lexems[j].length()-1);

			if (lexems[j+1][0] == ' ')
				lexems[j+1] = lexems[j+1].substr(1, lexems[j+1].length() - 1);
		} 
		while (lexems[j][0] == ' ' || lexems[j+1][0] == ' ');

		// Если у нас 2 лексемы, то мы по циклу пройдем 1 раз при j=0. В массиве будет 2 элемента
		*count = j + 2;
	}
}

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






