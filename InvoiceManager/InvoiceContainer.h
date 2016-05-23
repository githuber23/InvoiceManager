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
	void printToConsole();
	void printToFile(string fileName);
	int  getTotalCost();//стоимость всех чеков в нашей накладной
	string getFooter();//получаем футер
	string getHeader();//получаем хедер
	int count;//переменная, отвечающая за количество элементов в контейнере
public:
	const string HEADER = "Total count of cheks: ";
	const string FOOTER_1 = "Total cost: ";//по возможности -исправить!(не должно быть двух переменных, отвечающих за футер)
	const string FOOTER_2 = "; Total count of rows: ";//по возможности -исправить!
	InvoiceContainer();
	int GetCount();
	InvoiceItem* GetItem(int index);
	void Add(InvoiceItem* item);
	void Remove(InvoiceItem* item);
	void Clear();
	void Print(string fileName);//выводит элементы контейнера
};


