#include "stack.h"

static bool IsMatchingBracket(char c1, char c2)
{
    switch (c1)
    {
        case '(':
        {
            return c2 == ')';
        }
        case '[':
        {
            return c2 == ']';
        }
        case '{':
        {
            return c2 == '}';
        }
        default:
        {
            return false;
        }
    }
}

static bool IsCloseBracket(char c)
{
    return (c == ')' || c == '}' || c == ']');
}

static bool IsOpenBracket(char c)
{
    return (c == '(' || c == '{' || c == '[');
}

bool IsValid(mystack_t* st /*st = stack data strcuture */, char* s)
{

    char c;
    while ((c = *s++))
    {

        if (IsOpenBracket(c))
        {
            Push(st, c);
        }
        else if (IsCloseBracket(c))
        {
            if (st->SP < 1)
            {
                return false;
            }
            else if (!IsMatchingBracket(Pop(st), c))
            {
                return false;
            }
        }
    }

    return st->SP == 0;
}
