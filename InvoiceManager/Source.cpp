#include <iostream>
#include "InvoiceContainer.h"
using namespace std;

void main()
{
	InvoiceContainer ic;
	InvoiceItem* i1 = new InvoiceItem();//new - ���������� ������� � ����.
	InvoiceItem* i2 = new InvoiceItem();
	InvoiceItem* i3 = new InvoiceItem();
	InvoiceItem* i4 = new InvoiceItem();
	InvoiceItem* i5 = new InvoiceItem();
	i1->SetCost(100);
	ic.Add(i1);
	ic.Add(i2);
	ic.Add(i3);
	ic.Add(i4);
	ic.Add(i5);
	
	ic.Print("file.txt");
	ic.Print("");
	ic.Clear();





	system("pause");
}