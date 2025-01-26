#pragma once

// аппенд из ориг. двойных списков (не метод заданный в задании)
//  (методы с маленькой буквы - предусмотренные списками, а с большой - из задания, кроме оператора)

// метод добавленияэлемента, 1 перегрузка кторая 
// принимает параметр с типом значения шаблона. 
// (параметр по умолчанию есть, но при дублировании
// его в синтаксисе при выносе метода в inl файл 
// высвечивается ошибка, поэтому он только в синтаксисе хедера)
template<class T>
void Array<T>::append(T value, bool full_P)
{
    // воздание элемента с новым значением
    Node<T>* newNode = new Node<T>(value, full_P);

    // в случае если строка пуста (тейл и хед не обозначены)
    // и тейлу и хеду присваивается созданный элемент
    if (tail == nullptr)
    {
        head = tail = newNode;
        // сайз приравнивается одному
        size = 1;

        for (int i = 0; i < grow-1; i++)
        {
            // новый обьект пересоздается чтобы
            // указатель при каждом присваивании был разным
            // и все добавленные элементы не указывали на 1 ячейку

            Node<T>* newNode = new Node<T>(value, full_P);

            // в конец добавляется новый атрибут
            // и хвостовое значение меняется
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;

            // размер увеличивается на 1
            size++;
        }
    }
    else
    {
        // если при запросе верхней границы элементов с full!=0
        // это значение равно size-1 то есть кол-ву элементов
        // то новый элемент добавляется в конец
        if (GetUpperBound() == -1)
        {
            // цикл в котором добавляется такое кол-во элементов 
            // с заданным значением которое равно атрибуту grow
            for (int i = 0; i < grow; i++)
            {
                // новый обьект пересоздается чтобы
                // указатель при каждом присваивании был разным
                // и все добавленные элементы не указывали на 1 ячейку
                Node<T>* newNode = new Node<T>(value, full_P);

                // в конец добавляется новый атрибут
                // и хвостовое значение меняется
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;

                // размер увеличивается на 1
                size++;
            }
        }
        // в случае если в строке есть элементы
        // у которых атрибут full = 0 то значение
        // попадает в первый такой атрибут
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
                    // новый обьект пересоздается чтобы
                    // указатель при каждом присваивании был разным
                    // и все добавленные элементы не указывали на 1 ячейку
                    Node<T>* newNode = new Node<T>(value, full_P);

                    // в конец добавляется новый атрибут
                    // и хвостовое значение меняется
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode;

                    // размер увеличивается на 1
                    size++;
                }
            }
 
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

// метод увеличения/уменьшения размера

template<class T>
void Array<T>::SetSize(int size_P, int grow_P)
{
    if (size == size_P)
    {
        throw SizeTheSame("\n\nSize that you want to set is equal to the current one.\n\n");
    }
    // первым делом гроу изменяется в зависимости
    // с переданным параметром (даже если он был по умолчанию)
    grow = grow_P;

    // если нвый размер больше прежнего
    // то аппендится столько элементов, сколько
    // составляет разница между размерами
    if (size_P>size)
    {
        int diff = size_P - size;

        while(diff!=0)
        {
            append(T(), false); 
            diff--;
        }
    }
    // если переданный размер меньше чем нынешний
    else
    {
        // переменная для нахождения последнего
        // элемента который находится на индексе
        // равному новому размеру строки
        int size_buff = 1;
        // переменная с помощью которой будет 
        // произвдиться пробежка по элементам
        Node<T>* buff = head;
        // переменная для удаления последующих элементов
        Node<T>* buff_deleteing;

        // ищем нужный элемент
        while (size_buff!= size_P)
        {
            size_buff++;
            buff = buff->next;
        }

        // присваиваем переменной для
        // удаления значение
        // найденного элемента
        buff_deleteing = buff->next;

        // обнуляем в строке доступ к элементам
        // после нужного индекса
        buff->next = nullptr;

        // удаляем элементы которые мы урезали
        while (buff_deleteing->next != nullptr)
        {
            buff_deleteing = buff_deleteing->next;
            delete buff_deleteing->prev;
        }

        // удаляем переменную для удаления
        delete buff_deleteing;

        // меняем размер массива
        size = size_P;
    }
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
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nIt's impossible to remove all elements. Array is empty.\n\n");
    }

    // переменная для удаления
    Node<T>* buff = head;

    // удаляем все элементы по очереди кроме
    // последнего, т.к. условие не позволит сделать
    // это сразу в цикле
    while (buff->next != nullptr)
    {
        buff = buff->next;

        delete buff->prev;
    }

    // уже после цикла удаляем 
    // нашу переменную (последний эл.)
    delete buff;

    // обнуляем хед и тейл
    head = tail = nullptr;

    // обнуляем размер
    size = 0;
}

