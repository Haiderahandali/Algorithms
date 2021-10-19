#include "linkedliststr.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

linked_list_str_t* CreateLinkedListStr(char* key)
{
    linked_list_str_t* temp = malloc(sizeof(linked_list_str_t));

    temp->head      = malloc(sizeof(StrNode));
    temp->head->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(temp->head->key, key);

    temp->head->next = NULL;
    temp->head->prev = NULL;

    temp->tail = temp->head;

    return temp;
}

void AddStrNode(linked_list_str_t* ll, StrNode* location, char* key)
{

    if (location == NULL || ll == NULL)
    {
        printf("passing invalid node or uninitalised linked list.... returning\n");
        return;
    }
    StrNode* newNode = malloc(sizeof(StrNode));
    newNode->key     = strdup(key);
    newNode->next    = location->next;
    newNode->prev    = location;

    location->next = newNode;

    if (location == ll->tail)
    {
        ll->tail = newNode;
    }
    else
    {
        newNode->next->prev = newNode;
    }
}

StrNode* FindStrNode(linked_list_str_t* l, char* key)
{
    StrNode* currentStrNode = l->head;
    while (currentStrNode)
    {
        if (strcmp(currentStrNode->key, key) == 0)
        {
            return currentStrNode;
        }
        currentStrNode = currentStrNode->next;
    }
    return currentStrNode;
}

//this assumes there is a unique key, otherwise it will delete the first occurrence
void RemoveStrNodeAtKey(linked_list_str_t* l, char* key)
{
    RemoveStrNode(l, FindStrNode(l, key));
}
void RemoveStrNode(linked_list_str_t* l, StrNode* temp)
{

    if (temp)
    {
        if (temp == l->head)
        {
            l->head = temp->next;
        }

        if (temp == l->tail)
        {
            l->tail = temp->prev;
        }

        if (temp->prev)
        {
            temp->prev->next = temp->next;
        }
        if (temp->next)
        {
            temp->next->prev = temp->prev;
        }

        free(temp->key);
        temp->key = NULL;
        free(temp);
    }
    else
    {
        printf("This is a null node...returning\n");
        return;
    }
}

void AddNodeAtHead(linked_list_str_t* l, char* key)
{
    if (l == NULL)
    {
        printf("the linkedlist is uninitalised.... returning\n");
        return;
    }
    if (l->head == NULL)
    {
        printf("linkedlist head is null, creating a new head\n");
        l->head       = malloc(sizeof(StrNode));
        l->head->prev = NULL;
        l->head->key  = strdup(key);
        l->head->next = NULL;
        l->tail       = l->head;
        return;
    }
    StrNode* currentStrNode   = l->head;
    currentStrNode->prev      = malloc(sizeof(StrNode));
    currentStrNode->prev->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(currentStrNode->prev->key, key);
    currentStrNode->prev->prev = NULL;
    currentStrNode->prev->next = currentStrNode;
    l->head                    = currentStrNode->prev;
}

void AddNodeAtTail(linked_list_str_t* l, char* key)
{
    if (l == NULL)
    {
        printf("the linkedlist is uninitalised.... returning\n");
        return;
    }
    if (l->tail == NULL)
    {
        printf("tail is pointing to a null (empty linkedlist)....creating a new head ");
        l->head       = malloc(sizeof(StrNode));
        l->head->next = NULL;
        l->head->prev = NULL;
        l->head->key  = strdup(key);
        l->tail       = l->head;
        return;
    }

    StrNode* currentStrNode = l->tail;
    currentStrNode->next    = malloc(sizeof(StrNode));

    currentStrNode->next->prev = currentStrNode;
    currentStrNode->next->next = NULL;
    currentStrNode->next->key  = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(currentStrNode->next->key, key);
    l->tail = currentStrNode->next;
}

void PrintLLStr(linked_list_str_t* l)
{
    if (!l)
    {
        printf("The linkedlist is empty....\n");
        return;
    }
    StrNode* currentStrNode = l->head;

    int i = 0;
    printf("Printing String LinkedList....\n");

    while (currentStrNode)
    {
        printf("Item No. %d, key: %s\n", ++i, currentStrNode->key);
        currentStrNode = currentStrNode->next;
    }
}

void PrintLLReverse(linked_list_str_t* l)
{
    if (!l)
    {
        printf("The linkedlist is empty....\n");
        return;
    }
    StrNode* currentStrNode = l->tail;
    int i                   = 0;
    printf("Printing String LinkedList....\n");

    while (currentStrNode)
    {
        printf("Item No. %d, key: %s\n", ++i, currentStrNode->key);
        currentStrNode = currentStrNode->prev;
    }
}

void FreeLinkedListStr(linked_list_str_t** ll_ptr)
{
    if (!(*ll_ptr))
    {
        printf("the linkedlist is already freed\n");
        return;
    }
    linked_list_str_t* ll   = *ll_ptr;
    StrNode* currentStrNode = (*ll_ptr)->head;
    StrNode* nextNode;
    while (currentStrNode)
    {
        nextNode = currentStrNode->next;
        free(currentStrNode->key);
        free(currentStrNode);
        currentStrNode = nextNode;
    }
    free(ll);
    *ll_ptr = NULL;
}