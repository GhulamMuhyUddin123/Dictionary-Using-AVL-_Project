#include "avltree.h"

// =======================
// String Helper Functions
// =======================
string avltree::tolowercase(string str)
{
    string result = "";
    for (int i = 0; i < str.length(); i++)
    {
        char c = str[i];
        if (c >= 'A' && c <= 'Z')
        {
            c = c + 32; // Convert uppercase to lowercase
        }
        result += c;
    }
    return result;
}

bool avltree::startswith(string word, string prefix)
{
    if (prefix.length() > word.length())
        return false;

    for (int i = 0; i < prefix.length(); i++)
    {
        char wc = word[i];
        char pc = prefix[i];

        // Convert both to lowercase for comparison
        if (wc >= 'A' && wc <= 'Z') wc = wc + 32;
        if (pc >= 'A' && pc <= 'Z') pc = pc + 32;

        if (wc != pc)
            return false;
    }
    return true;
}

// =======================
// Constructor
// =======================
avltree::avltree()
{
    rootnode = NULL;
}

// =======================
// AVL Basic Functions
// =======================
int avltree::getheight(treenode* currentnode)
{
    if (currentnode == NULL)
    {
        return 0;
    }
    return currentnode->nodeheight;
}

int avltree::getmaxvalue(int firstvalue, int secondvalue)
{
    if (firstvalue > secondvalue)
    {
        return firstvalue;
    }
    else
    {
        return secondvalue;
    }
}

int avltree::getbalancefactor(treenode* currentnode)
{
    if (currentnode == NULL)
    {
        return 0;
    }
    return getheight(currentnode->leftchild) - getheight(currentnode->rightchild);
}

// =======================
// Rotations
// =======================
treenode* avltree::rightrotation(treenode* unbalancednode)
{
    treenode* leftchildnode = unbalancednode->leftchild;
    treenode* rightsubtree = leftchildnode->rightchild;

    leftchildnode->rightchild = unbalancednode;
    unbalancednode->leftchild = rightsubtree;

    unbalancednode->nodeheight = getmaxvalue(
        getheight(unbalancednode->leftchild),
        getheight(unbalancednode->rightchild)) + 1;

    leftchildnode->nodeheight = getmaxvalue(
        getheight(leftchildnode->leftchild),
        getheight(leftchildnode->rightchild)) + 1;

    return leftchildnode;
}

treenode* avltree::leftrotation(treenode* unbalancednode)
{
    treenode* rightchildnode = unbalancednode->rightchild;
    treenode* leftsubtree = rightchildnode->leftchild;

    rightchildnode->leftchild = unbalancednode;
    unbalancednode->rightchild = leftsubtree;

    unbalancednode->nodeheight = getmaxvalue(
        getheight(unbalancednode->leftchild),
        getheight(unbalancednode->rightchild)) + 1;

    rightchildnode->nodeheight = getmaxvalue(
        getheight(rightchildnode->leftchild),
        getheight(rightchildnode->rightchild)) + 1;

    return rightchildnode;
}

// =======================
// INSERT FUNCTION (Case-insensitive) - FIXED VERSION
// =======================
treenode* avltree::insertnode(treenode* currentnode, wordinfo newword)
{
    if (currentnode == NULL)
    {
        return new treenode(newword);
    }

    // Case-insensitive comparison
    string newwordLower = tolowercase(newword.word);
    string currentLower = tolowercase(currentnode->data.word);

    if (newwordLower < currentLower)
    {
        currentnode->leftchild = insertnode(currentnode->leftchild, newword);
    }
    else if (newwordLower > currentLower)
    {
        currentnode->rightchild = insertnode(currentnode->rightchild, newword);
    }
    else
    {
        // FIX: Word already exists - UPDATE the meaning instead of just returning
        currentnode->data.meaning = newword.meaning;
        // Don't print message here for file loading
        return currentnode;
    }

    // Update height
    currentnode->nodeheight = getmaxvalue(
        getheight(currentnode->leftchild),
        getheight(currentnode->rightchild)) + 1;

    // Get balance factor
    int balancefactor = getbalancefactor(currentnode);

    // Left Left Case
    if (balancefactor > 1 && newwordLower < tolowercase(currentnode->leftchild->data.word))
        return rightrotation(currentnode);

    // Right Right Case
    if (balancefactor < -1 && newwordLower > tolowercase(currentnode->rightchild->data.word))
        return leftrotation(currentnode);

    // Left Right Case
    if (balancefactor > 1 && newwordLower > tolowercase(currentnode->leftchild->data.word))
    {
        currentnode->leftchild = leftrotation(currentnode->leftchild);
        return rightrotation(currentnode);
    }

    // Right Left Case
    if (balancefactor < -1 && newwordLower < tolowercase(currentnode->rightchild->data.word))
    {
        currentnode->rightchild = rightrotation(currentnode->rightchild);
        return leftrotation(currentnode);
    }

    return currentnode;
}
// =======================
// FIND MINIMUM NODE
// =======================
treenode* avltree::findminnode(treenode* currentnode)
{
    treenode* temp = currentnode;
    while (temp && temp->leftchild != NULL)
    {
        temp = temp->leftchild;
    }
    return temp;
}

