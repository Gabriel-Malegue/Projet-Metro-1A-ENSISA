#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define INF 100000

#include "graph.h"



int* dijkstra(Graph * graph, int src, int dst, int* res, int* taille_chemin);
int* dijkstra_voisins(Graph * graph, int src); // Non utilise

#endif