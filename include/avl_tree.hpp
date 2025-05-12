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

private:
    struct Node
    {
        int key;
        int value;
        Node * left = nullptr;
        Node * right = nullptr;
        // std::unique_ptr<Node> left;
        // std::unique_ptr<Node> right;
        Node *parrent = nullptr; // using raw pointer here because unique_ptr cannot be copied. shared_ptr has RC overhead and observer_ptr is c++23 feature
        
        //size_t depthLeft = 0; // depth of left subtree
        //size_t depthRight = 0; // depth of right subtree
        int deltaDepth = 0;

        Node(int key, int value, Node *parrent = nullptr);
        // bool isLeaf() const;

        void print() const;
    };
    Node * root = nullptr;
    // std::unique_ptr<Node> root;
    size_t nodeCount = 0;

    void printInOrderInternal(Node * node) const;

    void destroyTree(Node * root);

    void propagateUpDepthChange(Node * newNode);
    void rotateLeft(Node * node);
    void rotateRight(Node * node);
    void rotateLeftRight(Node * node);
    void rotateRightLeft(Node * node);

};