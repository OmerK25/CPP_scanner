#include "scanner.h"

shared_ptr<Token> Scanner::nextToken()
{
    if (!nextChar())
        return nullptr;

    switch (ch)
    {
    case '\n':
    case '\r':
    case ' ':
    {
        return nextToken();
        break;
    }

    case '/':
    {
        if (!nextChar())
            return nullptr;

        if (ch == '/')
        {
            while (nextChar() && ch != '\n')
            {
                //skip the comments.
            }
            if (!inputFile.eof() && ch != '\n')
                inputFile.unget();
        }
        else if (ch == '*')
        {
            char p = 0;
            while (nextChar())
            {
                if (ch == '/' && p == '*')
                    break;
                p = ch;
            }
        }
        return nextToken();
        break;
    }
    case '-':
    {
        nextChar();
        if (ch == '>')
        {
            return shared_ptr<Token>(new Token(PTR_OP, "->"));
        }
        return nextToken();
        break;
    }
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
    case '=':
    case '&':

        return shared_ptr<Token>(new Token(static_cast<tokenType>(ch), string(1, ch)));
        break;

    case '\'':

    {
        string strFromChar;
        if (nextChar())
            strFromChar = string(1, ch);

        if (nextChar() && ch != '\'')
        {
            inputFile.unget();
            return shared_ptr<Token>(new Token(ERROR, strFromChar));
        }
        return shared_ptr<Token>(new Token(CONSTANT, strFromChar));
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
        str.pop_back();
        shared_ptr<Token> t1(new Token(STRING_LITERAL, str));
        return t1;

        break;
    }
    default:
        if (isdigit(ch) || ch == '.')
        {
            string checkIfGoodNum = string(1, ch);
            if (ch == '.')
            {
                nextChar();
                if (isalpha(ch))
                {
                    inputFile.unget();
                    return shared_ptr<Token>(new Token(static_cast<tokenType>('.'), string(1, '.')));
                }
                inputFile.unget();
            }

            while (nextChar() &&
                   (isdigit(ch) || ch == '.' || ch == 'E' || ch == 'e' || ch == '+' || ch == '-'))
            {
                checkIfGoodNum += ch;
            }

            inputFile.unget();

            regex aa("[0-9]");
            regex a("[1-9][0-9]*");
            regex b("[0-9]+[Ee][+-]?[0-9]+");
            regex c("[0-9]*[.][0-9]+([Ee][+-]?[0-9]+)?");
            regex d("[0-9]+[.][0-9]*([Ee][+-]?[0-9]+)?");

            if ((regex_match(checkIfGoodNum, a)) || (regex_match(checkIfGoodNum, b)) || (regex_match(checkIfGoodNum, c)) || (regex_match(checkIfGoodNum, d)) || (regex_match(checkIfGoodNum, aa)))
            {
                return shared_ptr<Token>(new Token(CONSTANT, checkIfGoodNum));
            }
            else
            {
                return shared_ptr<Token>(new Token(ERROR, checkIfGoodNum));
            }
        }

        else if (isalpha(ch))
        {
            string checkIfGoodWord = string(1, ch);
            while (nextChar() &&
                   (isalpha(ch) || isdigit(ch) || ch == '_'))
            {
                checkIfGoodWord += ch;
            }
            if (!inputFile.eof())
                inputFile.unget();
            shared_ptr<Token> t = symTab.lookupToken(checkIfGoodWord);
            if (t != nullptr)
            {
                if (t->getType() == IDENTIFIER)
                    t->add_line(lineno);
                return t;
            }
            else
            {
                shared_ptr<varToken> t1(new varToken(checkIfGoodWord));
                t1->add_line(lineno);
                symTab.insertToken(checkIfGoodWord, t1);
                return t1;
            }
        }
        else
        {
            return nextToken();
        }
        break;
    }
}
