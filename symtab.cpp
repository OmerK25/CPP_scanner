#include "symtab.h"

void SymbolTable::initReserved()
{

    string line;

    ifstream inFile;
    inFile.open("reserved.txt");
    string name;
    int num;
    while (getline(inFile, line))
    {
        int i = 0;
        while (line.at(i) != ' ')
        {
            name += line.at(i);
            i++;
        }
        while (line.at(i) == ' ')
        {
            i++;
        }
        while (i < line.size())
        {
            num += line.at(i);
            i++;
        }

        shared_ptr<Token> tok(new Token(static_cast<tokenType>(num), name));
        insertToken(name, tok);
    }
}

shared_ptr<Token> SymbolTable::lookupToken(string text)
{
    if (symMap.count(text) < 1)
    {
        shared_ptr<Token> t1(new Token(IDENTIFIER, text));
        insertToken(text, t1);
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
