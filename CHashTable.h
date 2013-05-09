/* Project:     HashTable in C
 * File:        CHashTable.h
 * Coder:       FunctionGHW
 * Version:     0.6
 * Last Change: 2013-5-9
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
typedef struct HashTable HashTable;

struct HashLnkLstNode
{
    BYTE* elemt;
    size_t elemt_size;
    HashLnkLstNode* next;
};

struct HashTable
{
    size_t size;
    size_t elemts_count;

    HashLnkLstNode** table;
};

HashTable* new_hashtable(size_t size);
size_t hashtable_size(const HashTable* table);
size_t hashtable_elemt_count(const HashTable* table);
size_t hashtable_hash(const BYTE* elemt, size_t elemt_size);
int hashtable_find(const HashTable* table, const BYTE* elemt, size_t elemt_size);
void hashtable_add(HashTable* table, const BYTE* elemt, size_t elemt_size);
void hashtable_romove(HashTable* table, const BYTE* elemt, size_t elemt_size);
void hashtable_dispose(HashTable* table);
void hashtable_empty(HashTable* table);

#endif // CHASHTABLE_H_BDD25836_8BE8_4079_B2E6_9CDF3EB0CD20
