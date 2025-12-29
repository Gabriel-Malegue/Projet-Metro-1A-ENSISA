#include "dijkstra.h"

int dijkstra(Graph * graph, int src, int dst)
{
    int size = graph->V;

    int visited[size];
    int dist[size];

    for (int i = 0; i < size; i++) {
        visited[i] = 0;
        dist[i] = INF;
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
                }
            }

            node = node->next;
        }
    }

    return dist[dst];
}