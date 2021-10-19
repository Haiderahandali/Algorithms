#ifndef LINKED_LIST_STR_H
#define LINKED_LIST_STR_H

typedef struct StrNode
{
    char* key;
    struct StrNode* next;
    struct StrNode* prev;
} StrNode;

typedef struct linked_list_str_t
{
    StrNode* head;
    StrNode* tail;
} linked_list_str_t;

linked_list_str_t* CreateLinkedListStr(char* key);
void FreeLinkedListStr(linked_list_str_t** linkedlistStr);
void AddStrNode(linked_list_str_t* l, StrNode* location, char* key);
void PrintLLStr(linked_list_str_t* l);
void PrintLLReverse(linked_list_str_t* l);

void RemoveStrNodeAtKey(linked_list_str_t* l, char* key);
void RemoveStrNode(linked_list_str_t* l, StrNode* temp);

void AddNodeAtTail(linked_list_str_t* l, char* key);
void AddNodeAtHead(linked_list_str_t* l, char* key);
StrNode* FindStrNode(linked_list_str_t* l, char* key);

#endif