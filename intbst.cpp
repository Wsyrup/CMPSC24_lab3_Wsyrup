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
        n->left->parent = n;
        return true;
    }
    else {
        if (n->right) {
            return insert(value, n->right);
        }

        n->right = new Node(value);
        n->right->parent = n;
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
    if (!n) return NULL;
    if (value < n->info) return getNodeFor(value, n->left);
    else if (value > n->info) return getNodeFor(value, n->right);
    else return n;
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
    //predecessor is the rightmost node in the left subtree of the given value
    Node* current = getNodeFor(value, root);
    if (!current) return nullptr;

    Node* pred = current->left;
    Node* parent = current->parent;

    if (!pred) { 
        while (parent) { 
            // traverses back up the tree until it reaches the root
            //in search of a parent with a lower key.  If one exists, return it.
            //if none exists, return null (we are at the minimum node in the tree)
            if (parent->info < current->info) {
                return parent;
            }
            parent= parent->parent;
        }
        return NULL; 
    }
    //only case where no predecessor exists in left subtree is if no left
    //subtree exists.
    //also need to handle case where no predecessor exists (leftmost node in the tree)
    //how do we check if we are at the minimum value in the tree?


    while (pred->right) {
        pred = pred->right;
    }

    return pred;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    if(getPredecessorNode(value)) return getPredecessorNode(value)->info;
    return 0;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    // reverse of predecessor: leftmost node in the right subtree.
    Node* current = getNodeFor(value, root);
    if (!current) return nullptr;

    Node* succ = current->right;
    Node* temp = current;

    if (!succ) {
        while (temp->parent) {
            if (temp->parent->info > current->info) {
                return temp->parent;
            }
            temp = temp->parent;
        }
        return NULL;
    } 

    while (succ->left) {
        succ = succ->left;
    }

    return succ;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    if (getSuccessorNode(value)) return getSuccessorNode(value)->info;
    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    //goal: find a node and remove it, freeing its dynamic memory as well as 

    //algo:
    /*three (four) cases:
    1. Empty tree: return false
        a. single node: remove and return true

    *For case 2, 3 we must find the node. If the search fails, we return false
    2. Leaf node removal: If leaf, return to its parent and delete it from the parent,
       severing the connection.
    
    3. Non-leaf removal: Find node. Replace its value with its predecessor value. Then,
       recurse / repeat on the predecessor node.
    */
    cycles++;
    if (!root) return false; //empty tree

    //find node
    Node* to_remove = getNodeFor(value, root);
    // cout << "currently removing node: " << value << endl;

    if (!to_remove) return false; //node not found

    if (!to_remove->left && !to_remove->right) { // node is a leaf
        Node* parent = to_remove->parent;
        if (to_remove->info < parent->info) {
            parent->left = nullptr; //leaf on the left
        }
        else {
            parent->right = nullptr; //leaf on the right
        }
        delete to_remove;
        return true;        
    }
    
    //nonleaf case:
    if (!to_remove->left) {
        Node* parent = to_remove->parent;
        if (to_remove->info < parent->info) {
            parent->left = to_remove->right; 
        }
        else {
            parent->right = to_remove->right;
        }
        delete to_remove;
        return true;
    }
    else if (!to_remove->right) {
        Node* parent = to_remove->parent;
        if (to_remove->info < parent->info) {
            parent->left = to_remove->right; 
        }
        else {
            parent->right = to_remove->right;
        }
        delete to_remove;
        return true;    
    }
    else {
        int predecessor = getPredecessor(value); //<-- issue lies here. 
        //if no left child --> no left subtree --> can't call predecessor
        //instead, simply replace with right subtree (set the parent to point to right child of current node.)
        remove(predecessor);
        to_remove->info = predecessor; //"remove" the value
        return true;
    }

    

    //fails all removal tests. I get the feeling that my algorithm is
    //somehow incorrect. Maybe I've misunderstood what is being asked of me?
    //i need to clarify maybe at office hours.
    //there is something wrong. Fix this later.
}
