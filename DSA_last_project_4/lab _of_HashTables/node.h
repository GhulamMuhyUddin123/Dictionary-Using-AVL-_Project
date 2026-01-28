//
// Created by Muhammad Hammad on 10/01/2026.
//


#ifndef NODE_H
#define NODE_H

class node {
public:
    int data;
    node* left;
    node* right;

    node(int d) {
        data = d;
        left = NULL;
        right = NULL;
    }
};

#endif
