#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "dico.h"

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

struct Graph* prepare_graph(char* filename){
    FILE* f = fopen(filename, "r");
    if (!f){
        fprintf(stderr, "Erreur pas de fichier %s \n", filename);
        return NULL;
    }

    char line[MAX_LINE];
    int max_id = 0; // Nombre de stations a la fin

    //on lit et on verifie que les station soient valide
    while (fgets(line, sizeof(line), f)){
        remove_newline(line); 
        if (line[0] == '#' || line[0] == '\0')
            continue;
    
        if (strncmp(line, "STATION", 7) != 0)
            continue;

        char* tok = strtok(line, ";");
        tok = strtok(NULL, ";");

        if (!tok || !is_number(tok)){
            printf( "Problème Station : ID de %s invalide\n",tok);
            continue;
        }

        int id = atoi(tok);

        tok = strtok(NULL, "\n");
        if (!tok || strlen(tok)==0) {
            fprintf(stderr, "Problème: Station pas de nom pour l'id %i\n", id);
            continue;
        }

        //
        // Rajout check si la ligne existe deja
        //

        
        //
        // Ajouter la paire station ID
        //

        if (id > max_id) max_id++;
    }

    struct Graph *graph = create_graph(max_id + 1);
    rewind(f);

    //on lit et on verifie que les edges soient valide
    while (fgets(line, sizeof(line), f)){
        remove_newline(line);
        if (line[0] == '#' || line[0] == '\0')
            continue;
        
        if (strncmp(line, "EDGE", 4) != 0)
            continue;

        char* tok = strtok(line, ";");

        tok = strtok(NULL, ";");

        int src = atoi(tok);

        tok = strtok(NULL, ";");

        int dest = atoi(tok);

        tok = strtok(NULL, "\n");
        if (!tok || !is_number(tok)){
            printf("Problème chemin %i à %i : pas de duré de trajet\n", src, dest);
            continue;
        }
        int weight = atoi(tok);

        // if (!is_station[src] || !is_station[dest]){
        //    printf("Problème chemin : station inexistante (%d ou %d)\n", src, dest);
        //    continue;
        // }
        
        add_edge(graph, src, dest, weight);
    }

    fclose(f);
    
    // for (int i = 0; i <= max_id; i++) {
    //     if (is_station[i] && graph->array[i] == NULL) {
    //         printf("Problème : la station %i (%s) n'a aucune arête\n", i, station_names[i]);
    //     }
    // }

    return graph;
}

