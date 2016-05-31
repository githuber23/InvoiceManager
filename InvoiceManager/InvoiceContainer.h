#include <string>
using namespace std;

//class InvoiceItem {
//private:
//	string invoiceNumber;
//	string name;
//	double quantity;
//	double price;//цена
//	double cost;//себестоимость
//public:
//	bool SetInvoiceNumber(string invoiceNumber);
//	string GetInvoiceNumber();
//	bool SetName(string name);
//	string GetName();
//	bool SetQuantity(double quantity);
//	double GetQuantity();
//	bool SetPrice(double price);
//	double GetPrice();
//	bool SetCost(double cost);
//	double GetCost();
//	string* GetDetails();//возвращает массив данных о текущей накладной
//	InvoiceItem* Next;
//};
//
//
//class InvoiceContainer {
//private:
//	InvoiceItem* lastItem;
//	InvoiceItem* getItem(int index, InvoiceItem* current);
//	void printToConsole();
//	void printToFile(string fileName);
//	int  getTotalCost();//стоимость всех чеков в нашей накладной
//	string getFooter();//получаем футер
//	string getHeader();//получаем хедер
//	int count;//переменная, отвечающая за количество элементов в контейнере
//public:
//	const string HEADER = "Total count of cheks: ";
//	const string FOOTER_1 = "Total cost: ";//по возможности -исправить!(не должно быть двух переменных, отвечающих за футер)
//	const string FOOTER_2 = "; Total count of rows: ";//по возможности -исправить!
//	InvoiceContainer();
//	int GetCount();
//	InvoiceItem* GetItem(int index);
//	void Add(InvoiceItem* item);
//	void Remove(InvoiceItem* item);
//	void Clear();
//	void Print(string fileName);//выводит элементы контейнера
//};


class InvoiceContainer {
private:
	class InvoiceItem {
	private:
		string invoiceNumber;
		string name;
		double quantity;
		double price;//цена
		double cost;//себестоимость
	public:
		InvoiceItem(string number, string name, double quantity, double price, double cost);
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
		InvoiceItem* Next;
	};
	InvoiceItem* head;
	int count;
public:
	class Iterator {
	public:
		Iterator(InvoiceItem* current = nullptr);
		InvoiceItem& operator *() const;	 //current data element if exist; else throw(out_of_range)
		virtual Iterator& operator ++(); //move to next node if current node exist; else nothing
		virtual bool OK() const;		// true iff current item exists;
		operator bool() const; //return OK()
		bool operator ==(const Iterator&) const;
		bool operator !=(const Iterator&) const;
	protected:
		InvoiceItem* current;
	};
	InvoiceContainer();
	InvoiceContainer(const InvoiceContainer&) = delete;
	InvoiceContainer(InvoiceContainer&&) = delete;
	InvoiceContainer& operator=(const InvoiceContainer&) = delete;
	InvoiceContainer& operator=(InvoiceContainer&&) = delete;
	~InvoiceContainer();
	void push(string number, string name, double quantity, double price, double cost);// throw(bad_alloc)
	bool pop(); //true iff was non empty
	InvoiceItem& top()const; //pre: stack is not empty, else throw(out_of_range)
	int size() const;
	bool empty() const;
	void clear();
	Iterator begin() const;
	Iterator end() const;
	void print(const Iterator& from, const Iterator& to) const; // [from; to) if not from<=to throw(out_of_range)
	void print() const; //
};