#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "BST.h"

class HashTable {
private:
    int tablesize;
    bst* dataTable;

    int hash(int d);

public:
    HashTable(int s);

    bool isempty();
    void add(int d);
    void remove(int d);
    void search(int d);
    void print();
    void sum();

    ~HashTable();
};

#endif
