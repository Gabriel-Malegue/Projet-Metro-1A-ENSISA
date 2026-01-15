#include <stdlib.h>
#include "dijkstra.h"

// Retourne le chemin minimal entre deux points
int* dijkstra(Graph * graph, int src, int dst, int* res, int* taille_chemin)
{
    int size = graph->V;

    int visited[size];
    int dist[size];
    int parent[size];

    for (int i = 0; i < size; i++) {
        visited[i] = 0;
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int c = 0; c < size - 1; c++) {
        int u = -1;
        int u_val = INF;

        for (int i = 0; i < size; i++) {
            if (dist[i] < u_val && !visited[i])
            {
                u = i;
                u_val = dist[i];
            }
        }

        if (u == -1)
            break;
        visited[u] = 1;

        struct AdjListNode *node = graph->array[u];
        while (node) {
            int dest = node->dest;
            if (!visited[dest])
            {
                if (u_val + node->weight < dist[dest])
                {
                    dist[dest] = u_val + node->weight;
                    parent[dest] = u;
                }
            }

            node = node->next;
        }
    }

    *res = dist[dst];

    if (dist[dst] == INF) {
        *taille_chemin = 0;
        return NULL;
    }

    // Creer chemin (a l'envers)
    *taille_chemin = 0;
    int tmp[size];
    int noeud = dst;

    while (noeud != -1) {
        tmp[(*taille_chemin)++] = noeud;
        noeud = parent[noeud];
    }

    // Remettre chemin a l'endroit
    int* chemin = malloc(*taille_chemin * sizeof(int));
    for (int i = 0; i < *taille_chemin; i++) {
        chemin[i] = tmp[*taille_chemin - 1 - i];
    }

    return chemin;
}
