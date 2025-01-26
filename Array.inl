#pragma once

// ������ �� ����. ������� ������� (�� ����� �������� � �������)
//  (������ � ��������� ����� - ��������������� ��������, � � ������� - �� �������, ����� ���������)

// ����� ������������������, 1 ���������� ������ 
// ��������� �������� � ����� �������� �������. 
// (�������� �� ��������� ����, �� ��� ������������
// ��� � ���������� ��� ������ ������ � inl ���� 
// ������������� ������, ������� �� ������ � ���������� ������)
template<class T>
void Array<T>::append(T value, bool full_P)
{
    // �������� �������� � ����� ���������
    Node<T>* newNode = new Node<T>(value, full_P);

    // � ������ ���� ������ ����� (���� � ��� �� ����������)
    // � ����� � ���� ������������� ��������� �������
    if (tail == nullptr)
    {
        head = tail = newNode;
        // ���� �������������� ������
        size = 1;

        for (int i = 0; i < grow-1; i++)
        {
            // ����� ������ ������������� �����
            // ��������� ��� ������ ������������ ��� ������
            // � ��� ����������� �������� �� ��������� �� 1 ������

            Node<T>* newNode = new Node<T>(value, full_P);

            // � ����� ����������� ����� �������
            // � ��������� �������� ��������
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;

            // ������ ������������� �� 1
            size++;
        }
    }
    else
    {
        // ���� ��� ������� ������� ������� ��������� � full!=0
        // ��� �������� ����� size-1 �� ���� ���-�� ���������
        // �� ����� ������� ����������� � �����
        if (GetUpperBound() == -1)
        {
            // ���� � ������� ����������� ����� ���-�� ��������� 
            // � �������� ��������� ������� ����� �������� grow
            for (int i = 0; i < grow; i++)
            {
                // ����� ������ ������������� �����
                // ��������� ��� ������ ������������ ��� ������
                // � ��� ����������� �������� �� ��������� �� 1 ������
                Node<T>* newNode = new Node<T>(value, full_P);

                // � ����� ����������� ����� �������
                // � ��������� �������� ��������
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;

                // ������ ������������� �� 1
                size++;
            }
        }
        // � ������ ���� � ������ ���� ��������
        // � ������� ������� full = 0 �� ��������
        // �������� � ������ ����� �������
        else
        {
            if (full_P == true)
            {
                Node<T>* Upper_bound = head;

                for (int i = 0; i < GetUpperBound(); i++)
                {
                    Upper_bound = Upper_bound->next;
                }

                Upper_bound->data = value;
                Upper_bound->full = true;
            }
            else
            {
                for (int i = 0; i < grow; i++)
                {
                    // ����� ������ ������������� �����
                    // ��������� ��� ������ ������������ ��� ������
                    // � ��� ����������� �������� �� ��������� �� 1 ������
                    Node<T>* newNode = new Node<T>(value, full_P);

                    // � ����� ����������� ����� �������
                    // � ��������� �������� ��������
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode;

                    // ������ ������������� �� 1
                    size++;
                }
            }
 
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

// ����� ����������/���������� �������

template<class T>
void Array<T>::SetSize(int size_P, int grow_P)
{
    if (size == size_P)
    {
        throw SizeTheSame("\n\nSize that you want to set is equal to the current one.\n\n");
    }
    // ������ ����� ���� ���������� � �����������
    // � ���������� ���������� (���� ���� �� ��� �� ���������)
    grow = grow_P;

    // ���� ���� ������ ������ ��������
    // �� ���������� ������� ���������, �������
    // ���������� ������� ����� ���������
    if (size_P>size)
    {
        int diff = size_P - size;

        while(diff!=0)
        {
            append(T(), false); 
            diff--;
        }
    }
    // ���� ���������� ������ ������ ��� ��������
    else
    {
        // ���������� ��� ���������� ����������
        // �������� ������� ��������� �� �������
        // ������� ������ ������� ������
        int size_buff = 1;
        // ���������� � ������� ������� ����� 
        // ������������ �������� �� ���������
        Node<T>* buff = head;
        // ���������� ��� �������� ����������� ���������
        Node<T>* buff_deleteing;

        // ���� ������ �������
        while (size_buff!= size_P)
        {
            size_buff++;
            buff = buff->next;
        }

        // ����������� ���������� ���
        // �������� ��������
        // ���������� ��������
        buff_deleteing = buff->next;

        // �������� � ������ ������ � ���������
        // ����� ������� �������
        buff->next = nullptr;

        // ������� �������� ������� �� �������
        while (buff_deleteing->next != nullptr)
        {
            buff_deleteing = buff_deleteing->next;
            delete buff_deleteing->prev;
        }

        // ������� ���������� ��� ��������
        delete buff_deleteing;

        // ������ ������ �������
        size = size_P;
    }
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
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nIt's impossible to remove all elements. Array is empty.\n\n");
    }

    // ���������� ��� ��������
    Node<T>* buff = head;

    // ������� ��� �������� �� ������� �����
    // ����������, �.�. ������� �� �������� �������
    // ��� ����� � �����
    while (buff->next != nullptr)
    {
        buff = buff->next;

        delete buff->prev;
    }

    // ��� ����� ����� ������� 
    // ���� ���������� (��������� ��.)
    delete buff;

    // �������� ��� � ����
    head = tail = nullptr;

    // �������� ������
    size = 0;
}

// ����������� �������� �� ������� (���������� ��������� [] � ������� ����� 
// � �.�. ���� ������ ������� �����, � �� ����� ������������ �������� � �������� ���)
// ��� ���������� �������������� ������� ���������� ����������� �������� ��� ���� ������ �������

// (������ �� ������������ ��� ���������� [] 
// �.�. �������� ��� ���������� ��� �����������
// �������� data � �� ����������� ������ �� ��.
template<class T>
const T Array<T>::GetAt(int indx) const
{
    // ���� ������ ������ � ��������
    // ��������� �������

    if (indx > size - 1 && indx < 0)
    {
        throw out_of_range("\n\nIndex that you want to get at is out of range.\n\n");
    }

    // ���������� ��� ����������
    // ������� �������
    int size_buff = 0;
    // ���������� ��� ������� �� ������
    Node<T>* buff = head;

    // ���� �� ����� ���������
    // ������������ ������
    while (size_buff != indx)
    {
        size_buff++;
        buff = buff->next;
    }

    // ���������� ��������� ��������
    return buff->data;
}

// ������� �������� �� �����-���� ������

template<class T>
void Array<T>::SetAt(int indx, T elem)
{
    if (indx > size - 1 && indx < 0)
    {
        throw out_of_range("\n\nIndex that you want to set at is out of range.\n\n");
    }

    // ����� ��������� ���� ��
    // ���������� ������ � ���������
    int size_buff = 0;
    Node<T>* buff = head;

    // ������� ��� � �����
    while (size_buff != indx)
    {
        size_buff++;
        buff = buff->next;
    }

    // �������� �������� �� �������
    buff->data = elem;
}

// ����������� ������ �������� ������� (������ ������, ��������� ��� �����������)

template<class T>
int Array<T>::GetUpperBound()
{
    Node<T>* buff = head;
    int buff_indx = 0;

    // ���� �� ����� ���������� 
    // ������� ����������� ���������
    while (buff->next != nullptr && buff->full != 0)
    {
        buff_indx++;
        buff = buff->next;
    }

    // � ������ ���� ��� �� ����� �������� �� ���������,
    // ����� ���������� -1 ��� ������������ ����, ���
    // � ������ ��� ��������� ������� �������� ��� ������������
    if (buff->full!=false)
    {
        return -1;
    }

    // � ������ ������ ������������ ������
    return buff_indx;
}

// �������� ������������� �����

template<class T>
void Array<T>::FreeExtra()
{
    // ���������� � �������� ������ �������
    int UpperBound = GetUpperBound();
    // ���������� ��� ������� �� ���������
    Node<T>* buff = head;
    // ���������� ��� ��������
    // ������ ���������
    Node<T>* buff_deleteing;

    // ����������� �� ������� ���� �� ������
    // ��������� ����������� �������
    for (int i = 0; i < UpperBound; i++)
    {
        buff = buff->next;
    }

    // �������������� ���������� ��� ��������
    buff_deleteing = buff->next;

    // �������� ������ � ������ ���������
    buff->next = nullptr;

    // ������� ��� ����� ��������
    // ����� ���������� � �����
    while (buff_deleteing->next != nullptr)
    {
        size--;

        buff_deleteing = buff_deleteing->next;
        delete buff_deleteing->prev;
    }

    // ������� ��������� �������
    delete buff_deleteing;
}

// ���������� ���������

template<class T>
T Array<T>::operator[](int indx)
{
    if (indx > size - 1 && indx < 0)
    {
        throw out_of_range("\n\nIndex that you're seekin' for is out of range.\n\n");
    }

    // ���������� ��� ���������� ������� �������
    int size_buff = 0;
    // ���������� ��� ������� �� �������
    Node<T>* buff = head;

    // ���� ������� ��� ������ �������� � �����
    while (size_buff != indx)
    {
        size_buff++;
        buff = buff->next;
    }

    // ���������� �������� ������� ��������
    return buff->data;
}

// �� �� ����� ���������� ���������, �� �����������
template<class T>
T Array<T>::operator[](int indx) const
{
    if (indx > size - 1 && indx < 0)
    {
        throw out_of_range("\n\nIndex that you're seekin' for is out of range.\n\n");
    }

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
const Array<T>::Node<T>& Array<T>::Get_data()
{
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nArray is empty.\n\n");
    }

    return *head;
}

// ���������� �� ����� ������-� ������� (�.�. � ������� 
// ��������� ������� LIFO �� � ����������� �� ������ ������ � �����)

template<class T>
void Array<T>::InsertAt(int indx, T value)
{
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nInsertion on the asked index is impossible. Array is empty.\n\n");
    }

    if (indx > size - 1 && indx <0)
    {
        throw out_of_range("\n\nIndex that you want to insert at is out of range.\n\n");
    }

    // ������� ����� �������
    Node<T>* newnode = new Node<T>{ value };

    // ���������� ��� ������� �� ������ 
    // � ����� ��� ���������� ������� �
    // ���������� ������ ������
    Node<T>* needed_val = tail;

    // ���� ������� ��� ������ �������� � ������� 
    // ����� � ���������� ���������� �������
    while (needed_val->prev->prev != nullptr && indx!=-2)
    {
        needed_val = needed_val->prev;
        indx--;
    }

    // ����������� ��������� prev � next �
    // ��������� ����������, �������� next
    // ����������� �� ����������� � prev ����������
    // �� �����������, ����� �������� ���������
    newnode->prev = needed_val;
    needed_val->next->prev = newnode;
    newnode->next = needed_val->next;
    needed_val->next = newnode;

    // ���������� ������
    size++;
}

//������� ������ ������

template<class T>
void Array<T>::DeleteAt(int indx)
{
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nDeletion of the asked index is impossible. Array is empty.\n\n");
    }

    if (indx > size - 1 && indx < 0)
    {
        throw out_of_range("\n\nIndex that you want to delete is out of range.\n\n");
    }

    Node<T>* buff = head;

    // ���� ������ �������
    // � �����
    for (int i = 0; i < indx - 1; i++)
    {
        buff = buff->next;
    }

    // ����� ���������� ���������� ���
    // ����������� �������� �����
    // ���������� �� 1 �����
    for (int i = indx-1; i < size && buff->next != nullptr; i++)
    {
        buff->data = buff->next->data;
        buff = buff->next;
    }

    // ��������� ������
    size--;
    // �������� �������� ������
    tail = tail->prev;
    // ������� ��������� ���������� ��������
    delete tail->next;
    // �������� � ���� ������
    tail->next = nullptr;
}

