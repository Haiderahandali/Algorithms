#include "stack.h"

void Init(mystack_t* s, unsigned int maxStackSize)
{
    s->stack = malloc(sizeof(char) * maxStackSize);
    s->SP    = 0;
    s->size  = maxStackSize;
}

char Pop(mystack_t* s)
{
    assert(s->SP > 0);
    return s->stack[s->SP--];
}
void Push(mystack_t* s, char value)
{
    assert(s->SP < (s->size - 1));
    s->stack[++s->SP] = value;
}
void Close(mystack_t** st)
{
    mystack_t* s = *st;
    if (s == NULL)
    {
        return;
    }
    free(s->stack);
    s->size = 0;
    s->SP   = 0;
    free(s);
    *st = NULL;
}
mystack_t* CreateStack(unsigned int maxStackSize)
{
    mystack_t* st = malloc(sizeof(mystack_t) * 1);
    Init(st, maxStackSize);
    return st;
}