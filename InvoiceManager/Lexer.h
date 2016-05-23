#include <fstream>
#include "InvoiceContainer.h"
class Lexer
{
private:
	InvoiceContainer* invoiceContainer;
public:
	Lexer();
	bool IsTitlesExist(ifstream* stream);
};