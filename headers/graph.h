#ifndef GRAPH_H
#define GRAPH_H

#include "dico.h"

struct AdjListNode {    
    int dest;
    int weight;
    struct AdjListNode* next;
};

struct Graph {
    int V;
    struct AdjListNode** array;
};

// Creation du graphe
struct AdjListNode* new_node(int dest, int weight);
struct Graph* create_graph(int V);
void free_graph(struct Graph* graph);
void add_edge(struct Graph* graph, int src, int dest, int weight);
struct Graph* prepare_graph(char *filename, Dictionnary dico);

#endif