// возвращение значения по индексу (перегрузку оператора [] я сделала позже 
// и т.к. была задача сделать метод, я не стала использовать оператор и оставила так)
// при отсутствии запрашиваемого индекса возвращает стандартное значение для типа данных шаблона

// (решила не переделывать под перегрузку [] 
// т.к. оставила эту перегрузку для возвращения
// значения data а не константной ссылки на эл.
template<class T>
const T Array<T>::GetAt(int indx) const
{
    // если индекс входит в диапазон
    // элементов строчки

    if (indx > size - 1 && indx < 0)
    {
        throw out_of_range("\n\nIndex that you want to get at is out of range.\n\n");
    }

    // переменная для нахождения
    // нужного индекса
    int size_buff = 0;
    // переменная для пробега по строке
    Node<T>* buff = head;

    // пока не будет достигнут
    // определенный индекс
    while (size_buff != indx)
    {
        size_buff++;
        buff = buff->next;
    }

    // возвращаем найденное значение
    return buff->data;
}

// вставка элемента на какой-либо индекс

template<class T>
void Array<T>::SetAt(int indx, T elem)
{
    if (indx > size - 1 && indx < 0)
    {
        throw out_of_range("\n\nIndex that you want to set at is out of range.\n\n");
    }

    // также проверяем есть ли
    // переданный индекс в диапазоне
    int size_buff = 0;
    Node<T>* buff = head;

    // находим его в цикле
    while (size_buff != indx)
    {
        size_buff++;
        buff = buff->next;
    }

    // изменяем значение по индексу
    buff->data = elem;
}

// возвращение самого верхнего индекса (только ячейки, созданные как заполненные)

template<class T>
int Array<T>::GetUpperBound()
{
    Node<T>* buff = head;
    int buff_indx = 0;

    // пока не будет достигнута 
    // граница заполненных элементов
    while (buff->next != nullptr && buff->full != 0)
    {
        buff_indx++;
        buff = buff->next;
    }

    // в случае если там не стоит значение по умолчанию,
    // метод возвращает -1 как обознгачение того, что
    // в методе нет элементов которые отмечены как незаполенные
    if (buff->full!=false)
    {
        return -1;
    }

    // в другом случае возвращается индекс
    return buff_indx;
}

// удаление незаполненных ячеек

template<class T>
void Array<T>::FreeExtra()
{
    // переменная с индексом высшей границы
    int UpperBound = GetUpperBound();
    // переменная для пробега по элементам
    Node<T>* buff = head;
    // переменная для удаления
    // лишних элементов
    Node<T>* buff_deleteing;

    // пробегаемся по массиву пока не найдем
    // последний заполненный элемент
    for (int i = 0; i < UpperBound; i++)
    {
        buff = buff->next;
    }

    // инициализируем переменную для удаления
    buff_deleteing = buff->next;

    // обнуляем доступ к пустым элементам
    buff->next = nullptr;

    // удаляем все пстые элемента
    // кроме последнкго в цикле
    while (buff_deleteing->next != nullptr)
    {
        size--;

        buff_deleteing = buff_deleteing->next;
        delete buff_deleteing->prev;
    }

    // удаляем последний элемент
    delete buff_deleteing;
}

// перегрузка оператора

