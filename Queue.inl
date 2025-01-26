#pragma once

// ����� ���������� ��������

template<class T>
void Queue<T>::append(T value)
{
    // ������� ����� ������� � 
    // �������������� ��� ���������
    Node<T>* newNode = new Node<T>(value);

    // ���� ������� �����, ��������� 
    // � �������� �������� 
    // ������������ ����� ���������
    if (tail == nullptr)
    {
        head = tail = newNode;
    }
    // � ��������� ������ ��������� ��� � �����
    // � �������� �������� ������
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// �������� ���������� (������� � �������) ��������

template<class T>
void Queue<T>::removeLast()
{
    // ������ ����
    if (head == nullptr)
    {
        cout << "������ ����. �������� ����������.\n";
        return;
    }
    // ���� � ������ 1 �������, ��
    // ��������� � ��������� �
    // ������� �������� ����������
    else if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    // ���� ��������� ������ ��� 1
    // �� ������������� ��������
    // �������� � ��������� 
    // ��������� ���������
    else
    {
        Node* temp = head;

        head = head->next;
        head->prev = nullptr;

        delete temp;
    }
}

// ����� ������ ������� �� �����

template<class T>
void Queue<T>::print() const
{
    // ���������� ��� ������� �� ���������
    Node<T>* current = head;

    // ����� ���� ��������� �� �������
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// ����� ������ ���������

template<class T>
bool Queue<T>::search(T value) const
{
    // ���������� ��� ������� �� �������
    Node<T>* current = head;

    // ����� �������� ���������������� �������
    while (current != nullptr)
    {
        if (current->data == value)
        {
            // ��� ���������� ���������� true
            return true;
        }

        current = current->next;
    }

    // ���� ������� ���������������
    // ������� �� ������, ���������� false
    return false;
}

template<class T>
Queue<T>::~Queue()
{
    Node<T>* current = head;

    while (current != nullptr)
    {
        Node<T>* nextNode = current->next;

        delete current;
        current = nextNode;
    }
}