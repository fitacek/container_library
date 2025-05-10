#pragma once

#include <optional>
#include <memory>

// naive aproach with int as key and value.
// Will make it templated later
class AVLTree {

public:
    AVLTree();
   // ~AVLTree(){}
    bool insert(const int key, const int value);
    bool remove(const int key);

    void contains(const int key) const;
    std::optional<int>find(const int key) const;

    bool empty() const;
    size_t size() const;
    void clear();

private:
    struct Node {
        int key;
        int value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        std::unique_ptr<Node> parrent;
        Node(int key, int value) : key(key), value(value) {}
    };
    std::unique_ptr<Node> root;
    size_t nodeCount = 0;
};