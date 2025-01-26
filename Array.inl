#pragma once

// аппенд из ориг. двойных списков (не метод заданный в задании)
//  (методы с маленькой буквы - предусмотренные списками, а с большой - из задания, кроме оператора)

template<class T>
void Array<T>::append(T value)
{
    int counter = 0;
    Node<T>* newNode = new Node<T>(value);

    if (tail == nullptr)
    {
        head = tail = newNode;
        size = 1;
    }
    else
    {
        if (GetUpperBound() == size - 1)
        {
            for (int i = 0; i < grow; i++)
            {
                Node<T>* newNode = new Node<T>(value);

                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
                size++;
            }
        }
        else
        {
            Node<T>* Upper_bound = head;
            for (int i = 0; i < GetUpperBound(); i++)
            {
                Upper_bound = Upper_bound->next;
            }

            Upper_bound->data = value;
        }
    }
}

// метод для обьединения списков. была идея просто к нексту у хвоста первого 
// присвоить адрес головы второго, но в деструкторе была ошибка из-за того, что
// они указывают на 1 обьект, поэтому оставила как есть

template<class T>
void Array<T>::append(Array& obj)
{
    for (int i = 0; i < obj.size; i++)
    {
        append(obj[i]);
    }
}

// возвращает атрибут с размером (сначала была версия подсчёта элеметов, 
// но так как класс по факту называется строка, а в таких
// классах обычно есть атрибут размера, сделала так

template<class T>
int Array<T>::GetSize() const
{
    return size;
}

// метод увеличения/уменьшения размера на число гроу с каждым шагом

template<class T>
void Array<T>::SetSize(int size_P, int grow)
{

    if (size_P>size)
    {
        int diff = size_P - size;

        for (int i = 0; i < diff; i++) 
        {
            for (int j = 0; j < grow; j++)
            {
                append(); 
            }
        }
    }
    else
    {
        int diff = size-size_P;
        int size_buff = 1;
        Node<T>* buff = head;

        while (size_buff!=diff)
        {
            size_buff++;
            buff = buff->next;
        }
        buff->next = nullptr;
    }

    size = size_P;
}

// проверка на пустоту списка

template<class T>
bool Array<T>::IsEmpty() const
{
    return head == nullptr;
}

// очищение списка

template<class T>
void Array<T>::RemoveAll()
{
    head = tail = nullptr;
}

// возвращение значения по индексу (перегрузку оператора [] я сделала позже 
// и т.к. была задача сделать метод, я не стала использовать оператор и оставила так)
// при отсутствии запрашиваемого индекса возвращает стандартное значение для типа данных шаблона

template<class T>
const T Array<T>::GetAt(int index) const
{
    if (index < size && index >= 0)
    {
        int size_buff = 0;
        Node<T>* buff = head;

        while (size_buff != index)
        {
            size_buff++;
            buff = buff->next;
        }

        return buff->data;
    }
    else
    {
        return T();
    }
}

// вставка элемент на какой-либо индекс

template<class T>
void Array<T>::SetAt(int index, T elem)
{
    if (index < size && index >= 0)
    {
        int size_buff = 0;
        Node<T>* buff = head;

        while (size_buff != index)
        {
            size_buff++;
            buff = buff->next;
        }

        buff->data = elem;
        buff->full = 1;
    }
}

// возвращение самого верхнего индекса (только ячейки, созданные как заполненные)

template<class T>
int Array<T>::GetUpperBound()
{
    Node<T>* buff = head;
    int buff_indx = -1;

    while (buff != nullptr && buff->full != 0)
    {
        buff_indx++;
        buff = buff->next;
    }

    return buff_indx;
}

// удаление незаполненных ячеек

template<class T>
void Array<T>::FreeExtra()
{
    int UpperBound = GetUpperBound();
    Node<T>* buff = head;

    for (int i = 0; i < UpperBound; i++)
    {
        buff = buff->next;
    }

    buff->next = nullptr; 
}

// перегрузка оператора

template<class T>
T Array<T>::operator[](int indx)
{
    int size_buff = 0;
    Node<T>* buff = head;

    while (size_buff != indx)
    {
        size_buff++;
        buff = buff->next;
    }

    return buff->data;
}

// возаращает неконстантную ссылку на начало списка

template<class T>
Array<T>::Node<T>& Array<T>::Get_data()
{
    return head;
}

// записывает на место какого-т индекса (т.к. а списках 
// действует принцип LIFO то и добавляется на нужный индекс с конца)

template<class T>
void Array<T>::InsertAt(int indx, T value)
{
    Node<T>* newnode = new Node<T>{ value };
    Node<T>* needed_val = head;

    if (needed_val->next->next != nullptr && indx != 0)
    {
        needed_val = needed_val->next;
        indx--;
    }
    newnode->prev = needed_val;
    needed_val->next->prev = newnode;
    newnode->next = needed_val->next;
    needed_val->next = newnode;

    size++;
}

//удалить нужный индекс

template<class T>
void Array<T>::DeleteAt(int indx)
{
    Node<T>* buff = head;
    Node<T>* buff_indx = head;

    for (int i = 0; i < indx - 1; i++)
    {
        buff = buff->next;
    }

    for (int i = indx; i < size && buff->next != nullptr; i++)
    {
        buff->data = buff->next->data;
        buff = buff->next;
    }

    size--;
    tail = tail->prev;
    tail->next = nullptr;
}

//удалить последний эл.

template<class T>
void Array<T>::removeLast()
{
    if (head == nullptr)
    {
        cout << "Список пуст. Удаление невозможно.\n";
        return;
    }
    else if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        Node* temp = tail;

        tail = tail->prev;
        tail->next = nullptr;

        delete temp;
    }
}

// вывод

template<class T>
void Array<T>::print() const
{
    Node<T>* current = head;

    cout << '\n';

    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }
}

// поиск массива и возвращение булевой переменной

template<class T>
bool Array<T>::search(T value) const
{
    Node<T>* current = head;

    while (current != nullptr)
    {
        if (current->data == value)
        {
            return true;
        }

        current = current->next;
    }

    return false;
}

//деструктор

template<class T>
Array<T>::~Array()
{
    Node<T>* current = head;

    while (current != nullptr)
    {
        Node<T>* nextNode = current->next;

        delete current;
        current = nextNode;
    }
}