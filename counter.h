/*counter.h*/

//
// Shyam Patel (NetID: spate54)
// U. of Illinois, Chicago
// CS 341, Fall 2018
// Project #03: Counter container
//
// The Counter container is a set with no duplicates. However, it keeps
// a count of how many times an element was inserted, hence the name
// "Counter". Users of the Counter container can test for set membership,
// as well as obtain an element's count.
//
// Example: suppose C is a Counter, and you insert the elements 3, 11,
// 5, 11, 3, and 11. Then C contains the elements {3, 5, 11}, where 3's
// count is 2, 5's count is 1, and 11's count is 3.
//
// Given N elements, search operations are O(lgN), and insert is O(N); these
// are average-time complexities. In terms of space, the container will
// consume at most 4N space.
//

#pragma once

#include <iostream>
#include <iterator>

using std::cout;  // for debug printing
using std::endl;

template<typename T>
class Counter {
private:
    class Node {           // Node class :
    public:
        T     key;         //   key value stored in node
        int   count;       //   # of key occurrences
        Node* left;        //   left child node
        Node* right;       //   right child node
        Node* parent;      //   parent node

        Node(T value)      //   node class constructors :
            : key(value), count(1), left(nullptr), right(nullptr), parent(nullptr) { }

        Node(T value, int n, Node* p)
            : key(value), count(n), left(nullptr), right(nullptr), parent(p) { }
    };//end Node class


    int   count;           // # of elements in set
    Node* root;            // root node of tree


    class iterator {       // iterator class :
    private:
        Node*    curr;     //   current node ptr
        Counter* cptr;     //   counter ptr


    public:
        //
        // iter class constructor
        //
        iterator(Node* n, Counter* c)
            : curr(n), cptr(c) { }

        //
        // operator++ : increment iter
        //
        iterator& operator++() {
            // current node has right child
            if (curr->right != nullptr) {
                // get right child node
                curr = curr->right;
                // move to farthest left node of subtree
                while (curr->left != nullptr)
                    curr = curr->left;
            }
            // current node doesn't have right child
            else {
                // get parent node
                Node* p = curr->parent;
                // move up tree leftwise until current node
                // is left child or parent is null
                while (p != nullptr && curr == p->right) {
                    curr = p;
                    p = p->parent;
                }
                curr = p;
            }
            return *this;
        }//end operator++

        //
        // operator* : dereference iter
        //
        const T& operator*() {
            // return key value at current node
            return curr->key;
        }//end operator*

        //
        // operator!= : LHS iter != RHS iter
        //
        bool operator!=(const iterator& rhs) {
            if (cptr != rhs.cptr)
                return true;              // return if LHS counter != RHS counter
            else
                return curr != rhs.curr;  // return if LHS node    != RHS node
        }//end operator!=
    };//end iterator class


public:
    //
    // constructor: initialize empty binary tree
    //
    Counter()
        : count(0), root(nullptr) { }


    //
    // copy constructor: copy other binary tree
    //
    Counter(const Counter& other)
        : count(other.count) {
        root = copyNodes(other.root, nullptr);
    }//end copy constructor


private:
    //
    // recursive helper function to copy nodes in binary tree
    //
    Node* copyNodes(const Node* n, Node* parent) {
        // base case : null
        if (n == nullptr)
            return nullptr;

        // allocate node + copy key value, count and parent
        Node* newNode  = new Node(n->key, n->count, parent);

        // recursively copy left + right subtrees
        newNode->left  = copyNodes(n->left, newNode);
        newNode->right = copyNodes(n->right, newNode);

        return newNode;
    }//end copyNodes()


public:
    //
    // destructor: deallocate nodes
    //
    ~Counter() {
        deleteNodes(root);
    }//end destructor


private:
    //
    // recursive helper function to deallocate nodes in binary tree
    //
    void deleteNodes(Node* n) {
        if (n == nullptr)       // base case : null
            return;

        deleteNodes(n->left);   // recursively call left subtree
        deleteNodes(n->right);  // recursively call right subtree

        delete n;               // deallocate node
    }//end deleteNodes()


public:
    //
    // size()
    //
    // Returns the # of elements in the set.
    //
    // Time complexity: O(1).
    //
    int size() const {
        return count;
    }//end size()


    //
    // empty()
    //
    // Returns true if the set is empty, false if not.
    //
    // Time complexity: O(1).
    //
    bool empty() const {
        return count == 0;
    }//end empty()


    //
    // clear()
    //
    // Empties the set, deleting all elements and counts.
    //
    void clear() {
        deleteNodes(root);  // deallocate nodes
        count = 0;          // reset # of elements in set
        root  = nullptr;    // reset root node of tree
    }//end clear()


