#include "InvoiceContainer.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define NULL 0

const int LENGTH_OF_INVOICE_DETAILS = 5;
const int HEADER_AND_FOOTER_COUNT = 2;



InvoiceContainer::InvoiceItem::InvoiceItem(string number, string name, double quantity, double price, double cost)
{
	SetInvoiceNumber(number);
	SetName(name);
	SetQuantity(quantity);
	SetPrice(price);
	SetCost(cost);
}

//InvoiceItem * InvoiceContainer::getItem(int index, InvoiceItem * current)
//{
//	if (index != 0)
//		getItem(index - 1, current->Next);
//	else
//		return current;
//}
//
//void InvoiceContainer::printToConsole()
//{
//	cout << getHeader() << endl;
//	for (int i = 0; i < count; i++)//проходим по каждому элементу контейнера(по каждой накладной)
//	{
//		InvoiceItem item = *GetItem(i);
//		string* details = item.GetDetails();
//		for (int strNum = 0; strNum < LENGTH_OF_INVOICE_DETAILS; strNum++)   //проходимся по каждой строке информации конкретной накладной
//		{
//			cout << details[strNum] << endl;//вывод конкретной строки с информацией
//		}
//
//		cout << "============================" << endl;
//	}
//
//	cout << getFooter() << endl;
//}
//
//void InvoiceContainer::printToFile(string fileName) 
//{
//	ofstream stream(fileName);//создается поток для записи в файл
//	stream << getHeader() << endl << endl;
//	for (int i = 0; i < count; i++)//проходим по каждому элементу контейнера(по каждой накладной)
//	{
//		InvoiceItem item = *GetItem(i);
//		string* details = item.GetDetails();
//		for (int strNum = 0; strNum < LENGTH_OF_INVOICE_DETAILS; strNum++)   //проходимся по каждой строке информации конкретной накладной
//		{
//			stream << details[strNum] << endl;//вывод конкретной строки с информацией
//		}
//		stream << "============================" << endl;
//
//	}
//
//	stream << getFooter() << endl;
//
//
//}
//
//int InvoiceContainer::getTotalCost()//считаем общую суму всех себестоимостей
//{
//	int sum = 0;
//	for (int i = 0; i < count; i++)
//		sum += GetItem(i)->GetCost();
//
//	return sum;
//}
//
//string InvoiceContainer::getFooter()
//{
//	int countOfStrings = HEADER_AND_FOOTER_COUNT + LENGTH_OF_INVOICE_DETAILS*count; //получаем количество строк в файле
//	return FOOTER_1 + to_string(getTotalCost()) + FOOTER_2 + to_string(countOfStrings);
//}
//
//string InvoiceContainer::getHeader()
//{
//	return HEADER + to_string(count);
//}
//
//InvoiceContainer::InvoiceContainer()//конструктор по умолчанию
//{
//	count = 0;
//	lastItem = NULL;
//}
//
//int InvoiceContainer::GetCount()
//{
//	return count;
//}
//
//InvoiceItem* InvoiceContainer::GetItem(int index)//получаем элемент по индексу
//{
//	if (index > count - 1)//последний элемент = каунт-1, так как считаем с нуля
//		return NULL;
//
//	return getItem(index, lastItem);
//}
//
//
//void InvoiceContainer::Add(InvoiceItem* item)
//{
//	if (lastItem == NULL)
//	{
//		lastItem = item;//ласт айтем- указатель на последний элемент контейнера
//	}
//	else
//	{
//		item->Next = lastItem;
//		lastItem = item;//получили последний элемент и сказали, что наш новый элемент- следующий элемент для уже существующего в контейнере
//	}
//
//	count++;
//}
//
//void InvoiceContainer::Remove(InvoiceItem* item)
//{
//
//	if (count == 1)//случай, когда у нас один элемент
//	{
//		delete(lastItem);
//		lastItem = NULL;//при удалении последнео элемента ластайтем ни на что не указывает
//		count = 0;
//		return;
//	}
//	else if (lastItem == item)//удаляем нулевой элемент списка, который содержит больше одного элемента
//	{
//		InvoiceItem* toDelete = item;//Создаем указатель, который будет отвечать за удаление элемента
//		lastItem = toDelete->Next;//переносим указатель старта списка на следующий элемент
//		delete(toDelete);
//		count--;
//		return;
//	}
//
//	InvoiceItem* indexator = lastItem;
//	InvoiceItem* before = NULL;//элемент, который указывает на элемент, который мы хотим удалить
//	InvoiceItem* after = item->Next;//следующий элемент после того, который хотим удалить
//	for (int i = 0; i < count; i++)
//	{
//		if (indexator->Next == item)//то что нам нужно удалить
//		{
//			before = indexator;//предыдущий элемент того, который нужно удалить
//			break;
//		}
//
//		indexator = GetItem(i);
//	}
//
//	InvoiceItem* toDelete = indexator->Next;
//	before->Next = after;//предыдущий элемент удаляемого элемента начинает указывать на следующий элемент удаляемого элемента
//	delete(toDelete);
//	count--;
//
//}
//
//void InvoiceContainer::Clear()
//{
//	while (count != 0)
//	{
//		InvoiceItem* item = GetItem(0);//чтобы очистить полностью удаляем постоянно нулевой элемент
//		Remove(item);
//	}
//}
//
//void InvoiceContainer::Print(string fileName)
//{
//	if (fileName == "")
//		printToConsole();
//	else
//		printToFile(fileName);
//}
//
//
bool InvoiceContainer::InvoiceItem::SetInvoiceNumber(string invoiceNumber)
{
	if (invoiceNumber.length() != 13)
		return false;

	this->invoiceNumber = invoiceNumber;
	return true;
}

