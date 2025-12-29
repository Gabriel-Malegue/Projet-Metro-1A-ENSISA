#ifndef GRAPH_H
#define GRAPH_H

#include "dico.h"

struct AdjListNode{    
    int dest;
    int weight;
    struct AdjListNode* next;
};

typedef struct{
    int V;
    struct AdjListNode** array;
    char** station_names; //pour obtenir un nom de station à partir d'un ID
} Graph;

// Creation du graphe
Graph * create_graph(int V);
void free_graph(Graph * graph);
struct AdjListNode * new_node(int dest, int weight);
void add_edge(Graph * graph, int src, int dest, int weight);
Graph * prepare_graph(char * filename, Dictionnary ** dico);

// Fonctions utilite reutilisables
int is_number(char *s);

#endif
