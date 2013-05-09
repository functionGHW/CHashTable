/* Project:     HashTable in C
 * File:        CHashTable.c
 * Coder:       FunctionGHW
 * Version:     0.6
 * Last Change: 2013-5-9
 * Description: Hashtable for C Programs.
 *              Note:   In this implementation, the function hashtable_hash() only
 *                      return a hashcode(sometimes greater than table's size),
 *                      so you should use it like this:
 *                                  hashcode = hashtable_hash() % table_size;
 */

#include "CHashTable.h"
#include <stdlib.h>
#include <string.h>

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

size_t hashtable_elemt_count(const HashTable* table)
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

size_t hashtable_hash(const BYTE* elemt, size_t elemt_size)
{
    size_t ret = 0, seed = 131, i;
    for (i = 0; i < elemt_size; ++i)
    {
        ret = ret * seed + elemt[i];
    }
    return ret;
}
int hashtable_find(const HashTable* table, const BYTE* elemt, size_t elemt_size)
{
    if (table == NULL || elemt == NULL || elemt_size < 1)
    {
        return 0;
    }
    size_t hashcode = hashtable_hash(elemt, elemt_size) % table->size;
    HashLnkLstNode* pNode = table->table[hashcode];
    while (pNode != NULL)
    {
        if (pNode->elemt_size == elemt_size
            && 0 == memcmp(pNode->elemt, elemt, elemt_size))
        {
            return 1;
        }
        pNode = pNode->next;
    }
    return 0;
}
void hashtable_add(HashTable* table, const BYTE* elemt, size_t elemt_size)
{
    if (table == NULL || elemt == NULL || elemt_size < 1)
    {
        return;
    }
    size_t hashcode = hashtable_hash(elemt, elemt_size) % table->size;
    HashLnkLstNode* pNode = table->table[hashcode];
    while (pNode != NULL)
    {
        if (pNode->elemt_size == elemt_size
            && 0 == memcmp(pNode->elemt, elemt, elemt_size))
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
    node->elemt = (BYTE*)malloc(elemt_size);
    if (node->elemt == NULL)
    {
        free(node);
        return;
    }
    memcpy(node->elemt, elemt, elemt_size);
    node->elemt_size = elemt_size;
    node->next = table->table[hashcode];
    table->table[hashcode] = node;
    table->elemts_count++;
}
void hashtable_romove(HashTable* table, const BYTE* elemt, size_t elemt_size)
{
    if (table == NULL || elemt == NULL || elemt_size < 1)
    {
        return;
    }
    size_t hashcode = hashtable_hash(elemt, elemt_size) % table->size;
    HashLnkLstNode* tmp_prev = table->table[hashcode];
    if (tmp_prev->elemt_size == elemt_size
        && 0 == memcmp(tmp_prev->elemt, elemt, elemt_size))
    {
        table->table[hashcode]->next = tmp_prev->next;
        free(tmp_prev->elemt);
        tmp_prev->elemt_size = 0;
        tmp_prev->elemt = NULL;
        free(tmp_prev);
        table->elemts_count--;
        return;
    }
    HashLnkLstNode* tmp = table->table[hashcode]->next;
    while (tmp != NULL)
    {
        if (tmp->elemt_size == elemt_size
            && 0 == memcmp(tmp->elemt, elemt, elemt_size))
        {
            tmp_prev->next = tmp->next;
            free(tmp->elemt);
            tmp->elemt_size = 0;
            tmp->elemt = NULL;
            free(tmp);
            table->elemts_count--;
            return;
        }
        tmp_prev = tmp;
        tmp = tmp->next;
    }
}
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

void hashtable_empty(HashTable* table)
{
    if (table == NULL)
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

            free(p->elemt);
            p->elemt = NULL;
            p->elemt_size = 0;
            free(p);
            table->elemts_count--;
        }
        table->table[i] = NULL;
    }
}
