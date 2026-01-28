#ifndef TREENODE_H
#define TREENODE_H

#include "wordinfo.h"

class treenode
{
public:
    wordinfo data;
    treenode* leftchild;
    treenode* rightchild;
    int nodeheight;

    treenode(wordinfo worddata)
    {
        data = worddata;
        leftchild = NULL;
        rightchild = NULL;
        nodeheight = 1;
    }
};

#endif
