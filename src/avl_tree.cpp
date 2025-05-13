#include "../include/avl_tree.hpp"
#include <iostream>

AVLTree::AVLTree() {}

AVLTree::~AVLTree(){
    clear();
}

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
    std::cout<<">>insert("<<key<<")\n";
    if (nodeCount == 0)
    {
        root = new Node(key, value);
        nodeCount++;
        return true;
    }

    Node *head = root;
    Node *tail = nullptr;

    while (head != nullptr)
    {
        tail = head;
        if (key < head->key)
            head = head->left; // go left
        else if (key > head->key)
            head = head->right; // go right
        else
            return false; // key already exists
    }
    // head == nullptr
    // tail == parrent of head (never nullptr)

    Node * newNode = new Node(key, value, tail);
    if (key < tail->key)
        tail->left = newNode; // insert new node to left
    else
        tail->right = newNode; // insert new node to right

    nodeCount++;
    // node is inserted, now there may be need to rebalance the tree
    propagateUpDepthChange(newNode);
    return true;
}

void AVLTree::printInOrder() const
{
    std::cout << "Print inOrder:\n";
    std::cout << "Root =" << root->key << "\n";
    printInOrderInternal(root);
    std::cout << "\n";
}

void AVLTree::printInOrderInternal(Node *node) const
{
    if (!node)
        return;
    printInOrderInternal(node->left);
    // std::cout<<node->key<<" ";
    node->print();
    printInOrderInternal(node->right);
};

AVLTree::Node::Node(int key, int value, Node *parrent) : key(key), value(value), parrent(parrent) {}

// bool AVLTree::Node::isLeaf() const
// {
//     return left == nullptr && right == nullptr;
// }

void AVLTree::Node::print() const
{
    std::cout << "key= " << key << ", "
              << "parent= " << (parrent != nullptr ? std::to_string(parrent->key) : "n") << ", "
              << "leftChild= " << (left != nullptr ? std::to_string(left->key) : "n") << ", "
              << "rightChild= " << (right != nullptr ? std::to_string(right->key) : "n") <<", "
              << "deltaDepth= " << deltaDepth
              << std::endl;
}

std::optional<int> AVLTree::find(const int key) const
{
    Node *head = root;
    Node *tail = nullptr;

    while (head != nullptr)
    {
        tail = head;

        if (key < head->key)
            head = head->left; // go left
        else if (key > head->key)            
            head = head->right; // go right
        else
            return tail->value; // key found, return the value
    }
    // head == nullptr
    // tail == parrent of head
    
    return std::nullopt; // key not found, return empty optional
}

void AVLTree::clear()
{
    destroyTree(root);
    root = nullptr;
    nodeCount = 0;
}

void AVLTree::destroyTree(Node * root){
    // TODO: recursion could be bad for performance & memory reasons
    if (root == nullptr)
        return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}


void AVLTree::rotateLeft(Node * x)
{
    std::cout<<"rotateLeft()\n";
    Node * y = x->right;
    Node * b = y->left;
    Node * p = x->parrent;

    y->left = x;
    x->right = b;

    y->deltaDepth = 0;
    x->deltaDepth = 0;

    if (x == root){
        root = y;
        root->parrent = nullptr;
    } else {
        // x has parrent
        if (p->left == x)
            p->left = y;
        else
            p->right = y;
    }

    // set parrents
    y->parrent = p;
    x->parrent = y;
    if (b)
        b->parrent = x;
}

void AVLTree::rotateRight(Node * x){
    std::cout<<"rotateRight()\n";
    Node * y = x->left;
    Node * b = y->right;
    Node * p = x->parrent;

    y->right = x;
    x->left = b;

    y->deltaDepth = 0;
    x->deltaDepth = 0;

    if (x == root){
        root = y;
        root->parrent = nullptr;
    } else {
        // x has parrent
        if (p->left == x)
            p->left = y;
        else if (p->right == x)
            p->right = y;
        else
            exit(10); // should be unreachable state
    }

    // set parrents
    y->parrent = p;
    x->parrent = y;
    if (b)
        b->parrent = x;
}

void AVLTree::rotateLeftRight(Node * x){

}

void AVLTree::rotateRightLeft(Node * x){

}

void AVLTree::propagateUpDepthChange(Node *newNode)
{
    if (newNode == root)
        return;

    // newNode is not root. Therefore it has parrent
    
    if (newNode->parrent->left != nullptr && newNode->parrent->right != nullptr) // deltaDepth of parrent has not changed
        return;
    else{
        // deltaDepth of parrent has changed
        if (newNode->parrent->left == newNode) 
            newNode->parrent->deltaDepth--; // newNode is leftChild
        else
            newNode->parrent->deltaDepth++; // newNode is rightChild
    }

    Node * head = newNode->parrent;
    while (head != nullptr){
        // traverse from newNode->parrent to root
        switch (head->deltaDepth){
            case 0: return; // end propagation
            case 1: break;
            case -1: break;
            case 2: // rotate and end propagation
                if (head->right->deltaDepth == 1)
                    rotateLeft(head);
                else if (head->right->deltaDepth == -1){
                    rotateRightLeft(head);
                }
                return;

            case -2: // rotate and end propagation
                if (head->left->deltaDepth == -1)
                    rotateRight(head);
                else if (head->left->deltaDepth == 1){
                    rotateLeftRight(head);
                }
                return;
        }

        // deltaDepth for head was 1 or -1
        if (head->parrent != nullptr){
            if (head->parrent->left == head)
                head->parrent->deltaDepth--;
            else 
                head->parrent->deltaDepth++;
        }

        head = head->parrent;
    }


}