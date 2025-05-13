#pragma once

#include <optional>
#include <memory>

// naive aproach with int as key and value.
// Will make it templated later
class AVLTree
{

public:
    AVLTree();
    ~AVLTree();
    bool insert(const int key, const int value);
    bool remove(const int key);

    std::optional<int> find(const int key) const;

    bool empty() const;
    size_t size() const;
    void clear();

    void printInOrder() const;

// private:
    struct Node
    {
        int key;
        int value;
        Node * left = nullptr;
        Node * right = nullptr;
        Node *parrent = nullptr;
        int deltaDepth = 0;

        Node(int key, int value, Node *parrent = nullptr);

        void print() const;
    };
    Node * root = nullptr;
    size_t nodeCount = 0;

    void printInOrderInternal(Node * node) const;

    void destroyTree(Node * root);

    void propagateUpDepthChange(Node * newNode);
    void rotateLeft(Node * x);
    void rotateRight(Node * x);
    void rotateLeftRight(Node * x);
    void rotateRightLeft(Node * x);

};