string InvoiceContainer::InvoiceItem::GetInvoiceNumber()
{
	return invoiceNumber;
}

bool InvoiceContainer::InvoiceItem::SetName(string name)
{
	if (name.length() < 2 || name.length() > 50)
		return false;

	this->name = name;
	return true;
}

string InvoiceContainer::InvoiceItem::GetName()
{
	return name;
}

bool InvoiceContainer::InvoiceItem::SetQuantity(double quantity)
{
	if (quantity <= 0)
		return false;

	this->quantity = quantity;
	return true;
}

double InvoiceContainer::InvoiceItem::GetQuantity()
{
	return quantity;
}

bool InvoiceContainer::InvoiceItem::SetPrice(double price)
{
	if (price <= 0)
		return false;

	this->price = price;
	return true;
}

double InvoiceContainer::InvoiceItem::GetPrice()
{
	return price;
}

bool InvoiceContainer::InvoiceItem::SetCost(double cost)
{
	if (cost <= 0)
		return false;

	this->cost = cost;
	return true;
}

double InvoiceContainer::InvoiceItem::GetCost()
{
	return cost;
}
//
//string * InvoiceItem::GetDetails()
//{
//	string* details = new string[LENGTH_OF_INVOICE_DETAILS]//для избежания ошибок объект лучше всего создавать в куче
//	{
//		"Number: " + invoiceNumber,
//		"Name: " + name,
//		"Quantity of goods: " + to_string(quantity),
//		"Price of product: " + to_string(price),
//		"Cost of product: " + to_string(cost)
//	};
//
//	return details;
//}

InvoiceContainer::InvoiceContainer() :head(nullptr), count(0)
{
}

InvoiceContainer::~InvoiceContainer()
{
	clear();
}

void InvoiceContainer::push(string number, string name, double quantity, double price, double cost)
{
	InvoiceItem* item = new InvoiceItem(number, name, quantity, price, cost);
	item->Next = head;
	head = item;
	++count;
}

bool InvoiceContainer::pop()
{
	if (!head) 
		return false;

	InvoiceItem* tmp = head->Next; 
	delete head; 
	head = tmp; --count;
	return true;
}

InvoiceContainer::InvoiceItem & InvoiceContainer::top() const
{
	if (!head) 
		throw out_of_range("no data to view\n");

	return *head;
}

int InvoiceContainer::size() const
{
	return count;
}

bool InvoiceContainer::empty() const//возвращает true,если count == 0
{
	return count == 0;
}

void InvoiceContainer::clear()
{
	InvoiceItem* tmp;
	while (head) 
	{
		tmp = head->Next;
		delete head;
		head = tmp;
	}

	count = 0;
}

InvoiceContainer::Iterator InvoiceContainer::begin() const
{
	return Iterator(head);
}

InvoiceContainer::Iterator InvoiceContainer::end() const
{
	return Iterator();
}

void InvoiceContainer::print(const Iterator & from, const Iterator & to) const
{
	for (Iterator i = from; i != to; ++i) 
		cout << (*i).GetName() << " ";
}

void InvoiceContainer::print() const
{
	print(begin(), end());
	cout << endl;
}

InvoiceContainer::Iterator::Iterator(InvoiceItem * current) :current(current) {}

InvoiceContainer::InvoiceItem & InvoiceContainer::Iterator::operator*() const
{
	if (current) 
		return *current;	
	else 
		throw out_of_range("wrong iterator position");
}

InvoiceContainer::Iterator & InvoiceContainer::Iterator::operator++()
{
	if (current) 
		current = current->Next;
	return 
		*this;
}

bool InvoiceContainer::Iterator::OK() const
{
	return current != nullptr;
}

InvoiceContainer::Iterator::operator bool() const
{
	return OK();
}

bool InvoiceContainer::Iterator::operator==(const Iterator &other) const
{
	return current == other.current;
}

bool InvoiceContainer::Iterator::operator!=(const Iterator &other) const
{
	return current != other.current;
}
