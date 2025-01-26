#pragma once

// метод доабвлени€ элемента

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
    // в противном случае добавл€ем его в конец
    // и измен€ем значение хвоста
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
        cout << "—писок пуст. ”даление невозможно.\n";
        return;
    }
    // если в списке 1 элемент, он
    // удал€етс€ и хвостовой и
    // голоной атрибуты обнул€ютс€
    else if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    // если элементов больше чем 1
    // то передвигаетс€ головное
    // значение и удал€етс€ 
    // урезанна€ пременна€
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
    // переменна€ дл€ пробега по элементам
    Node<T>* current = head;

    // вывод всех элементов по пор€дку
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
    // переменна€ дл€ пробега по очереди
    Node<T>* current = head;

    // поиск элемента удовлетвор€ющего условию
    while (current != nullptr)
    {
        if (current->data == value)
        {
            // при нахождении возвращаем true
            return true;
        }

        current = current->next;
    }

    // если элемент удовлетвор€ющий
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