//#include "Queue.h"
#include "Array.h"

int main()
{
	// �������� � ������������� 1 ������� ��� ������
	Array<int> obj;

	for (int i = 0; i < 5; i++)
	{
		obj.append(i);
	}

	// �������� � ������������� 2 ������� ��� ������
	Array<int> obj2;

	for (int i = 0; i < 4; i++)
	{
		obj2.append(i);
	}

	// ������������ ����������� 

	obj.print();
	obj2.print();

	obj.append(obj2);

	obj.print();

	obj.InsertAt(4,666);

	obj.print();

	obj.DeleteAt(4);

	obj.print();

}