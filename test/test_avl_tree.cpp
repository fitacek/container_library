#include "../include/avl_tree.hpp"
#include <iostream>
using namespace std;

int main(){
    AVLTree t = AVLTree();
    cout<<t.size()<<endl;

    t.insert(4,0);
    t.insert(2,0);
    t.insert(3,0);
    t.insert(7,0);
    t.insert(6,0);
    t.insert(8,0);

    t.printInOrder();
    return 0;
}