#ifndef BST_HPP
#define BST_HPP

template <typename T>
struct BSTNode {
    T data;
    BSTNode<T>* left;
    BSTNode<T>* right;
    BSTNode<T>* parent;

    BSTNode<T>(T data) : data(data), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class BST {
    public:
        BST() : root(nullptr) {}
        ~BST() { this->deleteSubTree(this->root); }

        BSTNode<T>* insert(T data);
        BSTNode<T>* search(T key) const;
        BSTNode<T>* min() const { return this->min(this->root); }
        BSTNode<T>* max() const { return this->max(this->root); }
        BSTNode<T>* successor(T data) const;
        BSTNode<T>* predecessor(T data) const;
        void deleteNode(T data);

        BSTNode<T>* getRoot() const { return this->root; }
    private:
        BSTNode<T>* root;
        BSTNode<T>* min(BSTNode<T>* node) const;
        BSTNode<T>* max(BSTNode<T>* node) const;

        void transplant(BSTNode<T>* dest, BSTNode<T>* src);
        void deleteSubTree(BSTNode<T>* subTreeRoot);
};

#include "bst.cpp"

#endif // BST_HPP