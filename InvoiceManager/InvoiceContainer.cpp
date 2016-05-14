#include "InvoiceContainer.h"
#define NULL 0

InvoiceItem * InvoiceContainer::getItem(int index, InvoiceItem * current)
{
	if (index != 0)
		getItem(index - 1, current->Next);
	else
		return current;

}

InvoiceContainer::InvoiceContainer()//����������� �� ���������
{
	count = 0;
	lastItem = NULL;
}

int InvoiceContainer::GetCount()
{
	return count;
}

InvoiceItem* InvoiceContainer::GetItem(int index)//�������� ������� �� �������
{
	if (index > count - 1)//��������� ������� = �����-1, ��� ��� ������� � ����
		return NULL;

	return getItem(index, lastItem);
}


void InvoiceContainer::Add(InvoiceItem* item)
{
	if (lastItem == NULL)
	{
		lastItem = item;//���� �����- ��������� �� ��������� ������� ����������
	}
	else
	{
		item->Next = lastItem;
		lastItem = item;//�������� ��������� ������� � �������, ��� ��� ����� �������- ��������� ������� ��� ��� ������������� � ����������
	}

	count++;
}

void InvoiceContainer::Remove(InvoiceItem* item)
{

		if (count == 1)//������, ����� � ��� ���� �������
		{
			delete(lastItem);
			lastItem = NULL;//��� �������� ��������� �������� ��������� �� �� ��� �� ���������
			count = 0;
			return;
		}
		else if (lastItem == item)//������� ������� ������� ������, ������� �������� ������ ������ ��������
		{
			InvoiceItem* toDelete = item;//������� ���������, ������� ����� �������� �� �������� ��������
			lastItem = toDelete->Next;//��������� ��������� ������ ������ �� ��������� �������
			delete(toDelete);
			count--;
			return;
		}

		InvoiceItem* indexator = lastItem;
		InvoiceItem* before = NULL;//�������, ������� ��������� �� �������, ������� �� ����� �������
		InvoiceItem* after = item->Next;//��������� ������� ����� ����, ������� ����� �������
		for (int i = 0; i < count; i++)
		{
			if (indexator->Next == item)//�� ��� ��� ����� �������
			{
				before = indexator;//���������� ������� ����, ������� ����� �������
				break;
			}

			indexator = GetItem(i);
		}

		InvoiceItem* toDelete = indexator->Next;
		before->Next = after;//���������� ������� ���������� �������� �������� ��������� �� ��������� ������� ���������� ��������
		delete(toDelete);
		count--;
	
}

void InvoiceContainer::Clear()
{
	while (count != 0)
	{
		InvoiceItem* item = GetItem(0);//����� �������� ��������� ������� ��������� ������� �������
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

