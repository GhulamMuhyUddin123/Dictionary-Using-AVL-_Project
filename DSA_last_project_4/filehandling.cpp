#include "filehandling.h"
#include <fstream>
#include <iostream>
using namespace std;

void loaddictionaryfile(avltree& dictionarytree)
{
    ifstream inputfile("dictionary.txt");

    if (!inputfile)
    {
        cout << "No dictionary file found. Starting fresh." << endl;
        return;
    }

    string line;
    int count = 0;

    while (getline(inputfile, line))
    {
        int pos = line.find(',');

        if (pos != -1)
        {
            wordinfo temp;
            temp.word = line.substr(0, pos);
            temp.meaning = line.substr(pos + 1);

            dictionarytree.insertFromFile(temp);
            count++;
        }
    }

    inputfile.close();
    cout << "Loaded " << count << " words from file." << endl;
}