template<class T>
T Array<T>::operator[](int indx)
{
    if (indx > size - 1 && indx < 0)
    {
        throw out_of_range("\n\nIndex that you're seekin' for is out of range.\n\n");
    }

    // переменная для нахождения нужного индекса
    int size_buff = 0;
    // переменная для пробега по массиву
    Node<T>* buff = head;

    // ищем элемент под нужным индексом в цикле
    while (size_buff != indx)
    {
        size_buff++;
        buff = buff->next;
    }

    // возвращаем значение нужного элемента
    return buff->data;
}

// та же самая перегрузка оператора, но константная
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

// возаращает неконстантную ссылку на начало списка

template<class T>
const Array<T>::Node<T>& Array<T>::Get_data()
{
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nArray is empty.\n\n");
    }

    return *head;
}

// записывает на место какого-т индекса (т.к. а списках 
// действует принцип LIFO то и добавляется на нужный индекс с конца)

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

    // создаем новый элемент
    Node<T>* newnode = new Node<T>{ value };

    // переменная для пробега по списку 
    // с конца для каноничной вставки в
    // визуальное начало строки
    Node<T>* needed_val = tail;

    // ищем элемент под нужным индексом с помощью 
    // цикла и переданной переменной индекса
    while (needed_val->prev->prev != nullptr && indx!=-2)
    {
        needed_val = needed_val->prev;
        indx--;
    }

    // присваиваем значениям prev и next у
    // созданной переменной, значению next
    // предыдущего от вставленной и prev следующему
    // от вставленной, новые значения указатели
    newnode->prev = needed_val;
    needed_val->next->prev = newnode;
    newnode->next = needed_val->next;
    needed_val->next = newnode;

    // прибавляем размер
    size++;
}

//удалить нужный индекс

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

    // ищем нужный элемент
    // в цикле
    for (int i = 0; i < indx - 1; i++)
    {
        buff = buff->next;
    }

    // после нахождения перемещаем все
    // последующие элементы после
    // найденного на 1 назад
    for (int i = indx-1; i < size && buff->next != nullptr; i++)
    {
        buff->data = buff->next->data;
        buff = buff->next;
    }

    // уменьшаем размер
    size--;
    // изменяем значение хвоста
    tail = tail->prev;
    // удаляем последнее обрезанное значение
    delete tail->next;
    // отрезаем к нему доступ
    tail->next = nullptr;
}

//удалить последний эл.

template<class T>
void Array<T>::removeLast()
{
    // если строка пуста, цдаление
    // не проивзодится
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nDeletion of the last index is impossible. Array is empty.\n\n");
    }
    // если элемент только 1 он удаляется
    // и значения хвоста и головы обнуляются
    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    // в случае если значений больше чем 1
    else
    {
        // пеерменной присваивается значение хвоста
        Node* temp = tail;

        // хвостовое значение перелдвигается
        tail = tail->prev;
        // следующее его значение обнуляется
        tail->next = nullptr;
        // удаляется урезанная переменная
        delete temp;
    }
}

// вывод

template<class T>
void Array<T>::print() const
{
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nPrinting array is impossible. It's empty.\n\n");
    }

    // пеерменная для пробега по строке
    Node<T>* current = head;

    cout << '\n';

    // вывод в случае если элемент заплнен
    // и не инициализирован значением по умолчанию
    while (current != nullptr && current->full != false)
    {
        cout << current->data << " ";
        current = current->next;
    }
}

// поиск массива и возвращение булевой переменной

template<class T>
bool Array<T>::search(T value) const
{
    if (head == nullptr)
    {
        throw ContaineerIsEmpty("\n\nNo point to search, i guess. Array is empty.\n\n");
    }

    Node<T>* current = head;

    // пробегаемся по списку с помощью цикла
    while (current != nullptr)
    {
        // в случае если найден первый элемент
        // удовлетворяющий условию, возвращаем true
        if (current->data == value)
        {
            return true;
        }

        current = current->next;
    }

    // если ни 1 элемент не удовлетворил 
    // условию в цикле, возвращаем false
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