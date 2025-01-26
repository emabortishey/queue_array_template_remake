#pragma once

// ������ �� ����. ������� ������� (�� ����� �������� � �������)
//  (������ � ��������� ����� - ��������������� ��������, � � ������� - �� �������, ����� ���������)

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

// ����� ��� ����������� �������. ���� ���� ������ � ������ � ������ ������� 
// ��������� ����� ������ �������, �� � ����������� ���� ������ ��-�� ����, ���
// ��� ��������� �� 1 ������, ������� �������� ��� ����

template<class T>
void Array<T>::append(Array& obj)
{
    for (int i = 0; i < obj.size; i++)
    {
        append(obj[i]);
    }
}

// ���������� ������� � �������� (������� ���� ������ �������� ��������, 
// �� ��� ��� ����� �� ����� ���������� ������, � � �����
// ������� ������ ���� ������� �������, ������� ���

template<class T>
int Array<T>::GetSize() const
{
    return size;
}

// ����� ����������/���������� ������� �� ����� ���� � ������ �����

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

// �������� �� ������� ������

template<class T>
bool Array<T>::IsEmpty() const
{
    return head == nullptr;
}

// �������� ������

template<class T>
void Array<T>::RemoveAll()
{
    head = tail = nullptr;
}

// ����������� �������� �� ������� (���������� ��������� [] � ������� ����� 
// � �.�. ���� ������ ������� �����, � �� ����� ������������ �������� � �������� ���)
// ��� ���������� �������������� ������� ���������� ����������� �������� ��� ���� ������ �������

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

// ������� ������� �� �����-���� ������

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

// ����������� ������ �������� ������� (������ ������, ��������� ��� �����������)

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

// �������� ������������� �����

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

// ���������� ���������

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

// ���������� ������������� ������ �� ������ ������

template<class T>
Array<T>::Node<T>& Array<T>::Get_data()
{
    return head;
}

// ���������� �� ����� ������-� ������� (�.�. � ������� 
// ��������� ������� LIFO �� � ����������� �� ������ ������ � �����)

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

//������� ������ ������

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

//������� ��������� ��.

template<class T>
void Array<T>::removeLast()
{
    if (head == nullptr)
    {
        cout << "������ ����. �������� ����������.\n";
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

// �����

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

// ����� ������� � ����������� ������� ����������

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

//����������

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