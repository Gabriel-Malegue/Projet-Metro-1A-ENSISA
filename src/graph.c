#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

#define MAX_LINE 256 // Taille maximale pour une entree


struct AdjListNode* new_node(int dest, int weight) {
    struct AdjListNode* new_node = malloc(sizeof(struct AdjListNode));
    new_node->dest = dest;
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}


struct Graph* create_graph(int V) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = malloc(V * sizeof(struct AdjListNode*));
    for (int i = 0; i < V; i++)
        graph->array[i] = NULL;
    return graph;
}


void add_edge(struct Graph* graph, int src, int dest, int weight) {
    // Rajoute l'arrete pour le premier sommet
    struct AdjListNode* node = new_node(dest, weight);
    node->next = graph->array[src];
    graph->array[src] = node;

    // Rajoute l'arrete pour le deuxieme sommet
    node = new_node(src, weight);
    node->next = graph->array[dest];
    graph->array[dest] = node;
}


//Pour check si le caractère en question est un nombre
int is_number(char *s){
    if (s[0] == '\0')
        return 0;

    for (int i = 0; s[i]; i++){
        if (s[i] < '0' || s[i] > '9')
            return 0;
    }
    return 1;
}


void remove_newline(char* s) {
    if (!s) return;
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n')
        s[len-1] = '\0';
}


// Lis les donnees d'un fichier et cree le graphe correspondant
struct Graph* prepare_graph(char* filename, Dictionnary dico){
    FILE* f = fopen(filename, "r");
    if (!f){
        fprintf(stderr, "Erreur pas de fichier %s \n", filename);
        return NULL;
    }

    // Nombre de stations a la fin
    int stations = -1;

    // On lit et on verifie que les stations soient valides
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), f)){
        remove_newline(line); 
        if (line[0] == '#' || line[0] == '\0')
            continue;
    
        if (strncmp(line, "STATION", 7) != 0)
            continue;

        char* tok = strtok(line, ";");
        tok = strtok(NULL, ";");

        if (!tok || !is_number(tok)){
            fprintf(stderr, "Probleme Station : ID de %s invalide\n",tok);
            continue;
        }

        int id = atoi(tok);

        tok = strtok(NULL, "\n");
        if (!tok || strlen(tok)==0) {
            fprintf(stderr, "Probleme: Station pas de nom pour l'id %i\n", id);
            continue;
        }

        if (get_value(dico, tok, NULL)) {
            fprintf(stderr, "Probleme: La station %s existe deja\n", tok);
        }

        add_pair(dico, tok, id);
        if (id > stations) stations = id;
    }

    struct Graph *graph = create_graph(stations + 1);
    rewind(f);

    // On lit et on verifie que les edges soient valides
    while (fgets(line, sizeof(line), f)){
        remove_newline(line);
        if (line[0] == '#' || line[0] == '\0')
            continue;
        
        if (strncmp(line, "EDGE", 4) != 0)
            continue;

        char* tok = strtok(line, ";");

        tok = strtok(NULL, ";");
        if (!tok || !is_number(tok)) continue;
        int src = atoi(tok);

        tok = strtok(NULL, ";");
        if (!tok || !is_number(tok)) continue;
        int dest = atoi(tok);

        tok = strtok(NULL, "\n");
        if (!tok || !is_number(tok)){
            fprintf(stderr, "Probleme chemin %i a %i: pas de duree de trajet\n", src, dest);
            continue;
        }
        int weight = atoi(tok);

        if (src < 0 || src > stations || dest < 0 || dest > stations) {
            fprintf(stderr, "Probleme chemin: station inexistante (%d ou %d)\n", src, dest);
            continue;
        }

        add_edge(graph, src, dest, weight);
    }

    fclose(f);
    
    for (int i = 0; i <= stations; i++) {
        if (graph->array[i] == NULL) {
            fprintf(stderr, "Probleme: la station %i n'a aucune arrete\n", i);
        }
    }

    return graph;
}

