#include "avl_tree.hpp"

AVLTree::AVLTree(){}



size_t AVLTree::size() const{
    return nodeCount;
}

bool AVLTree::empty() const {
    return nodeCount == 0;
}