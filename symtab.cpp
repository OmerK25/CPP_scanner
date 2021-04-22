#include "symtab.h"

void SymbolTable::initReserved()
{
    ifstream inFile;
    inFile.open("reserved.txt");
    string word;
    if (!inFile)
        cerr << "Unable to open file reserved.txt";
    string text;
    while (inFile >> word)
    {
        if (isalpha(word.at(0)))
        {
            text = word;
        }
        else
        {
            tokenType tt = static_cast<tokenType>(stoi(word));
            insertToken(text, shared_ptr<Token>(new Token(tt, text)));
        }
    }
    inFile.close();
}

shared_ptr<Token> SymbolTable::lookupToken(string text)
{
    if (symMap.count(text) < 1)
    {
        shared_ptr<Token> t1(new Token(ERROR, text));
        return t1;
    }
    else
    {
        map<string, shared_ptr<Token>>::iterator it;
        it = symMap.find(text);
        return it->second;
    }
}

void SymbolTable::insertToken(string text, shared_ptr<Token> tokenp)
{
    symMap.insert({text, tokenp});
}

void SymbolTable::xref()
{
    map<string, shared_ptr<Token>>::iterator it;

    for (it = symMap.begin(); it != symMap.end(); it++)
    {
        if (it->second->getType() == IDENTIFIER)
        {
            cout << it->first << "\t";

            set<int>::iterator itr;
            for (itr = it->second->getLines()->begin(); itr != it->second->getLines()->end(); ++itr)
            {
                cout << *itr << " ";
            }
            cout << endl;
        }
    }
}
