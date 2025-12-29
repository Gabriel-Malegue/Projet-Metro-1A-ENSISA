#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

#define INF 100000

int dijkstra(Graph * graph, int src, int dst);
int* dijkstra_voisins(Graph * graph, int src);

#endif