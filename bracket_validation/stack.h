#ifndef STACK_H
#define STACK_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct mystack_t
{
    unsigned int SP;
    unsigned int size;
    char* stack;

} mystack_t;
void Init(mystack_t* s, unsigned int maxStackSize);
void Push(mystack_t* s, char value);
void Close(mystack_t** s);
char Pop(mystack_t* s);
mystack_t* CreateStack(unsigned int maxStackSize);

#endif