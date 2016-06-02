#include <string>
#include "InvoiceContainer.h"
#include "Lexer.h"
using namespace std;

class Builder
{
private:
	InvoiceContainer* invoiceContainer;
	Lexer* lexer;
	// ���������, ������������� �� ���� ������ ������� ������ ���������. title - Number, value - 123.
	void checkNote(string title, string value, string* error);
	bool isWhiteSymbolsString(string s);
	bool isInt(string value);
	bool isNumberOfInvoice(string value);
	bool isDouble(string value, int countOfNumberAfterDot, bool fixed);

public:
	Builder();
	//��� ����������� ���������� ��� ������ � ���������
	void Print(string path);
	void ReadFile(string path);
};