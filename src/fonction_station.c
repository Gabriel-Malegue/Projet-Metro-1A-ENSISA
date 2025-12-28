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
    struct AdjListNode* curr = graph->array[id];
    if(!curr){
        printf("La station %i - %s n'a aucun voisin.\n", id, graph->station_names[id]);
        return;
    }

    printf("Station voisine de  %i - %s :\n", id, graph->station_names[id]);
    while(curr){
        int voisin_id = curr->dest;
        int temps = curr->weight;
        char* nom_voisin = graph->station_names[voisin_id];
        printf("%i - %s a %i minutes\n", voisin_id, nom_voisin, temps);
        curr = curr->next;
    }
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