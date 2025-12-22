#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "graph.h"

#define MAX_LINE 300
#define MAX_ID   300

char* stationNames[MAX_ID];
int isStation[MAX_ID];


struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = malloc(sizeof(*newNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = malloc(sizeof(*graph));
    graph->V = V;
    graph->array = calloc(V, sizeof(struct AdjListNode*));
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct AdjListNode* node = newAdjListNode(dest, weight);
    node->next = graph->array[src];
    graph->array[src] = node;

    node = newAdjListNode(src, weight);
    node->next = graph->array[dest];
    graph->array[dest] = node;
}

//Pour check si le caractère en question est un nombre
int isNumber(char *s){
    if (s[0] == '\0')
        return 0;

    for (int i = 0; s[i]; i++){
        if (s[i] < '0' || s[i] > '9')
            return 0;
    }
    return 1;
}

void removeNewline(char* s) {
    if (!s) return;
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n')
        s[len-1] = '\0';
}

struct Graph* PrepareGraph(char* filename){
    FILE* f = fopen(filename, "r");
    if (!f){
        printf("Erreur pas de fichier %s \n", filename);
        return NULL;
    }

    for (int i = 0; i < MAX_ID; i++){
        stationNames[i] = NULL;
        isStation[i] = 0;
    }


    char line[MAX_LINE];
    int maxId = -1;

    //on lit et on verifie que les station soient valide
    while (fgets(line, sizeof(line), f)){
        removeNewline(line); 
        if (line[0] == '#' || line[0] == '\0')
            continue;
    
        if (strncmp(line, "STATION", 7) != 0)
            continue;

        char* tok = strtok(line, ";");
        tok = strtok(NULL, ";");
        removeNewline(tok); // pour enlever le retour à la ligne car c'est moche
        if (!tok || !isNumber(tok)){
            printf( "Problème Station : ID de %s invalide\n",tok);
            continue;
        }

        int id = atoi(tok);

        tok = strtok(NULL, "\n");
        if (!tok || strlen(tok)==0) {
            printf("Problème Station pas de nom pour l'id %i\n", id);
            continue;
        }

        if (isStation[id]){
            printf("Problème Station : station %i définie plusieurs fois donc %s pas pris en compte\n", id, tok);
            continue;
        }

        isStation[id] = 1;
        stationNames[id] = malloc(strlen(tok) + 1);
        strcpy(stationNames[id], tok);
        if (id > maxId) 
            maxId = id;
    }

    struct Graph *graph = createGraph(maxId + 1);
    rewind(f);

    //on lit et on verifie que les edges soient valide
    while (fgets(line, sizeof(line), f)){
        removeNewline(line);
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
        if (!tok || !isNumber(tok)){
            printf("Problème chemin %i à %i : pas de duré de trajet\n", src, dest);
            continue;
        }
        int weight = atoi(tok);

        if (!isStation[src] || !isStation[dest]){
            printf("Problème chemin : station inexistante (%d ou %d)\n", src, dest);
            continue;
        }
        
        addEdge(graph, src, dest, weight);
    }

    fclose(f);
    for (int i = 0; i <= maxId; i++) {
        if (isStation[i] && graph->array[i] == NULL) {
            printf("Problème : la station %i (%s) n'a aucune arête\n", i, stationNames[i]);
        }
    }

    return graph;
}

