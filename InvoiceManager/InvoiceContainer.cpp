#include "InvoiceContainer.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define NULL 0

const int LENGTH_OF_INVOICE_DETAILS = 5;
const int HEADER_AND_FOOTER_COUNT = 2;

InvoiceItem * InvoiceContainer::getItem(int index, InvoiceItem * current)
{
	if (index != 0)
		getItem(index - 1, current->Next);
	else
		return current;
}

void InvoiceContainer::printToConsole()
{
	cout << getHeader() << endl;
	for (int i = 0; i < count; i++)//проходим по каждому элементу контейнера(по каждой накладной)
	{
		InvoiceItem item = *GetItem(i);
		string* details = item.GetDetails();
		for (int strNum = 0; strNum < LENGTH_OF_INVOICE_DETAILS; strNum++)   //проходимся по каждой строке информации конкретной накладной
		{
			cout << details[strNum] << endl;//вывод конкретной строки с информацией
		}

		cout << "============================" << endl;
	}

	cout << getFooter() << endl;
}

void InvoiceContainer::printToFile(string fileName) 
{
	ofstream stream(fileName);//создается поток для записи в файл
	stream << getHeader() << endl << endl;
	for (int i = 0; i < count; i++)//проходим по каждому элементу контейнера(по каждой накладной)
	{
		InvoiceItem item = *GetItem(i);
		string* details = item.GetDetails();
		for (int strNum = 0; strNum < LENGTH_OF_INVOICE_DETAILS; strNum++)   //проходимся по каждой строке информации конкретной накладной
		{
			stream << details[strNum] << endl;//вывод конкретной строки с информацией
		}
		stream << "============================" << endl;

	}

	stream << getFooter() << endl;


}

int InvoiceContainer::getTotalCost()//считаем общую суму всех себестоимостей
{
	int sum = 0;
	for (int i = 0; i < count; i++)
		sum += GetItem(i)->GetCost();

	return sum;
}

string InvoiceContainer::getFooter()
{
	int countOfStrings = HEADER_AND_FOOTER_COUNT + LENGTH_OF_INVOICE_DETAILS*count; //получаем количество строк в файле
	return "Total cost: " + to_string(getTotalCost()) + ". Total count of rows: " + to_string(countOfStrings);
}

string InvoiceContainer::getHeader()
{
	return "Total count of cheks: " + to_string(count);
}

InvoiceContainer::InvoiceContainer()//конструктор по умолчанию
{
	count = 0;
	lastItem = NULL;
}

int InvoiceContainer::GetCount()
{
	return count;
}

InvoiceItem* InvoiceContainer::GetItem(int index)//получаем элемент по индексу
{
	if (index > count - 1)//последний элемент = каунт-1, так как считаем с нуля
		return NULL;

	return getItem(index, lastItem);
}


void InvoiceContainer::Add(InvoiceItem* item)
{
	if (lastItem == NULL)
	{
		lastItem = item;//ласт айтем- указатель на последний элемент контейнера
	}
	else
	{
		item->Next = lastItem;
		lastItem = item;//получили последний элемент и сказали, что наш новый элемент- следующий элемент для уже существующего в контейнере
	}

	count++;
}

void InvoiceContainer::Remove(InvoiceItem* item)
{

	if (count == 1)//случай, когда у нас один элемент
	{
		delete(lastItem);
		lastItem = NULL;//при удалении последнео элемента ластайтем ни на что не указывает
		count = 0;
		return;
	}
	else if (lastItem == item)//удаляем нулевой элемент списка, который содержит больше одного элемента
	{
		InvoiceItem* toDelete = item;//Создаем указатель, который будет отвечать за удаление элемента
		lastItem = toDelete->Next;//переносим указатель старта списка на следующий элемент
		delete(toDelete);
		count--;
		return;
	}

	InvoiceItem* indexator = lastItem;
	InvoiceItem* before = NULL;//элемент, который указывает на элемент, который мы хотим удалить
	InvoiceItem* after = item->Next;//следующий элемент после того, который хотим удалить
	for (int i = 0; i < count; i++)
	{
		if (indexator->Next == item)//то что нам нужно удалить
		{
			before = indexator;//предыдущий элемент того, который нужно удалить
			break;
		}

		indexator = GetItem(i);
	}

	InvoiceItem* toDelete = indexator->Next;
	before->Next = after;//предыдущий элемент удаляемого элемента начинает указывать на следующий элемент удаляемого элемента
	delete(toDelete);
	count--;

}

void InvoiceContainer::Clear()
{
	while (count != 0)
	{
		InvoiceItem* item = GetItem(0);//чтобы очистить полностью удаляем постоянно нулевой элемент
		Remove(item);
	}
}

void InvoiceContainer::Print(string fileName)
{
	if (fileName == "")
		printToConsole();
	else
		printToFile(fileName);
}


bool InvoiceItem::SetInvoiceNumber(string invoiceNumber)
{
	if (invoiceNumber.length() != 13)
		return false;

	this->invoiceNumber = invoiceNumber;
	return true;
}

string InvoiceItem::GetInvoiceNumber()
{
	return invoiceNumber;
}

bool InvoiceItem::SetName(string name)
{
	if (name.length() < 2 || name.length() > 50)
		return false;

	this->name = name;
	return true;
}

string InvoiceItem::GetName()
{
	return name;
}

bool InvoiceItem::SetQuantity(double quantity)
{
	if (quantity <= 0)
		return false;

	this->quantity = quantity;
	return true;
}

double InvoiceItem::GetQuantity()
{
	return quantity;
}

bool InvoiceItem::SetPrice(double price)
{
	if (price <= 0)
		return false;

	this->price = price;
	return true;
}

double InvoiceItem::GetPrice()
{
	return price;
}

bool InvoiceItem::SetCost(double cost)
{
	if (cost <= 0)
		return false;

	this->cost = cost;
	return true;
}

double InvoiceItem::GetCost()
{
	return cost;
}

string * InvoiceItem::GetDetails()
{
	string* details = new string[LENGTH_OF_INVOICE_DETAILS]//для избежания ошибок объект лучше всего создавать в куче
	{
		"Number: " + invoiceNumber,
		"Name: " + name,
		"Quantity of goods: " + to_string(quantity),
		"Price of product: " + to_string(price),
		"Cost of product: " + to_string(cost)
	};

	return details;
}