// =======================
// DELETE FUNCTION (Case-insensitive)
// =======================
treenode* avltree::deletenode(treenode* currentnode, string wordkey)
{
    if (currentnode == NULL)
    {
        return currentnode;
    }

    // Case-insensitive comparison
    string wordkeyLower = tolowercase(wordkey);
    string currentLower = tolowercase(currentnode->data.word);

    if (wordkeyLower < currentLower)
    {
        currentnode->leftchild = deletenode(currentnode->leftchild, wordkey);
    }
    else if (wordkeyLower > currentLower)
    {
        currentnode->rightchild = deletenode(currentnode->rightchild, wordkey);
    }
    else
    {
        // Node found
        // Case 1: No child or one child
        if ((currentnode->leftchild == NULL) || (currentnode->rightchild == NULL))
        {
            treenode* temp = currentnode->leftchild ?
                           currentnode->leftchild :
                           currentnode->rightchild;

            // No child case
            if (temp == NULL)
            {
                temp = currentnode;
                currentnode = NULL;
            }
            else // One child case
            {
                *currentnode = *temp; // Copy the contents
            }
            delete temp;
        }
        else
        {
            // Case 2: Two children
            treenode* temp = findminnode(currentnode->rightchild);
            currentnode->data.word = temp->data.word;
            currentnode->data.meaning = temp->data.meaning;
            currentnode->rightchild = deletenode(currentnode->rightchild, temp->data.word);
        }
    }

    // If tree had only one node
    if (currentnode == NULL)
    {
        return currentnode;
    }

    // Update height
    currentnode->nodeheight = getmaxvalue(
        getheight(currentnode->leftchild),
        getheight(currentnode->rightchild)) + 1;

    // Get balance factor
    int balancefactor = getbalancefactor(currentnode);

    // Balance the tree
    // Left Left Case
    if (balancefactor > 1 && getbalancefactor(currentnode->leftchild) >= 0)
        return rightrotation(currentnode);

    // Left Right Case
    if (balancefactor > 1 && getbalancefactor(currentnode->leftchild) < 0)
    {
        currentnode->leftchild = leftrotation(currentnode->leftchild);
        return rightrotation(currentnode);
    }

    // Right Right Case
    if (balancefactor < -1 && getbalancefactor(currentnode->rightchild) <= 0)
        return leftrotation(currentnode);

    // Right Left Case
    if (balancefactor < -1 && getbalancefactor(currentnode->rightchild) > 0)
    {
        currentnode->rightchild = rightrotation(currentnode->rightchild);
        return leftrotation(currentnode);
    }

    return currentnode;
}

// =======================
// UPDATE FUNCTION (Case-insensitive)
// =======================
treenode* avltree::updatenode(treenode* currentnode, string wordkey, string newmeaning)
{
    if (currentnode == NULL)
    {
        return currentnode;
    }

    // Case-insensitive comparison
    string wordkeyLower = tolowercase(wordkey);
    string currentLower = tolowercase(currentnode->data.word);

    if (wordkeyLower < currentLower)
    {
        currentnode->leftchild = updatenode(currentnode->leftchild, wordkey, newmeaning);
    }
    else if (wordkeyLower > currentLower)
    {
        currentnode->rightchild = updatenode(currentnode->rightchild, wordkey, newmeaning);
    }
    else
    {
        // Word found - update meaning
        currentnode->data.meaning = newmeaning;
    }

    return currentnode;
}

// =======================
// DISPLAY FUNCTIONS
// =======================
void avltree::printtreehelper(treenode* currentnode, int space)
{
    if (currentnode == NULL)
        return;

    space += 5;

    // Process right child first
    printtreehelper(currentnode->rightchild, space);

    cout << endl;
    for (int i = 5; i < space; i++)
        cout << " ";
    cout << currentnode->data.word << " (h=" << currentnode->nodeheight << ")" << endl;

    // Process left child
    printtreehelper(currentnode->leftchild, space);
}

void avltree::inorderdisplay(treenode* currentnode)
{
    if (currentnode == NULL)
    {
        return;
    }

    inorderdisplay(currentnode->leftchild);

    cout << currentnode->data.word;
    cout << " : ";
    cout << currentnode->data.meaning;
    cout << endl;

    inorderdisplay(currentnode->rightchild);
}

// =======================
// SEARCH FUNCTIONS (Case-insensitive)
// =======================
void avltree::searchwordhelper(treenode* currentnode, string searchkey)
{
    if (currentnode == NULL)
    {
        cout << "Word not found!" << endl;
        return;
    }

    // Case-insensitive comparison
    string searchLower = tolowercase(searchkey);
    string currentLower = tolowercase(currentnode->data.word);

    if (searchLower == currentLower)
    {
        cout << "Word: " << currentnode->data.word << endl;
        cout << "Meaning: " << currentnode->data.meaning << endl;
        return;
    }

    if (searchLower < currentLower)
    {
        searchwordhelper(currentnode->leftchild, searchkey);
    }
    else
    {
        searchwordhelper(currentnode->rightchild, searchkey);
    }
}

