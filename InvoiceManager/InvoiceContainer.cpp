#include "InvoiceContainer.h"
#define NULL 0

InvoiceItem * InvoiceContainer::getItem(int index, InvoiceItem * current)
{
	if (index != 0)
		getItem(index - 1, current->Next);
	else
		return current;

}

InvoiceContainer::InvoiceContainer()//конструктор по умолчанию
{
	count = 0;
	lastItem = NULL;
}

int InvoiceContainer::GetCount()
{
	return count;
}

InvoiceItem* InvoiceContainer::GetItem(int index)//получаем элемент по индексу
{
	if (index > count - 1)//последний элемент = каунт-1, так как считаем с нуля
		return NULL;

	return getItem(index, lastItem);
}


void InvoiceContainer::Add(InvoiceItem* item)
{
	if (lastItem == NULL)
	{
		lastItem = item;//ласт айтем- указатель на последний элемент контейнера
	}
	else
	{
		item->Next = lastItem;
		lastItem = item;//получили последний элемент и сказали, что наш новый элемент- следующий элемент для уже существующего в контейнере
	}

	count++;
}

void InvoiceContainer::Remove(InvoiceItem* item)
{

		if (count == 1)//случай, когда у нас один элемент
		{
			delete(lastItem);
			lastItem = NULL;//при удалении последнео элемента ластайтем ни на что не указывает
			count = 0;
			return;
		}
		else if (lastItem == item)//удаляем нулевой элемент списка, который содержит больше одного элемента
		{
			InvoiceItem* toDelete = item;//Создаем указатель, который будет отвечать за удаление элемента
			lastItem = toDelete->Next;//переносим указатель старта списка на следующий элемент
			delete(toDelete);
			count--;
			return;
		}

		InvoiceItem* indexator = lastItem;
		InvoiceItem* before = NULL;//элемент, который указывает на элемент, который мы хотим удалить
		InvoiceItem* after = item->Next;//следующий элемент после того, который хотим удалить
		for (int i = 0; i < count; i++)
		{
			if (indexator->Next == item)//то что нам нужно удалить
			{
				before = indexator;//предыдущий элемент того, который нужно удалить
				break;
			}

			indexator = GetItem(i);
		}

		InvoiceItem* toDelete = indexator->Next;
		before->Next = after;//предыдущий элемент удаляемого элемента начинает указывать на следующий элемент удаляемого элемента
		delete(toDelete);
		count--;
	
}

void InvoiceContainer::Clear()
{
	while (count != 0)
	{
		InvoiceItem* item = GetItem(0);//чтобы очистить полностью удаляем постоянно нулевой элемент
		Remove(item);
	}
}


bool InvoiceItem::SetInvoiceNumber(string invoiceNumber)
{
	return false;
}

string InvoiceItem::GetInvoiceNumber()
{
	return string();
}

