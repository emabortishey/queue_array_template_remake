//#include "Queue.h"
#include "Array.h"

int main()
{
	// создание и инициализация 1 обьекта для тестов
	Array<int> obj;

	for (int i = 0; i < 5; i++)
	{
		obj.append(i);
	}

	// создание и инициализация 2 обьекта для тестов
	Array<int> obj2;

	for (int i = 0; i < 4; i++)
	{
		obj2.append(i);
	}

	// тестирование обьединения 

	obj.print();
	obj2.print();

	obj.append(obj2);

	obj.print();

	// тестирование вставки числа 666 на индекс 4

	obj.InsertAt(4,666);

	// проверка удаления 4 индекса

	//obj.DeleteAt(4);  

	// вывод результатов

	obj.print();

	//// проверка смены размера

	//obj.SetSize(15);

	//// проверка удаления ненужных ячеек

	////obj.FreeExtra();

	//// вывод результата

	//obj.print();

	//// проверка вывода по индексу с помощью метода

	//cout << obj.GetAt(1);

}