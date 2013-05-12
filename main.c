#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "CHashtable.h"

void print_hashtable(Hashtable* table)
{
    if (table == NULL || table->table == NULL)
    {
        puts("NULL table");
        return;
    }
    size_t i;
    printf("size: %d, count: %d\n", hashtable_size(table), hashtable_elemts_count(table));
    for (i = 0; i < table->size; ++i)
    {
        HashLnkLstNode* p = table->table[i];
        printf("%4d: %x", i, (unsigned int)p);
        if (p == NULL || p->next == NULL)
        {
            puts("");
        }
        else
        {
            p = p->next;
            while(p != NULL)
            {
                printf(" ->%x", (unsigned int)p);
                p = p->next;
            }
            puts("");
        }
    }
}

int main()
{
    const int TABLE_SIZE = 101;
    int i;
    Hashtable* ht_str_str = new_hashtable(TABLE_SIZE);
    print_hashtable(ht_str_str);

    srand(time(NULL));
    for (i = 0; i < TABLE_SIZE << 1; ++i)
    {
        int len = rand() % 100 + 1;
        int key_size = len + 1;
        char* strkey = (char*)malloc(key_size);
        if (strkey == NULL)
        {
            continue;
        }
        strkey[len] = '\0';
        len--;
        while (len >= 0)
        {
            strkey[len] = (char)rand();
            if (strkey[len] == '\0')
            {
                continue;
            }
            len--;
        }
        len = rand() % 100 + 1;
        int val_size = len + 1;
        char* strval = (char*)malloc(val_size);
        if (strval == NULL)
        {
            free(strkey);
            continue;
        }
        strval[len] = '\0';
        len--;
        while (len >= 0)
        {
            strval[len] = (char)rand();
            if (strval[len] == '\0')
            {
                continue;
            }
            len--;
        }
        hashtable_add(ht_str_str, (BYTE*)strkey, key_size, (BYTE*)strval, val_size);
    }

    print_hashtable(ht_str_str);

    /* the function strlen(const char* s) return the length of string s(not include the end char '\0')*/
    hashtable_add(ht_str_str, (BYTE*)"hello world", strlen("hello world") + 1, (BYTE*)"fuck haitai", strlen("hello world") +1);
    printf("find :%d\n", hashtable_contains_key(ht_str_str, (BYTE*)"hello world", strlen("hello world") + 1));
    printf("find :%d\n", hashtable_contains_key(ht_str_str, (BYTE*)"fuck world", strlen("fuck world") + 1));

    char* pstr = (char*)hashtable_getval(ht_str_str, (BYTE*)"hello world", 12);
    printf("get :%s\n", pstr);
    free(pstr);
    print_hashtable(ht_str_str);

    BYTE* p = NULL;
    hashtable_add(ht_str_str, (BYTE*)&p, sizeof(p), (BYTE*)"The key is NULL", 16);

    int* k = NULL;
    pstr = (char*)hashtable_getval(ht_str_str, (BYTE*)&k, sizeof(k));
    printf("'null' key's value :%s\n", pstr);
    free(pstr);
    hashtable_remove(ht_str_str, (BYTE*)&p, sizeof(p));
    hashtable_empty(ht_str_str);
    //print_hashtable(ht_str_str);

    hashtable_dispose(ht_str_str);
    //print_hashtable(ht_str_str);

    getchar();
    return 0;
}
