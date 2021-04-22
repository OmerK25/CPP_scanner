#include "token.h"
#include <iostream>
#include "tokenstrings.h"

using namespace std;

tokenType Token::getType()
{
    return type;
}

string Token::getText()
{
    return text;
}

void Token::printToken()
{
    if (getType() >= 258)
    {
        cout << tokenStrings[getType() - 258] << "\t" << getText() << endl;
    }
    else
    {
        cout << getText() << "\t" << getText() << endl;
    }
}

void varToken::add_line(int l)
{
    (*lines).insert(l);
}

shared_ptr<set<int>> varToken::getLines()
{
    return lines;
}