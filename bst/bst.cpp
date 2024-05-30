#include "bst.hpp"
#include <iostream>

template <typename T>
BSTNode<T>* BST<T>::insert(T data) {
    BSTNode<T>* current = this->root;
    BSTNode<T>* prev = nullptr;

    // traversing the tree
    while(current != nullptr) {
        prev = current;

        if(data > current->data) current = current->right;
        else current = current->left;
    }

    // allocating space for new node
    BSTNode<T>* newNode = new BSTNode(data);
    if(not newNode) throw std::bad_alloc();

    // inserting node in effective position
    newNode->parent = prev;
    if(prev == nullptr) this->root = newNode;
    else if(data > prev->data) prev->right = newNode;
    else prev->left = newNode;

    return newNode;    
}

template <typename T>
BSTNode<T>* BST<T>::search(T key) const {
    BSTNode<T>* node = this->root;

    while(node != nullptr) {
        if(key == node->data) return node;
        else if(key > node->data) node = node->right;
        else node = node->left;
    }

    // node not found in the tree
    return nullptr;
}

template <typename T>
BSTNode<T>* BST<T>::min(BSTNode<T>* node) const {
    BSTNode<T>* temp = node;
    while(temp->left != nullptr) temp = temp->left;

    return temp;
}

template <typename T>
BSTNode<T>* BST<T>::max(BSTNode<T>* node) const {
    BSTNode<T>* temp = node;
    while(temp->right != nullptr) temp = temp->right;

    return temp;
}

template <typename T>
BSTNode<T>* BST<T>::successor(T data) const {
    // searching the node
    BSTNode<T>* node = this->search(data);
    if(node == nullptr) return nullptr;

    // searching the successor
    if(node->right != nullptr) return this->min(node->right);

    BSTNode<T>* p = node->parent;
    while(p != nullptr and node == p->right) {
        node = p;
        p = p->right;
    }

    return p;
}

template <typename T>
BSTNode<T>* BST<T>::predecessor(T data) const {
    BSTNode<T>* node = this->search(data);
    if(node == nullptr) return nullptr;

    if(node->left != nullptr) return this->max(node->left);

    BSTNode<T>* p = node->parent;
    while(p != nullptr and node == p->left) {
        node = p;
        p = p->parent;
    }

    return p;
}

template <typename T>
void BST<T>::transplant(BSTNode<T>* dest, BSTNode<T>* src) {
    if(dest->parent == nullptr) this->root = src;
    else if(dest == dest->parent->left) dest->parent->left = src;
    else dest->parent->right = src;

    if(src != nullptr) src->parent = dest->parent;
}

template <typename T>
void BST<T>::deleteNode(T data) {
    BSTNode<T>* node = this->search(data);
    if(node == nullptr) throw std::runtime_error("Unable to remove node");

    if(node->left == nullptr) this->transplant(node, node->right);
    else if(node->right == nullptr) this->transplant(node, node->left);
    else {
        BSTNode<T>* min = this->min(node->right);
        if(min != node->right) {
            this->transplant(min, min->right);
            min->right = node->right;
            min->right->parent = min;
        }
        this->transplant(node, min);
        min->left = node->left;
        min->left->parent = min;
    }

    delete node;
}

template <typename T>
void BST<T>::deleteSubTree(BSTNode<T>* subTreeRoot) {
    if(subTreeRoot) {
        this->deleteSubTree(subTreeRoot->left);
        this->deleteSubTree(subTreeRoot->right);
        delete subTreeRoot;
    }
}