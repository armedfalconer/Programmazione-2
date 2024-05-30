#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>

#define OUT_OF_RANGE_E "List out of range" // out of range error
#define EMPTY_LIST_E "Empty List" // empty list error

template <typename T>
class List;

template <typename T>
class Node {
    public:
        Node(T data) : data(data), next(nullptr), prev(nullptr) {}

        T getData() const { return this->data; }
    
    private:
        T data;
        Node<T>* next;
        Node<T>* prev;

    friend class List<T>;
};

template <typename T>
class List {
    public:
        List() : root(nullptr) {}
        ~List();

        void insert(size_t index, T data);
        void append(T data) { this->insert(this->getLength(), data); }
        void push(T data) { this->insert(0, data); }

        List<T> slice(size_t start, size_t end) const;

        T get(size_t index) const;
        size_t getLength() const;
        std::string toString() const;

    private:
        Node<T>* root;

        Node<T>* search(size_t index) const;

};

#include "list.cpp"

#endif // LIST_H