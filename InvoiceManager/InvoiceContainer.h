#include <string>
using namespace std;

class InvoiceItem {
private:
	string invoiceNumber;
	string name;
	double quantity;
	double price;//цена
	double cost;//себестоимость
public:
	bool SetInvoiceNumber(string invoiceNumber);
	string GetInvoiceNumber();
	bool SetName(string name);
	string GetName();
	bool SetQuantity(double quantity);
	double GetQuantity();
	bool SetPrice(double price);
	double GetPrice();
	bool SetCost(double cost);
	double GetCost();
	string* GetDetails();//возвращает массив данных о текущей накладной
	InvoiceItem* Next;
};


class InvoiceContainer {
private:
	InvoiceItem* lastItem;
	InvoiceItem* getItem(int index, InvoiceItem* current);
	int count;//переменная, отвечающая за количество элементов в контейнере
public:
	InvoiceContainer();
	int GetCount();
	InvoiceItem* GetItem(int index);
	void Add(InvoiceItem* item);
	void Remove(InvoiceItem* item);
	void Clear();
	void Print(string fileName);//выводит элементы контейнера
};


