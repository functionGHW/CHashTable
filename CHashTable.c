/* Project:     HashTable in C
 * File:        CHashTable.c
 * Coder:       FunctionGHW
 * Version:     0.8
 * Last Change: 2013-5-11
 * Description: Hashtable for C Programs.
 *              Note:   In this implementation, the function hashtable_hash() only
 *                      return a hashcode(sometimes greater than table's size),
 *                      so you should use it like this:
 *                                  hashcode = hashtable_hash() % table_size;
 *                      You can use the value NULL as the key, but it's like this:
 *                                  BYTE* p = NULL;
 *                                  BYTE* key = &p; // use this as key.
 *                                  size_t key_size = sizeof(BYTE*);
 *                      If the val is NULL or size of val is 0, the val saved will be a NULL pointer;
 *                      Because this 'generic-types' implementation is actually more like no type,
 *                      I suggest that:
 *                              one hashtable only use one kind of data type for key,
 *                              and one kind of data type for val;
 */

#include "CHashTable.h"
#include <stdlib.h>
#include <string.h>

//Create a new hashtable with size of specified value;
HashTable* new_hashtable(size_t size)
{
    if (size < 1)
    {
        return NULL;
    }
    HashTable* newtable = (HashTable*)malloc(sizeof(HashTable));
    if (newtable == NULL)
    {
        return NULL;
    }
    newtable->table = (HashLnkLstNode**)calloc(size, sizeof(HashLnkLstNode*));
    if (newtable->table == NULL)
    {
        free(newtable);
        return NULL;
    }
    newtable->size = size;
    newtable->elemts_count = 0;
    return newtable;
}

//Get the size of a hashtable;
size_t hashtable_size(const HashTable* table)
{
    if (table == NULL)
    {
        return 0;
    }
    else
    {
        return table->size;
    }
}

//Get the number of elements contained in the hashtable;
size_t hashtable_elemts_count(const HashTable* table)
{
    if (table == NULL)
    {
        return 0;
    }
    else
    {
        return table->elemts_count;
    }
}

//The hash function, this is a BKDRHash;
size_t hashtable_hash(const BYTE* key, size_t key_size)
{
    size_t ret = 0,
           seed = 131, // 31 131 1313 13131 131313 etc..
           i;
    for (i = 0; i < key_size; ++i)
    {
        ret = ret * seed + key[i];
    }
    return ret;
}

//Determines whether the hashtable contains a specific element;
int hashtable_contains_key(const HashTable* table, const BYTE* key, size_t key_size)
{
    if (table == NULL || key == NULL || key_size < 1)
    {
        return 0;
    }
    size_t hashcode = hashtable_hash(key, key_size) % table->size;
    HashLnkLstNode* pNode = table->table[hashcode];
    while (pNode != NULL)
    {
        if (pNode->key_size == key_size
            && 0 == memcmp(pNode->key, key, key_size))
        {
            return 1;
        }
        pNode = pNode->next;
    }
    return 0;
}

//Search the hashtable and return the value with specific key;
//Note: this function just return a memory block without any info about it's type and size;
//      In order to avoid problems, I suggest that
//          one hashtable only use one kind of data type for key, and one kind of data type for val;
//      You can add more info to the names:
//              HashTable tab_str_str = new_hashtable(size);
//              HashTable tab_str_int = new_hashtable(size);
BYTE* hashtable_getval(const HashTable* table, const BYTE* key, size_t key_size)
{
    if (table == NULL || key == NULL || key_size < 1)
    {
        return NULL;
    }
    size_t hashcode = hashtable_hash(key, key_size) % table->size;
    HashLnkLstNode* pNode = table->table[hashcode];
    while (pNode != NULL)
    {
        if (pNode->key_size == key_size
            && 0 == memcmp(pNode->key, key, key_size))
        {
            if (pNode->val == NULL || pNode->val_size == 0)
            {
                return NULL;
            }
            BYTE* tmpval = NULL;
            tmpval = (BYTE*)malloc(pNode->val_size);
            if (tmpval != NULL)
            {
                memcpy(tmpval, pNode->val, pNode->val_size);
            }
            return tmpval;
        }
        pNode = pNode->next;
    }
    return NULL;
}

