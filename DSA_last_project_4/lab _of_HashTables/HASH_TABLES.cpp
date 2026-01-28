#include <iostream>
#include "HASH_TABLES.h"
using namespace std;

HashTable::HashTable(int s) {
    tablesize = s;
    dataTable = new bst[tablesize];
}

int HashTable::hash(int d) {
    return d % tablesize;
}

bool HashTable::isempty() {
    for (int i = 0; i < tablesize; i++) {
        if (!dataTable[i].isempty()) {
            return false;
        }
    }
    return true;
}

void HashTable::add(int d) {
    int index = hash(d);
    dataTable[index].add(d);
}

void HashTable::remove(int d) {
    int index = hash(d);
    dataTable[index].remove(d);
}

void HashTable::search(int d) {
    int index = hash(d);
    if (dataTable[index].search(d)) {
        cout << "value found at index " << index << endl;
    } else {
        cout << "value not found" << endl;
    }
}

void HashTable::print() {
    for (int i = 0; i < tablesize; i++) {
        cout << "index " << i << ": ";
        dataTable[i].print();
        cout << endl;
    }
}

void HashTable::sum() {
    for (int i = 0; i < tablesize; i++) {
        cout << "sum at index " << i << ": ";
        cout << dataTable[i].sum() << endl;
    }
}

HashTable::~HashTable() {
    delete[] dataTable;
}
