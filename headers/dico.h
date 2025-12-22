#ifndef DICO_H
#define DICO_H

#define MAX_SIZE 2048 // Will make it dynamic in the future

struct dictionnary_entry {
    char* key;
    int value;
    // Chained collisions
    struct dictionnary_entry * Next; 
};
typedef struct dictionnary_entry * Entry;

struct dictionnary {
    Entry table[MAX_SIZE];
};
typedef struct dictionnary * Dictionnary;

unsigned int hash_function(const char * s);
Dictionnary initialize_dictionnary();
void free_dictionnary(Dictionnary dict);
void add_pair(Dictionnary dict, const char* key, int value);
void remove_pair(Dictionnary dict, const char* key);
int get_value(Dictionnary dict, const char* key, int* output);
void print_value(Dictionnary dict, const char* key);

#endif