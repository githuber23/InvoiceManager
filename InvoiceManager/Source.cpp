#include <iostream>
#include "InvoiceContainer.h"
using namespace std;

void main()
{
	InvoiceContainer ic;
	InvoiceItem* i1 = new InvoiceItem(1);//new - размещение объекта в куче.
	InvoiceItem* i2 = new InvoiceItem(2);
	InvoiceItem* i3 = new InvoiceItem(3);
	InvoiceItem* i4 = new InvoiceItem(4);
	InvoiceItem* i5 = new InvoiceItem(5);
	
	ic.Add(i1);
	ic.Add(i2);
	ic.Add(i3);
	ic.Add(i4);
	ic.Add(i5);
	ic.Clear();




	system("pause");
}