#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dico.h"
#include "graph.h"
#include "menu.h"
#include "fonction_station.h"

void info_station(struct Graph* graph, int id){
    printf("Nom : %s \n", graph->station_names[id]);
    printf("ID : %i \n", id);

    int degre = 0;

    struct AdjListNode* curr = graph->array[id];
        while(curr){
            degre++;
            curr = curr->next;
        }
    
    printf("Degré sortant : %i \n", degre);
}

void station_voisine(struct Graph* graph, int id){
    (void) graph;
    (void) id;

    printf("Work in progress bientot dispo \n");
}

void chemin_minimal(Dictionnary* dico, struct Graph* graph, int id_depart, int id_arriver){
    (void) dico;
    (void) graph;
    (void) id_depart;
    (void) id_arriver;
    printf("Work in progress bientot dispo (fin bientot j'ai menti faut implémenter le Dijestra kaka) \n");
}

void degre_sortant(Dictionnary* dico, struct Graph* graph, int id ){
    (void) dico;
    (void) graph;  
    (void) id;

    printf("Work in progress bientot dispo (c'est faux ça a chiant l'air à implémenter ça aussi) \n");
}