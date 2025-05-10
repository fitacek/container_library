#include "avl_tree.hpp"
#include <iostream>
AVLTree::AVLTree() {}

size_t AVLTree::size() const
{
    return nodeCount;
}

bool AVLTree::empty() const
{
    return nodeCount == 0;
}

bool AVLTree::insert(const int key, const int value)
{
    if (nodeCount == 0)
    {
        root = std::make_unique<Node>(key, value);
        nodeCount++;
        return true;
    }

    Node *head = root.get();
    Node *tail = nullptr;

    while (head != nullptr)
    {
        tail = head;
        if (key < head->key)
        {
            // go left
            head = head->left.get();
        }
        else if (key > head->key)
        {
            // go right
            head = head->right.get();
        }
        else
        {
            // trying to insert duplicate key
            return false;
        }
    }
    // head == nullptr
    // tail == parrent of head
    if (key < tail->key)
    {
        // insert new node to left
        tail->left = std::make_unique<Node>(key, value, tail);
    }
    else
    {
        // insert new node to right
        tail->right = std::make_unique<Node>(key, value, tail);
    }
    nodeCount++;
    // node is inserted, now there may be need to rebalance the tree
    return true;
}

void AVLTree::printInOrder() const{
    std::cout<<"Print inOrder:\n";
    printInOrderInternal(root.get());
    std::cout<<"\n";
}

void AVLTree::printInOrderInternal(Node * node) const{
    if (!node)
        return;
    printInOrderInternal(node->left.get());
    //std::cout<<node->key<<" ";
    node->print();
    printInOrderInternal(node->right.get());
};
    

AVLTree::Node::Node(int key, int value, Node *parrent) : key(key), value(value), parrent(parrent) {}

bool AVLTree::Node::isLeaf() const
{
    return left == nullptr && right == nullptr;
}

void AVLTree::Node::print() const
{
    std::cout << "key= " << key << ", "
              << "parent= " << (parrent != nullptr ? std::to_string(parrent->key) : "n") << ", "
              << "leftChild= " << (left != nullptr ? std::to_string(left->key) : "n") << ", "
              << "rightChild= " << (right != nullptr ? std::to_string(right->key) : "n") << std::endl;
}

std::optional<int> AVLTree::find(const int key) const{
    Node *head = root.get();
    Node *tail = nullptr;

    while (head != nullptr)
    {
        tail = head;
        if (key < head->key)
        {
            // go left
            head = head->left.get();
        }
        else if (key > head->key)
        {
            // go right
            head = head->right.get();
        }
        else
        {
            // key found, return the value
            return tail->value;
        }
    }
    // head == nullptr
    // tail == parrent of head
    // key not found, return empty optional
    return std::nullopt;
}
