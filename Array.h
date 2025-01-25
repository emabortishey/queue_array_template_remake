#pragma once
#include <iostream>

using namespace std;



template<class T>
class Array {
private:
    template<class T1>
    class Node;

    Node<T>* head;
    Node<T>* tail;
    int size;

    template<class T1>
    class Node {
    public:
        T1 data;
        // атрибут означающий заполнен узел или нет
        bool full;
        Node* next;
        Node* prev;

        Node() : data(0), full(false), next(nullptr), prev(nullptr) {}
        explicit Node(T1 data_P) : data(data_P), full(true), next(nullptr), prev(nullptr) {}

        friend Array;
    };

public:
    Array() = default;

    void append();
    void append(T value);
    void Append(Array& obj);
    void removeLast();
    void print() const;
    bool search(T value) const;
    int GetSize();
    void SetSize(int size, int grow = 1);
    bool IsEmpty();
    void RemoveAll();
    const T GetAt(int index);
    void SetAt(int index, T elem);
    int GetUpperBound();
    void FreeExtra();
    T operator[](int indx);
    Node<T>& Get_data();
    void InsertAt(int indx, T value);
    void DeleteAt(int indx);

    ~Array();
};

#include "Array.inl"