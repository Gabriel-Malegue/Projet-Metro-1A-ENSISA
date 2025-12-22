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

struct AdjListNode* newAdjListNode(int dest, int weight);
struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int dest, int weight);
struct Graph* PrepareGraph(char *filename);

#endif
