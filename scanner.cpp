#include "scanner.h"

shared_ptr<Token> Scanner::nextToken()
{
    while (nextChar())
    {
        switch (ch)
        {
        case ' ':
            while (ch == ' ')
            {
                inputFile.get(ch);
            }
            break;

        case '/':
            inputFile.get(ch);
            if (ch == '/')
            {
                while (ch != '\n')
                {
                    inputFile.get(ch);
                }
                inputFile.get(ch);
            }
            break;

            switch (ch)
            {
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
            case '/':
                return shared_ptr<Token>(new Token(static_cast<tokenType>(ch), string(1, ch)));
                break;

            case '\\d':
                string checkIfGoodNum;
                checkIfGoodNum = ch;
                inputFile.get(ch);
                while (ch == '\\d' || ch == '.' || ch == 'E' || ch == 'e')
                {
                    checkIfGoodNum.push_back(ch);
                }

                if (checkIfGoodNum)
                    break;
            default:
                break;
            }
        }
    }