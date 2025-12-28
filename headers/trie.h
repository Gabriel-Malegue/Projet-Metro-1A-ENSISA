#ifndef TRIE_H
#define TRIE_H

#include "graph.h"

struct degre_station{
    int id;
    int degre;
};

typedef struct degre_station * Deg_Sta;

Deg_Sta degre_entry(struct Graph* graph);

void selection_sort(Deg_Sta arr, int n);
void insertion_sort(Deg_Sta arr, int n);
void quick_sort(Deg_Sta arr, int n);

#endif