/* Project:     Hashtable in C
 * File:        CHashtable.h
 * Coder:       FunctionGHW
 * Version:     1.0
 * Last Change: 2013-5-12
 * Description: Hashtable for C Programs, using chaining to deal with collisions.
 *              This is the header file.
 */

#ifndef CHASHTABLE_H_BDD25836_8BE8_4079_B2E6_9CDF3EB0CD20
#define CHASHTABLE_H_BDD25836_8BE8_4079_B2E6_9CDF3EB0CD20

#include <stddef.h>

#ifndef TYPEDEF_BYTE
#define TYPEDEF_BYTE
typedef unsigned char BYTE;
#endif

typedef struct HashLnkLstNode HashLnkLstNode;
typedef struct Hashtable Hashtable;

struct HashLnkLstNode
{
    BYTE* key;
    BYTE* val;
    size_t key_size;
    size_t val_size;
    HashLnkLstNode* next;
};

struct Hashtable
{
    size_t size; //This is the size of the table,
                 //which contains all header of the single-linked list;
    size_t elemts_count; // The count can be greater than size;

    HashLnkLstNode** table;
};

//Create a new hashtable with size of specified value;
Hashtable* new_hashtable(size_t size);
//Get the size of a hashtable;
size_t hashtable_size(const Hashtable* table);
//Get the number of elements contained in the hashtable;
size_t hashtable_elemts_count(const Hashtable* table);
//The hash function;
size_t hashtable_hash(const BYTE* key, size_t key_size);
//Determines whether the hashtable contains a specific element;
int hashtable_contains_key(const Hashtable* table, const BYTE* key, size_t key_size);
//Search the hashtable and return the value with specific key;
BYTE* hashtable_getval(const Hashtable* table, const BYTE* key, size_t key_size);
//Add a new element into the hashtable, if the key has exist in the hashtable, do nothing;
void hashtable_add(Hashtable* table,
                   const BYTE* key,
                   size_t key_size,
                   const BYTE* val,
                   size_t val_size);
//Remove a specific element from the hashtable;
void hashtable_remove(Hashtable* table, const BYTE* key, size_t key_size);
//Dispose the hashtable;
void hashtable_dispose(Hashtable* table);
//Romove all elements of the hashtable;
void hashtable_empty(Hashtable* table);

#endif // CHASHTABLE_H_BDD25836_8BE8_4079_B2E6_9CDF3EB0CD20
