#pragma once

// метод доабвления элемента

template<class T>
void Queue<T>::append(T value)
{
    // создаем новый элемент и 
    // инициализируем его значением
    Node<T>* newNode = new Node<T>(value);

    // если очередь пуста, хвостовое 
    // и головное значение 
    // приравниваем новой переменнй
    if (tail == nullptr)
    {
        head = tail = newNode;
    }
    // в противном случае добавляем его в конец
    // и изменяем значение хвоста
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// удаление последнего (первого в очереди) элемента

template<class T>
void Queue<T>::removeLast()
{
    // список пуст
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nDeletion of the last index is impossible. Queue is empty.\n\n");
    }
    // если в списке 1 элемент, он
    // удаляется и хвостовой и
    // голоной атрибуты обнуляются
    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    // если элементов больше чем 1
    // то передвигается головное
    // значение и удаляется 
    // урезанная пременная
    else
    {
        Node* temp = head;

        head = head->next;
        head->prev = nullptr;

        delete temp;
    }
}

// метод вывода очереди на экран

template<class T>
void Queue<T>::print() const
{
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nPrinting queue is impossible. It's empty.\n\n");
    }

    // переменная для пробега по элементам
    Node<T>* current = head;

    // вывод всех элементов по порядку
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// метод поиска элементов

template<class T>
bool Queue<T>::search(T value) const
{
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nNo point to search, i guess. Array is empty.\n\n");
    }

    // переменная для пробега по очереди
    Node<T>* current = head;

    // поиск элемента удовлетворяющего условию
    while (current != nullptr)
    {
        if (current->data == value)
        {
            // при нахождении возвращаем true
            return true;
        }

        current = current->next;
    }

    // если элемент удовлетворяющий
    // условию не найден, возвращаем false
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