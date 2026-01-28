#include <iostream>
#include "BST.h"
using namespace std;

bst::bst() {
    root = NULL;
}

bool bst::isempty() {
    return root == NULL;
}

// chronological insertion (not value based)
node* bst::add(node* r, int d) {
    if (r == NULL) {
        return new node(d);
    }

    if (r->left == NULL) {
        r->left = add(r->left, d);
    } else {
        r->right = add(r->right, d);
    }

    return r;
}

void bst::add(int d) {
    root = add(root, d);
}

bool bst::search(node* r, int d) {
    if (r == NULL) {
        return false;
    }
    if (r->data == d) {
        return true;
    }
    return search(r->left, d) || search(r->right, d);
}

bool bst::search(int d) {
    return search(root, d);
}

// simple remove (leaf or single child preferred – lab level)
node* bst::remove(node* r, int d) {
    if (r == NULL) {
        return NULL;
    }

    if (r->data == d) {
        if (r->left == NULL && r->right == NULL) {
            delete r;
            return NULL;
        }
        if (r->left != NULL) {
            return r->left;
        }
        return r->right;
    }

    r->left = remove(r->left, d);
    r->right = remove(r->right, d);
    return r;
}

void bst::remove(int d) {
    root = remove(root, d);
}

void bst::inorder(node* r) {
    if (r == NULL) {
        return;
    }
    inorder(r->left);
    cout << r->data << " ";
    inorder(r->right);
}

void bst::print() {
    inorder(root);
}

int bst::sum(node* r) {
    if (r == NULL) {
        return 0;
    }
    return r->data + sum(r->left) + sum(r->right);
}

int bst::sum() {
    return sum(root);
}
