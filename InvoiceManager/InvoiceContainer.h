#include <string>
using namespace std;

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
	void push(string name);
	bool contains(InvoiceItem item);
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
	void print(string path) const; //
	void getMostPopularGoods(int* countOfChecks, int* count, double* totalPrice, string* name) const;
};