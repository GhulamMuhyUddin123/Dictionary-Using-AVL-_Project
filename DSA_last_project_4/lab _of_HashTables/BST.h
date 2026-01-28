#ifndef BST_H
#define BST_H

#include "node.h"

class bst {
private:
    node* root;

    node* add(node* r, int d);
    bool search(node* r, int d);
    node* remove(node* r, int d);
    void inorder(node* r);
    int sum(node* r);

public:
    bst();

    bool isempty();
    void add(int d);
    bool search(int d);
    void remove(int d);
    void print();
    int sum();
};

#endif
