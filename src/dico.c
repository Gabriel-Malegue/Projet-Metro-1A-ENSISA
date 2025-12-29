#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dico.h"

unsigned int hash_function(const char *s, int dict_size)
{
    unsigned int hash = 2166136261;
    const unsigned int fnv_prime = 16777619;
    for (const char *c = s; *c; c++) {
        hash ^= *c;
        hash *= fnv_prime;
    }
    return hash % dict_size;
}

Dictionnary initialize_dictionnary(int size)
{
    Dictionnary new_dictionnary = malloc(sizeof(struct dictionnary));
    new_dictionnary->size = size;
    new_dictionnary->table = malloc(size * sizeof(Entry));
    for (int i = 0; i < size; i++)
        new_dictionnary->table[i] = NULL;

    return new_dictionnary;
}

void free_dictionnary(Dictionnary dict)
{
    if (!dict)
        return;

    for (int i = 0; i < dict->size; i++) {
        Entry curr = dict->table[i];
        while (curr)
        {
            Entry next = curr->Next;
            free(curr->key); // strdup'd the key so must free
            free(curr);
            curr = next;
        }
        dict->table[i] = NULL;
    }

    free(dict->table);
    free(dict);
}

void add_pair(Dictionnary dict, const char *key, int value)
{
    int slot = hash_function(key, dict->size);
    Entry curr = dict->table[slot];
    while (curr) {
        if (strcmp(curr->key, key) == 0)
        {
            curr->value = value;
            return;
        }
        curr = curr->Next;
    }

    Entry new_entry = malloc(sizeof(struct dictionnary_entry));
    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->Next = dict->table[slot];

    dict->table[slot] = new_entry;
}

void remove_pair(Dictionnary dict, const char *key)
{
    int slot = hash_function(key, dict->size);
    Entry curr = dict->table[slot];
    Entry prev = NULL;
    while (curr) {
        if (strcmp(curr->key, key) == 0)
        {
            if (prev == NULL)
            {
                dict->table[slot] = curr->Next;
            }
            else
            {
                prev->Next = curr->Next;
            }
            free(curr->key);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->Next;
    }

    printf("Entry does not exist in specified dictionnary\n");
}

int get_value(Dictionnary dict, const char *key, int *output)
{
    int slot = hash_function(key, dict->size);
    Entry curr = dict->table[slot];

    while (curr) {
        if (strcmp(curr->key, key) == 0)
        {
            if (output)
                *output = curr->value;
            return 1;
        }
        curr = curr->Next;
    }

    return 0;
}

void print_value(Dictionnary dict, const char *key)
{
    int output;
    int value = get_value(dict, key, &output);
    if (value)
    {
        printf("%s quantity: %i\n", key, output);
    }
}