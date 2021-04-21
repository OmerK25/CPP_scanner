#include "token.h"
#include <iostream>

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
    cout << type << "\t" << text << endl;
}

void varToken::add_line(int l)
{
    (*lines).insert(l);
}

shared_ptr<set<int>> varToken::getLines()
{
    return lines;
}