// intbst.cpp
// Implements class IntBST
// Christian Kantchev, 1/22/26

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = NULL;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
    root = NULL;
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    //postorder traversal of tree, then free up heap on the way up
    if (!n) return;

    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (!root) {
        root = new Node(value);
        return true;
    }

    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    //if value < n->val and !n->left, n->left = new Node;
    //if n->left, recurse on n->left;
    //right is analogously defined.
    if (value == n->info) { //base case: duplicate val
        return false;
    }
    
    if (value < n->info) {
        if (n->left) {
            return insert(value, n->left);
        }

        n->left = new Node(value);
        return true;
    }
    else {
        if (n->right) {
            return insert(value, n->right);
        }

        n->right = new Node(value);
        return true;
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
    // cout << endl;
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    //preorder iteration: root->left->right
    if (!n) return;

    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
    // cout << endl;
}
void IntBST::printInOrder(Node *n) const {
    //inorder iteration: left->root->right
    if (!n) return;

    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
    // cout << endl;
}

void IntBST::printPostOrder(Node *n) const {
    //postorder iteration: left->right->root
    if (!n) return;

    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    // if (!root) return -1;
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    //sum of nodes is given by sum of values in left subtree
    //+ sum of value in right subtree. 
    //postorder traversal

    if (!n) return 0;

    int left = sum(n->left);
    int right = sum(n->right);
    return n->info + left + right;
}

// return count of values
int IntBST::count() const {
    // if (!root) return -1;
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    //similar to sum. count is equal to count in left subtree + count in right subtree + 1;
    //postorder traversal, add 1 to the running count on each step.
    if (!n) return 0; //null nodes should count as 0;

    return count(n->left) + count(n->right) + 1;
    //since current node is processed last, this is still a postorder traversal (even though
    // it is only on one line.)

}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    //Basically: search for a value in a BST
    //binary search?
    if (!n) return NULL; //leaf node reached but value not found
    if (value < n->info) {
        getNodeFor(value, n->left);
    }
    else if (value > n->info) {
        getNodeFor(value, n->right);
    }
    else { //n->val = value (desired value found)
        return n;
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    //recursive solution would involve calling getNodeFor with root, and
    //returning true if return is a node or false if return is null

    //iteratively:
    //binary search within the tree:
    //since this is a binary tree, stepping into left or right is equivalent
    //to halving the search space. Thus, we maintain a runtime of O(logn)
    Node* current = root;
    while (current) {
        if (value == current->info) {
            return true;
        }
        else if (value < current->info) {
            current = current->left;
        }
        else { //value > current
            current = current->right;
        }
    }

    return false;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    return NULL; // REPLACE THIS NON-SOLUTION
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    return -1; // REPLACE THIS NON-SOLUTION
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    return NULL; // REPLACE THIS NON-SOLUTION
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    return -1; // REPLACE THIS NON-SOLUTION
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    return false; // REPLACE THIS NON-SOLUTION
}
