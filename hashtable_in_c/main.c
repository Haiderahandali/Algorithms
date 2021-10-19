//this is just for testing, and not really required but just for testing, I am finding john and change its value.

#ifndef SYMBOL_SIZE
#define SYMBOL_SIZE 10
#endif

#include "hashtable.h"

int main()
{
    symbol_table_t* hashtable = CreateSymbolTable(SYMBOL_SIZE);

    HashtableInsertSymbol("Ali", 20, hashtable);
    HashtableInsertSymbol("Alia", 15, hashtable);
    HashtableInsertSymbol("Alib", 25, hashtable);
    HashtableInsertSymbol("Alic", 20, hashtable);
    HashtableInsertSymbol("Alid", 20, hashtable);
    HashtableInsertSymbol("John", 12, hashtable);
    HashtableInsertSymbol("Smith", 25, hashtable);
    HashtableInsertSymbol("Mom", 1, hashtable);
    HashtableInsertSymbol("Dad", 10, hashtable);

    char* key = "John";

    symbol_t* symbol = GetSymbolInHashTable(hashtable, key);
    if (symbol != NULL)
    {
        printf("key: %s, was found and it's value: %d\n", symbol->key, symbol->value);
    }
    HashtableInsertSymbol("John", 18, hashtable); //should update john's value tp 18
    symbol = GetSymbolInHashTable(hashtable, key);
    if (symbol != NULL)
    {
        printf("key: %s, value = %d\n", symbol->key, symbol->value);
    }
    DestroySymbolTable(hashtable);
}
