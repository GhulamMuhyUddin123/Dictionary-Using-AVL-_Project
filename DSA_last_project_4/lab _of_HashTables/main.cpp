#include <iostream>
#include "HASH_TABLES.h"
using namespace std;

int main() {
    int size;
    cout << "enter hash table size: ";
    cin >> size;

    HashTable h(size);

    int choice, value;

    do {
        cout << "\n1. add\n2. remove\n3. search\n4. print\n5. find sum\n6. exit\n";
        cout << "enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "enter value: ";
            cin >> value;
            h.add(value);
            break;

        case 2:
            cout << "enter value: ";
            cin >> value;
            h.remove(value);
            break;

        case 3:
            cout << "enter value: ";
            cin >> value;
            h.search(value);
            break;

        case 4:
            h.print();
            break;

        case 5:
            h.sum();
            break;
        }
    } while (choice != 6);

    return 0;
}
