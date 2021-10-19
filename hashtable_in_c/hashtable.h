#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYMBOL_SIZE 10
#define RANDOM_SEED 1751379 // can be set to anything really
typedef unsigned long ulong_t;

typedef struct symbol_t
{
    char* key;
    int value;
    struct symbol_t* next;
} symbol_t;

typedef struct symbol_table_t
{
    symbol_t** symbols;
    ulong_t size;
} symbol_table_t;

int Hash(char* key, ulong_t seed);
void PrintSymbols(symbol_t* smybol);
void FreeSymbol(symbol_t* symbol);
symbol_table_t* CreateSymbolTable(ulong_t size);
void DestroySymbolTable(symbol_table_t* table);
void HashtableInsertSymbol(char* key, int value, symbol_table_t* hashtable);
symbol_t* GetSymbolInHashTable(symbol_table_t* hashtable, char* key);
#endif
