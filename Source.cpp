//#include "Queue.h"
#include "Array.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	// �������� � ������������� 1 ������� ��� ������
	Array<int> obj;

	try {
		obj.print();
	}
	catch (ContaineerIsEmpty objj)
	{
		cout << "��������� ������� ���������� ��� ������� ������ ������ ������ ������ �� �������������: " << objj.what();
	}

	for (int i = 0; i < 5; i++)
	{
		obj.append(i+1);
	}

	// �������� � ������������� 2 ������� ��� ������
	Array<int> obj2;

	for (int i = 0; i < 4; i++)
	{
		obj2.append(i+1);
	}

	// ������������ ����������� 
	
	// ����� ����� ����� ������������

	cout << "������ ������ �� �����������: ";
	obj.print();

	cout << "\n������ ������ �� �����������: ";
	obj2.print();

	// ���������� ������ ������ � ������
	obj.append(obj2);

	cout << "\n\n���������� ����� ����������� ������: ";
	obj.print();

	obj.InsertAt(4,666);

	cout << "\n\n������ ������ ����� ������� 666 �� 4 ������: ";
	obj.print();

	obj.DeleteAt(4);

	cout << "\n\n������ ������ ����� �������� 666 �� 4 �������: ";
	obj.print();

	obj.SetSize(12);

	cout << "\n\n������ ������ ����� ���������� 1 ������ ������ (������ ������ �� ���������, �� ������������): ";
	obj.print();

	obj.append(666);

	cout << "\n\n������ ������ ����� ���������� 666 � � ����� (666 ������ �� ����� ������� ��������): ";
	obj.print();

}