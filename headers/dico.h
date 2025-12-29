#ifndef DICO_H
#define DICO_H

struct dictionnary_entry {
    char* key;
    int value;
    // Collisions chainees
    struct dictionnary_entry * Next; 
};
typedef struct dictionnary_entry * Entry;

typedef struct {
    int size;
    Entry* table; 
} Dictionnary;

unsigned int hash_function(const char * s, int dict_size);
Dictionnary * initialize_dictionnary(int size);
void free_dictionnary(Dictionnary * dict);
void add_pair(Dictionnary * dict, const char* key, int value);
void remove_pair(Dictionnary * dict, const char* key);
int get_value(Dictionnary * dict, const char* key, int* output);
void print_value(Dictionnary * dict, const char* key);

#endif