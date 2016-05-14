#include <string>
using namespace std;

class InvoiceItem {
private:
	string invoiceNumber;
	string name;
	double quantity;
	double price;//����
	double cost;//�������������
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
	string* GetDetails();//���������� ������ ������ � ������� ���������
	InvoiceItem* Next;
};


class InvoiceContainer {
private:
	InvoiceItem* lastItem;
	InvoiceItem* getItem(int index, InvoiceItem* current);
	int count;//����������, ���������� �� ���������� ��������� � ����������
public:
	InvoiceContainer();
	int GetCount();
	InvoiceItem* GetItem(int index);
	void Add(InvoiceItem* item);
	void Remove(InvoiceItem* item);
	void Clear();
	void Print(string fileName);//������� �������� ����������
};


