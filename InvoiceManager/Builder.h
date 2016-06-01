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
	bool checkNote(string title, string value);
public:
	Builder();
	void ReadFile(string path);
};