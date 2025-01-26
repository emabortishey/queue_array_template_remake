#pragma once
#include <iostream>
#include "exceptionss.h"

using namespace std;

template<class T>
class Queue {
private:
    template<class T1>
    class Node {
    public:
        T1 data;
        Node* next;
        Node* prev;

        Node(T1 data) : data(data), next(nullptr), prev(nullptr) {}
    };

    Node<T>* head;
    Node<T>* tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}

    void append(T value);
    void removeLast();
    void print() const;
    bool search(T value) const;

    ~Queue();
};

#include "Queue.inl"