//Add a new element into the hashtable, if the key has exist in the hashtable, do nothing;
void hashtable_add(HashTable* table, const BYTE* key, size_t key_size, const BYTE* val, size_t val_size)
{
    if (table == NULL || key == NULL || key_size < 1)
    {
        return;
    }
    size_t hashcode = hashtable_hash(key, key_size) % table->size;
    HashLnkLstNode* pNode = table->table[hashcode];
    while (pNode != NULL)
    {
        if (pNode->key_size == key_size
            && 0 == memcmp(pNode->key, key, key_size))
        {
            return;
        }
        pNode = pNode->next;
    }
    HashLnkLstNode* node = (HashLnkLstNode*)malloc(sizeof(HashLnkLstNode));
    if (node == NULL)
    {
        return;
    }
    node->key = (BYTE*)malloc(key_size);
    if (node->key == NULL)
    {
        free(node);
        return;
    }
    if (val == NULL || val_size == 0)
    {
        node->val = NULL;
        node->val_size = 0;
    }
    else
    {
        node->val = (BYTE*)malloc(val_size);
        if (node->val == NULL)
        {
            free(node->key);
            free(node);
            return;
        }
        memcpy(node->val, val, val_size);
        node->val_size = val_size;
    }
    memcpy(node->key, key, key_size);
    node->key_size = key_size;

    node->next = table->table[hashcode];
    table->table[hashcode] = node;
    table->elemts_count++;
}
//Remove a specific element from the hashtable;
void hashtable_remove(HashTable* table, const BYTE* key, size_t key_size)
{
    if (table == NULL || key == NULL || key_size < 1)
    {
        return;
    }
    size_t hashcode = hashtable_hash(key, key_size) % table->size;
    HashLnkLstNode* tmp_prev = table->table[hashcode];
    if (tmp_prev->key_size == key_size
        && 0 == memcmp(tmp_prev->key, key, key_size))
    {
        table->table[hashcode]->next = tmp_prev->next;
        free(tmp_prev->key);
        tmp_prev->key_size = 0;
        tmp_prev->key = NULL;
        free(tmp_prev->val);
        tmp_prev->val_size = 0;
        tmp_prev->val = NULL;
        free(tmp_prev);
        table->table[hashcode] = NULL;
        table->elemts_count--;
        return;
    }
    HashLnkLstNode* tmp = table->table[hashcode]->next;
    while (tmp != NULL)
    {
        if (tmp->key_size == key_size
            && 0 == memcmp(tmp->key, key, key_size))
        {
            tmp_prev->next = tmp->next;
            free(tmp->key);
            tmp->key_size = 0;
            tmp->key = NULL;
            free(tmp->val);
            tmp->val_size = 0;
            free(tmp);
            table->elemts_count--;
            return;
        }
        tmp_prev = tmp;
        tmp = tmp->next;
    }
}

//Dispose the hashtable;
void hashtable_dispose(HashTable* table)
{
    if (table == NULL)
    {
        return;
    }
    hashtable_empty(table);
    free(table->table);
    table->table = NULL;
    table->size = 0;
    free(table);
}

//Romove all elements of the hashtable;
void hashtable_empty(HashTable* table)
{
    if (table == NULL || table->table == NULL || table->elemts_count < 1)
    {
        return;
    }
    size_t i;
    HashLnkLstNode* p;
    HashLnkLstNode* tmp;
    for (i = 0; i < table->size; ++i)
    {
        tmp = table->table[i];
        while (tmp != NULL)
        {
            p = tmp;
            tmp = tmp->next;

            free(p->key);
            p->key = NULL;
            p->key_size = 0;
            free(p->val);
            p->val = NULL;
            p->val_size = 0;
            free(p);
            table->elemts_count--;
        }
        table->table[i] = NULL;
    }
}
