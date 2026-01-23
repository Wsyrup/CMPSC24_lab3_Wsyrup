#include "intbst.h"

#include <iostream>
using namespace std;

int getTest();

int main() {
    IntBST bst1;

    bst1.insert(4);
    bst1.insert(3);
    bst1.insert(6);
    bst1.insert(5);
    bst1.insert(7);
    bst1.insert(2);
    bst1.insert(1);
    
    cout << "BST: " << endl << "  pre-order: ";
    bst1.printPreOrder();
    cout << endl;
    cout << "removing leaf: 1" << endl;
    bst1.remove(1);
    cout << "removing node with one child: 3" << endl;
    bst1.remove(3);
    cout << "removing node with two children: 6" << endl;
    bst1.remove(6);
    cout << "  pre-order after removals: ";
    bst1.printPreOrder();
    cout << endl;

    return 0;
}