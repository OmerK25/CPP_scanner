#include "scanner.h"

shared_ptr<Token> Scanner::nextToken()
{
    nextChar();

    if (isdigit(ch))
    {
        string checkIfGoodNum = "";
        checkIfGoodNum = ch;
        nextChar();
        while (isdigit(ch) || ch == '.' || ch == 'E' || ch == 'e')
        {
            checkIfGoodNum.push_back(ch);
        }
        regex a("[0-9]");
        regex b("[1-9][0-9]*");
        regex c("[0-9]+[Ee][+-]?[0-9]+");
        regex d("[0-9]*\\.[0-9]+([Ee][+-]?[0-9]+)?");
        regex e("[0-9]+\\.[0-9]*([Ee][+-]?[0-9]+)?");
        if ((regex_match(checkIfGoodNum, a)) || (regex_match(checkIfGoodNum, b)) || (regex_match(checkIfGoodNum, c)) || (regex_match(checkIfGoodNum, d)) || (regex_match(checkIfGoodNum, e)))
        {
            return shared_ptr<Token>(new Token(CONSTANT, checkIfGoodNum));
        }
        else
        {
            return shared_ptr<Token>(new Token(ERROR, checkIfGoodNum));
        }
    }

    if (isalpha(ch) || ch == '_')
    {
        string checkIfGoodWord;
        checkIfGoodWord += ch;

        while (nextChar() && (isalpha(ch) || isdigit(ch) || ch == '_'))
        {
            checkIfGoodWord += ch;
        }
        if (!inputFile.eof())
            inputFile.unget();

        shared_ptr<Token> t = symTab.lookupToken(checkIfGoodWord);
        if (t->getType() != ERROR)
        {
            if (t->getType() == IDENTIFIER)
            {
                t->add_line(lineno);
            }
            else
            {
                shared_ptr<Token> t1(new Token(t->getType(), t->getText()));
                return t1;
            }
        }
        else
        {
            shared_ptr<Token> t1(new Token(IDENTIFIER, checkIfGoodWord));
            t1->add_line(lineno);
            return t1;
        }
    }

    switch (ch)
    {
    case ' ':
    {
        while (ch == ' ')
        {
            nextChar();
        }
        inputFile.unget();
        nextToken();
        break;
    }

    case '/':
        nextChar();
        if (ch == '/')
        {
            while (ch != '\n')
            {
                nextChar();
            }
        }
        else if (ch == '*')
        {
            nextChar();
            while (ch != '*')
            {
                nextChar();
            }
            if (ch == '/')
            {
                nextChar();
            }
        }
        else
        {
            inputFile.unget();
            return shared_ptr<Token>(new Token(static_cast<tokenType>(ch), string(1, ch)));
        }

        break;

    case ';':
    case '{':
    case '}':
    case ',':
    case ':':
    case '(':
    case ')':
    case '[':
    case ']':
    case '~':
    case '*':
    case '%':
    case '^':
    case '?':
        return shared_ptr<Token>(new Token(static_cast<tokenType>(ch), string(1, ch)));
        break;

    case '\'':
    {
        nextChar();
        char c = ch;
        nextChar();
        if (ch == '\'')
        {
            shared_ptr<Token> t1(new Token(CHAR, string(1, ch)));
        }
        else
        {
            throw "Error";
        }
        break;
    }

    case '\"':
    {
        string str = "";
        nextChar();
        str.push_back(ch);
        while (ch != '\"')
        {
            nextChar();
            str.push_back(ch);
        }
        shared_ptr<Token> t1(new Token(CHAR, str));
        return t1;

        break;
    }
    default:
        break;
    }
}
