#ifndef GRAPH_H
#define GRAPH_H

struct AdjListNode {    
    int dest;
    int weight;
    struct AdjListNode* next;
};

struct Graph {
    int V;
    struct AdjListNode** array;
};

struct AdjListNode* new_node(int dest, int weight);
struct Graph* create_graph(int V);
void add_edge(struct Graph* graph, int src, int dest, int weight);
struct Graph* prepare_graph(char *filename);

#endif
