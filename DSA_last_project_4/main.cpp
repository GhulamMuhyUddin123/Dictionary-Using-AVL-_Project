#include <iostream>
#include <string>
#include "avltree.h"
#include "filehandling.h"
using namespace std;

// =======================
// ADMIN MENU
// =======================
void adminmenu(avltree& dictionary)
{
    int choice;
    string word;
    string meaning;

    do
    {
        cout << "\n====== ADMIN MENU ======" << endl;
        cout << "1. add word" << endl;
        cout << "2. delete word" << endl;
        cout << "3. search word" << endl;
        cout << "4. search similar words" << endl;
        cout << "5. see tree structure" << endl;
        cout << "6. display all words" << endl;
        cout << "7. save dictionary" << endl;
        cout << "8. exit admin menu" << endl;
        cout << "enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            cout << "enter word: ";
            getline(cin, word);
            cout << "enter meaning: ";
            getline(cin, meaning);

            wordinfo newword;
            newword.word = word;
            newword.meaning = meaning;

            dictionary.insert(newword);
        }
        else if (choice == 2)
        {
            cout << "enter word to delete: ";
            getline(cin, word);
            dictionary.deleteword(word);
        }
        else if (choice == 3)
        {
            cout << "enter word to search: ";
            getline(cin, word);
            dictionary.search(word);
        }
        else if (choice == 4)
        {
            cout << "enter prefix: ";
            getline(cin, word);
            dictionary.findsimilarwords(word);
        }
        else if (choice == 5)
        {
            dictionary.showtree();
        }
        else if (choice == 6)
        {
            dictionary.display();
        }
        else if (choice == 7)
        {
            dictionary.savetofile();
        }
        else if (choice == 8)
        {
            cout << "exiting admin menu..." << endl;
        }
        else
        {
            cout << "invalid choice!" << endl;
        }

    } while (choice != 8);
}

// =======================
// USER MENU
// =======================
void usermenu(avltree& dictionary)
{
    int choice;
    string word;

    do
    {
        cout << "\n====== USER MENU ======" << endl;
        cout << "1. search word" << endl;
        cout << "2. search similar words" << endl;
        cout << "3. display all words" << endl;
        cout << "4. exit user menu" << endl;
        cout << "enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            cout << "enter word to search: ";
            getline(cin, word);
            dictionary.search(word);
        }
        else if (choice == 2)
        {
            cout << "enter prefix: ";
            getline(cin, word);
            dictionary.findsimilarwords(word);
        }
        else if (choice == 3)
        {
            dictionary.display();
        }
        else if (choice == 4)
        {
            cout << "exiting user menu..." << endl;
        }
        else
        {
            cout << "invalid choice!" << endl;
        }

    } while (choice != 4);
}

// =======================
// MAIN FUNCTION
// =======================
int main()
{
    avltree dictionary;

    // load dictionary from file
    loaddictionaryfile(dictionary);

    int role;
    string password;

    cout << "\n====== DICTIONARY SYSTEM ======" << endl;
    cout << "1. admin" << endl;
    cout << "2. user" << endl;
    cout << "enter role: ";
    cin >> role;
    cin.ignore();

    if (role == 1)
    {
        cout << "enter admin password: ";
        getline(cin, password);

        if (password == "admin123")
        {
            adminmenu(dictionary);
        }
        else
        {
            cout << "wrong password! switching to user mode." << endl;
            usermenu(dictionary);
        }
    }
    else if (role == 2)
    {
        usermenu(dictionary);
    }
    else
    {
        cout << "invalid role selected!" << endl;
    }

    // save before exit
    dictionary.savetofile();

    cout << "\nthank you for using dictionary system." << endl;
    return 0;
}
