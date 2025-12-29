#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "dico.h"

#define MAX_LINE 200 // Taille maximale pour une entree

Graph * create_graph(int V)
{
    Graph *graph = malloc(sizeof(Graph));
    graph->V = V;
    graph->array = malloc(V * sizeof(struct AdjListNode *));
    for (int i = 0; i < V; i++)
        graph->array[i] = NULL;
    return graph;
}

void free_graph(Graph * graph)
{
    if (!graph)
        return;

    for (int i = 0; i < graph->V; i++)
    {
        struct AdjListNode * curr = graph->array[i];
        while (curr) {
            struct AdjListNode *next = curr->next;
            free(curr);
            curr = next;
        }
        graph->array[i] = NULL;
    }

    free(graph->array);
    graph->array = NULL;

    for (int i = 0; i < graph->V; i++) // on libère le tableau des noms de stations
        free(graph->station_names[i]);

    free(graph->station_names);

    free(graph);
}

struct AdjListNode * new_node(int dest, int weight)
{
    struct AdjListNode *new_node = malloc(sizeof(struct AdjListNode));
    new_node->dest = dest;
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}

void add_edge(Graph * graph, int src, int dest, int weight)
{
    // Rajoute l'arrete pour le premier sommet
    struct AdjListNode *node = new_node(dest, weight);
    node->next = graph->array[src];
    graph->array[src] = node;
}

// Pour check si le caractère en question est un nombre
int is_number(char *s)
{
    if (s[0] == '\0')
        return 0;

    for (int i = 0; s[i]; i++) {
        if (s[i] < '0' || s[i] > '9')
            return 0;
    }
    return 1;
}

void remove_newline(char *s)
{
    if (!s)
        return;
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
}

// Lis les donnees d'un fichier et cree le graphe correspondant
Graph * prepare_graph(char * filename, Dictionnary * dico)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        fprintf(stderr, "Erreur pas de fichier %s \n", filename);
        return NULL;
    }

    char line[MAX_LINE];
    int station_count = 0;
    int max_id = -1;

    while (fgets(line, sizeof(line), f)) {
        remove_newline(line);

        if (line[0] == '#' || line[0] == '\0')
            continue;

        if (strncmp(line, "STATION", 7) != 0)
            continue;

        char *tok = strtok(line, ";");

        tok = strtok(NULL, ";");
        if (!tok || !is_number(tok))
            continue;

        int id = atoi(tok);
        if (id > max_id)
            max_id = id;

        station_count++;
    }

    dico = initialize_dictionnary(station_count * 2); // 2 fois le nbr de stations pour eviter les collisions
    Graph *graph = create_graph(max_id + 1);
    graph->station_names = calloc(max_id + 1, sizeof(char *));

    rewind(f);

    // Lis et verifie que les stations soient valides
    while (fgets(line, sizeof(line), f)) {
        remove_newline(line);
        if (line[0] == '#' || line[0] == '\0')
            continue;

        if (strncmp(line, "STATION", 7) != 0)
            continue;

        char *tok = strtok(line, ";");
        tok = strtok(NULL, ";");

        if (!tok || !is_number(tok))
        {
            fprintf(stderr, "Probleme Station : ID de %s invalide\n", tok);
            continue;
        }

        int id = atoi(tok);

        tok = strtok(NULL, "\n");
        if (!tok || strlen(tok) == 0)
        {
            fprintf(stderr, "Probleme: Station pas de nom pour l'id %i\n", id);
            continue;
        }

        if (get_value(dico, tok, NULL))
        {
            fprintf(stderr, "Probleme: La station %s existe deja\n", tok);
            continue;
        }

        add_pair(dico, tok, id);
        graph->station_names[id] = strdup(tok);
    }

    // Traverse plusieurs fois au cas ou STATION et EDGE non ordonnes
    rewind(f);

    // Lis et verifie que les edges soient valides
    while (fgets(line, sizeof(line), f)) {
        remove_newline(line);
        if (line[0] == '#' || line[0] == '\0')
            continue;

        if (strncmp(line, "EDGE", 4) != 0)
            continue;

        char *tok = strtok(line, ";");

        tok = strtok(NULL, ";");
        if (!tok || !is_number(tok))
            continue;
        int src = atoi(tok);

        tok = strtok(NULL, ";");
        if (!tok || !is_number(tok))
            continue;
        int dest = atoi(tok);

        tok = strtok(NULL, "\n");
        if (!tok || !is_number(tok))
        {
            fprintf(stderr, "Probleme chemin %i a %i: pas de duree de trajet\n", src, dest);
            continue;
        }
        int weight = atoi(tok);

        if (src < 0 || src > max_id || dest < 0 || dest > max_id)
        {
            fprintf(stderr, "Probleme chemin: station inexistante (%d ou %d)\n", src, dest);
            continue;
        }

        add_edge(graph, src, dest, weight);
    }

    fclose(f);

    for (int i = 0; i <= max_id; i++) {
        if (graph->array[i] == NULL)
        {
            fprintf(stderr, "Probleme: la station %i n'a aucune arrete\n", i);
        }
    }

    return graph;
}