//������� ��������� ��.

template<class T>
void Array<T>::removeLast()
{
    // ���� ������ �����, ��������
    // �� ������������
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nDeletion of the last index is impossible. Array is empty.\n\n");
    }
    // ���� ������� ������ 1 �� ���������
    // � �������� ������ � ������ ����������
    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    // � ������ ���� �������� ������ ��� 1
    else
    {
        // ���������� ������������� �������� ������
        Node* temp = tail;

        // ��������� �������� ��������������
        tail = tail->prev;
        // ��������� ��� �������� ����������
        tail->next = nullptr;
        // ��������� ��������� ����������
        delete temp;
    }
}

// �����

template<class T>
void Array<T>::print() const
{
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nPrinting array is impossible. It's empty.\n\n");
    }

    // ���������� ��� ������� �� ������
    Node<T>* current = head;

    cout << '\n';

    // ����� � ������ ���� ������� �������
    // � �� ��������������� ��������� �� ���������
    while (current != nullptr && current->full != false)
    {
        cout << current->data << " ";
        current = current->next;
    }
}

// ����� ������� � ����������� ������� ����������

template<class T>
bool Array<T>::search(T value) const
{
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nNo point to search, i guess. Array is empty.\n\n");
    }

    Node<T>* current = head;

    // ����������� �� ������ � ������� �����
    while (current != nullptr)
    {
        // � ������ ���� ������ ������ �������
        // ��������������� �������, ���������� true
        if (current->data == value)
        {
            return true;
        }

        current = current->next;
    }

    // ���� �� 1 ������� �� ������������ 
    // ������� � �����, ���������� false
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