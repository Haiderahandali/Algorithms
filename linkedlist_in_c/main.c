#include "linkedliststr.h"
#include <stdio.h>

// --------------- main.c is just for testing ---------//

int main()
{

    //-------- Normal Case of multiple values --------//
    linked_list_str_t* ll = CreateLinkedListStr("Key 1");
    AddStrNode(ll, ll->tail, "Key 2");
    AddStrNode(ll, ll->tail, "Key 6");
    AddStrNode(ll, ll->tail, "Key 11");
    AddStrNode(ll, ll->tail, "Key 5");
    AddStrNode(ll, ll->tail, "Key 10");
    PrintLLStr(ll);

    char* x = "Key 6";

    RemoveStrNodeAtKey(ll, x);

    StrNode* xNode = FindStrNode(ll, x);
    if (xNode)
    {
        printf("key: %s was found!\n", x);
    }
    else
    {
        printf("key: %s was not found!\n", x);
    }

    RemoveStrNodeAtKey(ll, "Key 2");
    RemoveStrNodeAtKey(ll, "Key 11");
    RemoveStrNodeAtKey(ll, "Key 5");
    RemoveStrNodeAtKey(ll, "Key 10");

    //--------------- Edge case of a single element ------------------//
    PrintLLReverse(ll);
    RemoveStrNodeAtKey(ll, ll->head->key);
    AddNodeAtTail(ll, "I am at tail");
    AddNodeAtHead(ll, "I am at head");
    PrintLLReverse(ll);
    PrintLLStr(ll);

    FreeLinkedListStr(&ll);

    PrintLLReverse(ll);

    //---------- Edge case of no elements ------------//
    FreeLinkedListStr(&ll);
    PrintLLReverse(ll);
    PrintLLStr(ll);
}