void avltree::findsimilarwordshelper(treenode* currentnode, string prefix)
{
    if (currentnode == NULL)
    {
        return;
    }

    // Check current node
    if (startswith(currentnode->data.word, prefix))
    {
        cout << " - " << currentnode->data.word << endl;
    }

    // Check left and right subtrees
    findsimilarwordshelper(currentnode->leftchild, prefix);
    findsimilarwordshelper(currentnode->rightchild, prefix);
}

// =======================
// FILE OPERATIONS
// =======================
void avltree::savetofilehelper(treenode* currentnode, ofstream& outputfile)
{
    if (currentnode == NULL)
    {
        return;
    }

    savetofilehelper(currentnode->leftchild, outputfile);

    outputfile << currentnode->data.word;
    outputfile << ",";
    outputfile << currentnode->data.meaning;
    outputfile << endl;

    savetofilehelper(currentnode->rightchild, outputfile);
}

// =======================
// PUBLIC METHODS
// =======================
void avltree::insert(wordinfo newword)
{
    // Check if word already exists
    bool exists = false;
    treenode* temp = rootnode;
    string newwordLower = tolowercase(newword.word);

    while (temp != NULL)
    {
        string currentLower = tolowercase(temp->data.word);

        if (newwordLower == currentLower)
        {
            exists = true;
            break;
        }
        else if (newwordLower < currentLower)
            temp = temp->leftchild;
        else
            temp = temp->rightchild;
    }

    rootnode = insertnode(rootnode, newword);

    if (exists)
        cout << "Word '" << newword.word << "' meaning updated successfully!" << endl;
    else
        cout << "Word '" << newword.word << "' inserted successfully!" << endl;
}

void avltree::deleteword(string wordkey)
{
    // First check if word exists
    treenode* temp = rootnode;
    bool found = false;

    string wordkeyLower = tolowercase(wordkey);

    while (temp != NULL)
    {
        string currentLower = tolowercase(temp->data.word);

        if (wordkeyLower == currentLower)
        {
            found = true;
            break;
        }
        else if (wordkeyLower < currentLower)
            temp = temp->leftchild;
        else
            temp = temp->rightchild;
    }

    if (!found)
    {
        cout << "Word '" << wordkey << "' not found. Cannot delete." << endl;
        return;
    }

    rootnode = deletenode(rootnode, wordkey);
    cout << "Word '" << wordkey << "' deleted successfully!" << endl;
}

void avltree::updateword(string wordkey, string newmeaning)
{
    // First check if word exists
    treenode* temp = rootnode;
    bool found = false;

    string wordkeyLower = tolowercase(wordkey);

    while (temp != NULL)
    {
        string currentLower = tolowercase(temp->data.word);

        if (wordkeyLower == currentLower)
        {
            found = true;
            break;
        }
        else if (wordkeyLower < currentLower)
            temp = temp->leftchild;
        else
            temp = temp->rightchild;
    }

    if (!found)
    {
        cout << "Word '" << wordkey << "' not found. Cannot update." << endl;
        return;
    }

    rootnode = updatenode(rootnode, wordkey, newmeaning);
    cout << "Word '" << wordkey << "' updated successfully!" << endl;
}

void avltree::display()
{
    if (rootnode == NULL)
    {
        cout << "Dictionary is empty!" << endl;
        return;
    }
    cout << "\n=== Dictionary Contents ===" << endl;
    inorderdisplay(rootnode);
}

void avltree::showtree()
{
    if (rootnode == NULL)
    {
        cout << "Tree is empty!" << endl;
        return;
    }
    cout << "\n=== Tree Structure (Horizontal) ===" << endl;
    cout << "(Right is up, Left is down)" << endl;
    printtreehelper(rootnode, 0);
    cout << endl;
}

void avltree::search(string searchkey)
{
    if (rootnode == NULL)
    {
        cout << "Dictionary is empty!" << endl;
        return;
    }

    cout << "\nSearching for: " << searchkey << endl;
    searchwordhelper(rootnode, searchkey);
}

void avltree::findsimilarwords(string prefix)
{
    if (rootnode == NULL)
    {
        cout << "Dictionary is empty!" << endl;
        return;
    }

    cout << "\nWords starting with '" << prefix << "':" << endl;
    findsimilarwordshelper(rootnode, prefix);
}

void avltree::savetofile()
{
    ofstream outputfile;
    outputfile.open("dictionary.txt");

    if (!outputfile)
    {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    savetofilehelper(rootnode, outputfile);
    outputfile.close();
    cout << "Dictionary saved to file successfully!" << endl;
}
// =======================
// INSERT FOR FILE LOADING (No duplicate check)
// =======================

void avltree::insertFromFile(wordinfo newword)
{
    rootnode = insertnode(rootnode, newword);
}
