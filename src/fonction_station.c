#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonction_station.h"
#include "graph.h"
#include "menu.h"
#include "trie.h"

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
    printf("Work in progress bientot dispo (fin bientot j'ai menti faut implémenter le Dijkstra kaka) \n");
}

void degre_sortant(struct Graph* graph){
    Deg_Sta deg = degre_entry(graph); //on initialise le tableau des degres 

    //Tri par selection
    Deg_Sta deg_selection = malloc(graph->V * sizeof(struct degre_station));
    memcpy(deg_selection, deg, graph->V * sizeof(struct degre_station));
    selection_sort(deg_selection, graph->V);
    printf("\n");

    //Trie par insertion
    Deg_Sta deg_insertion = malloc(graph->V * sizeof(struct degre_station));
    memcpy(deg_insertion, deg, graph->V * sizeof(struct degre_station));
    insertion_sort(deg_insertion, graph->V);
    printf("\n");

    //Trie rapide (jsp ce que c'est)
    Deg_Sta deg_fast = malloc(graph->V * sizeof(struct degre_station));
    memcpy(deg_fast, deg, graph->V * sizeof(struct degre_station));
    //fast_sort(deg_fast, graph->V); (faut creer la fonction)
    printf("\n");
    
    for(int i=graph->V-1; i>=0; i--){
        printf("Station %i - %s -> Degre Sortant : %i \n", deg_insertion[i].id, 
            graph->station_names[deg_insertion[i].id] ,deg_insertion[i].degre);
    }
    
    free(deg);
}