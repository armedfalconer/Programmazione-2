#include "list.hpp"
#include <iostream>
#include <string>
#include <sstream>

template <typename T>
List<T>::~List() {
    Node<T>* curr = this->root;
    
    while(curr != nullptr) {
        Node<T>* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

template <typename T>
void List<T>::insert(size_t index, T data) {
    // checking if the list is long enough
    if(index > this->getLength()) throw std::runtime_error(OUT_OF_RANGE_E);

    // allocating nodes
    Node<T>* newNode = new Node(data);
    if(not newNode) throw std::bad_alloc();
    
    // temp nodes
    Node<T>* curr = this->root;
    Node<T>* prev = nullptr;

    // traversing list
    for(size_t i = 0; i < index and curr != nullptr; i++) {
        prev = curr;
        curr = curr->next;
    }

    // updating nodes
    if(prev) prev->next = newNode; 
    else this->root = newNode; // when prev does not exist curr = root
    newNode->prev = prev;

    if(curr) curr->prev = newNode;
    newNode->next = curr;
}

template <typename T>
List<T> List<T>::slice(size_t start, size_t end) const {
    if(end > this->getLength()) throw std::runtime_error(OUT_OF_RANGE_E);
    if(not this->root) throw std::runtime_error(EMPTY_LIST_E);

    List<T> l;
    if(start > end) return l;

    Node<T>* temp;

    try {
        temp = this->search(start);
    }
    catch(const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return l;
    }   

    for(size_t i = start; i < end; i++) {
        l.append(temp->data);
        temp = temp->next;
    }    

    return l;
}

template <typename T>
T List<T>::get(size_t index) const {
    if(index > this->getLength()) throw std::runtime_error(OUT_OF_RANGE_E);
    if(not this->root) throw std::runtime_error(EMPTY_LIST_E);

    // traversing 
    Node<T>* temp = this->root;
    for(size_t i = 0; i < index; i++) temp = temp->next;
    return temp->data;
}

template <typename T>
size_t List<T>::getLength() const {
    size_t len = 0;
    Node<T>* temp = this->root;

    while(temp != nullptr) {
        temp = temp->next;
        len++;
    }

    return len;
}

template <typename T>
std::string List<T>::toString() const {
    if(not this->root) return "Empty List";

    std::stringstream ss;
    for(Node<T>* temp = this->root; temp != nullptr; temp = temp->next) {
        ss << temp->data << " ";
    }

    return ss.str();
}

template <typename T>
Node<T>* List<T>::search(size_t index) const {
    if(index > this->getLength()) throw std::runtime_error(OUT_OF_RANGE_E);
    if(not this->root) throw std::runtime_error(EMPTY_LIST_E);

    Node<T>* temp = this->root;
    for(size_t i = 0; i < index; i++) temp = temp->next;
    
    return temp;
}