#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <fstream>
#include "treenode.h"
using namespace std;

class avltree
{
private:
    treenode* rootnode;

    int getheight(treenode* currentnode);
    int getmaxvalue(int firstvalue, int secondvalue);
    int getbalancefactor(treenode* currentnode);

    treenode* rightrotation(treenode* unbalancednode);
    treenode* leftrotation(treenode* unbalancednode);

    treenode* insertnode(treenode* currentnode, wordinfo newword);
    treenode* findminnode(treenode* currentnode);
    treenode* deletenode(treenode* currentnode, string wordkey);
    treenode* updatenode(treenode* currentnode, string wordkey, string newmeaning);

    void printtreehelper(treenode* currentnode, int space);
    void inorderdisplay(treenode* currentnode);
    void searchwordhelper(treenode* currentnode, string searchkey);
    void findsimilarwordshelper(treenode* currentnode, string prefix);

    void savetofilehelper(treenode* currentnode, ofstream& outputfile);

    string tolowercase(string str);
    bool startswith(string word, string prefix);

public:
    avltree();

    void insert(wordinfo newword);
    void insertFromFile(wordinfo newword);
    void deleteword(string wordkey);
    void updateword(string wordkey, string newmeaning);
    void display();
    void showtree();
    void search(string searchkey);
    void findsimilarwords(string prefix);
    void savetofile();
};

#endif
