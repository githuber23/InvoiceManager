#include "InvoiceContainer.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Constants.h"
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

bool InvoiceContainer::empty() const//���������� true,���� count == 0
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
	{
		cout << NUMBER_OF_INVOICE << ": " << (*i).GetInvoiceNumber() << "; ";
		cout << NAME_OF_INVOICE << ": " << (*i).GetName() << "; ";
		cout << QUANTITY << ": " << (*i).GetQuantity() << "; ";
		cout << PRICE << ": " << (*i).GetPrice() << "; ";
		cout << COST << ": " << (*i).GetCost() << "; " << endl;
	}
}



void InvoiceContainer::print(string path) const
{
	double totalCost = 0;
	for (Iterator i = begin(); i != end(); ++i)
	{
		totalCost += (*i).GetCost();
	}

	if (path == "")
	{
		cout << HEADER << ": " << size() << ";" << endl;

		print(begin(), end());
		cout << TOTAL_COST << ": " << totalCost << "; ";
		cout << TOTAL_COUNT_OF_ROWS << ": " << size() + 2 << "; " << endl;
	}
	else
	{
		ofstream stream(path);//��������� ����� ��� ������ � ����
		stream.clear();
		stream << HEADER << ": " << size() << ";" << endl;

		for (Iterator i = begin(); i != end(); ++i)
		{
			stream << NUMBER_OF_INVOICE << ": " << (*i).GetInvoiceNumber() << "; ";
			stream << NAME_OF_INVOICE << ": " << (*i).GetName() << "; ";
			stream << QUANTITY << ": " << (*i).GetQuantity() << "; ";
			stream << PRICE << ": " << (*i).GetPrice() << "; ";
			stream << COST << ": " << (*i).GetCost() << "; " << endl;
		}
		stream << TOTAL_COST << ": " << totalCost << "; ";
		stream << TOTAL_COUNT_OF_ROWS << ": " << size()+2 << "; " << endl;
		stream.close();
	}
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
