#include <iostream>
#include <string>
#include "Builder.h"
using namespace std;

void main()
{
	Builder b;
	b.ReadFile("file.txt");
	b.Print("");
	b.Print("result.txt");
	
	//InvoiceContainer* ic = new InvoiceContainer();
	//ic->push("123", "Item1", 1, 1, 1);
	//ic->push("123", "Item2", 1, 1, 1);
	//ic->print(ic->begin(), ic->end());
	//InvoiceItem* i1 = new InvoiceItem();//new - ���������� ������� � ����.

	//InvoiceItem* i2 = new InvoiceItem();
	//InvoiceItem* i3 = new InvoiceItem();
	//InvoiceItem* i4 = new InvoiceItem();
	//InvoiceItem* i5 = new InvoiceItem();
	//i1->SetCost(100);
	//ic.Add(i1);
	//ic.Add(i2);
	//ic.Add(i3);
	//ic.Add(i4);
	//ic.Add(i5);
	//
	//ic.Print("file.txt");
	//ic.Print("");
	//ic.Clear();

	

	//stream = new ifstream("file.txt");
	//string* text = new string[count];
	//for (int i = 0; i < count; i++)
	//{
	//	getline(*stream, text[i]);
	//}

	//string* text1 = new string[1]
	//{
	//	"Total cost: 100; Total count of rows: 27"
	//};
	//string* text2 = new string[2]
	//{
	//	"Total count of cheks: 5",
	//	"Total cost: 100; Total count of rows: 27"
	//};
	//string* text3 = new string[2]
	//{
	//	"Total count of 12cheks : 5",
	//	"Total cost: 100; Total count of rows: 27"
	//};

	//string* text4 = new string[2]
	//{
	//	"Total count of cheks: 5",
	//	"Total cost: 100; Total count of rows: 27"
	//};

	//cout << l.IsTitlesExist(text1, 1);//������ ��������- ���������� �����
	//cout << l.IsTitlesExist(text2, 2);
	//cout << l.IsTitlesExist(text3, 2);
	//cout << l.IsTitlesExist(text4, 2);



	system("pause");
}