    //
    // [e]
    //
    // Returns true if set contains e, false if not.
    //
    // NOTE: since the type of e is unknown, elements are compared using <.
    // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
    //
    // Time complexity: average-case O(lgN).
    //
    bool operator[](const T& e) {
        Node* curr = root;           // get root of tree

        while (curr != nullptr) {
                                     // e is = current node :
            if (!(e < curr->key) && !(curr->key < e))
                return true;         //   set contains e
            else if (e < curr->key)  // e is < current node :
                curr = curr->left;   //   move to left node
            else                     // e is > current node :
                curr = curr->right;  //   move to right node
        }
        return false;                // set doesn't contain e
    }//end operator[]


    //
    // (e)
    //
    // Returns a count of how many times e has been inserted into the set;
    // the count will be 0 if e has never been inserted.
    //
    // NOTE: since the type of e is unknown, elements are compared using <.
    // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
    //
    // Time complexity: average-case O(lgN).
    //
    int operator()(const T& e) const {
        Node* curr = root;           // get root of tree

        while (curr != nullptr) {
                                     // e is = current node :
            if (!(e < curr->key) && !(curr->key < e))
                return curr->count;  //   return count
            else if (e < curr->key)  // e is < current node :
                curr = curr->left;   //   move to left node
            else                     // e is > current node :
                curr = curr->right;  //   move to right node
        }
        return 0;                    // set doesn't contain e
    }//end operator()


    //
    // insert(e)
    //
    // "If e is not a member of the set, e is inserted and e's count set to 1."
    // If e is already in the set, it is *not* inserted again; instead, e's
    // count is increased by 1. Sets are unbounded in size, and elements are
    // inserted in order as defined by T's < operator; this enables in-order
    // iteration.
    //
    // NOTE: since the type of e is unknown, elements are compared using <.
    // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
    //
    // Time complexity: worst-case O(N).
    // Space complexity: 4N.
    //
    void insert(const T& e) {
        root = _insert(root, e);
    }//end insert()


private:
    Node* _insert(Node* curr, const T& e) {
        if (curr == nullptr) {        // subtree is empty :
            count++;                  //   increment # of elements in set
            return new Node(e);       //   allocate + return e node
        }                             // e is = current node :
        else if (!(e < curr->key) && !(curr->key < e)) {
            curr->count++;
        }
        else if (e < curr->key) {     // e is < current node :
            Node* lchild   = _insert(curr->left, e);
            curr->left     = lchild;  //   add left child
            lchild->parent = curr;    //   set parent
        }
        else {                        // e is > current node :
            Node* rchild   = _insert(curr->right, e);
            curr->right    = rchild;  //   add right child
            rchild->parent = curr;    //   set parent
        }
        return curr;                  // return current node
    }//end _insert()


public:
    //
    // += e
    //
    // Inserts e into the set; see insert.
    //
    // Time complexity: worst-case O(N).
    // Space complexity: 4N.
    //
    Counter& operator+=(const T& e) {
        //
        // insert e into "this" set:
        //
        this->insert(e);

        // return "this" updated set:
        return *this;
    }//end operator+=


    //
    // lhs = rhs;
    //
    // Makes a deep copy of rhs (right-hand-side) and assigns into
    // lhs (left-hand-side). Any existing elements in the lhs
    // are destroyed *before* the deep copy is made.
    //
    // NOTE: the lhs is "this" object.
    //
    Counter& operator=(const Counter& rhs) {
        //
        // NOTE: where is the lhs in the function call? The lhs operand is
        // hidden --- it's "this" object. So think this->operator=(rhs).
        //

        // check for self-assignment:
        if (this == &rhs)   // S = S;
            return *this;

        if (!empty())       // set isn't empty :
            clear();        //   empty set

        count = rhs.count;  // make deep copy of rhs
        root = copyNodes(rhs.root, nullptr);

        //
        // return "this" updated set:
        //
        return *this;
    }//end operator=


    //
    // begin()
    //
    // Returns an iterator denoting the first element of the set. If the
    // set is empty, begin() == end(). The iterator will advance through
    // the elements in order, as defined by T's < operator.
    //
    iterator begin() {
        // set is empty : return nullptr iter
        if (empty())
            return iterator(nullptr, this);

        // get root of tree
        Node* curr = root;
        // move to farthest left node
        while (curr->left != nullptr)
            curr = curr->left;

        // return iter initialized with farthest left node
        return iterator(curr, this);
    }//end begin()


    //
    // end()
    //
    // Returns an iterator denoting the end of the iteration space --- i.e.
    // one past the last element of the set. If the set is empty, then
    // begin() == end().
    //
    iterator end() {
        // return iter initialized with nullptr
        return iterator(nullptr, this);
    }//end end()

};//end Counter class
