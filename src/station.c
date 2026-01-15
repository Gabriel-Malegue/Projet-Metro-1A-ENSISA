#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "station.h"
#include "graph.h"
#include "menu.h"
#include "trie.h"
#include "dijkstra.h"

void info_station(Graph * graph, int id)
{
    // ID et Nom
    printf("Nom : %s \n", graph->station_names[id]);
    printf("ID : %i \n", id);

    // Degre sortant
    int degre = 0;
    struct AdjListNode * curr = graph->array[id];
    while (curr) {
        degre++;
        curr = curr->next;
    }
    printf("Degre sortant : %i \n", degre);
}

void station_voisine(Graph * graph, int id)
{
    struct AdjListNode *curr = graph->array[id];
    if (!curr)
    {
        printf("La station %i - %s n'a aucun voisin.\n", id, graph->station_names[id]);
        return;
    }

    printf("Stations voisines de  %i - %s :\n\n", id, graph->station_names[id]);
    while (curr) {
        int voisin_id = curr->dest;
        int temps = curr->weight;
        char *nom_voisin = graph->station_names[voisin_id];
        printf("%i - %s a %i minutes\n", voisin_id, nom_voisin, temps);
        curr = curr->next;
    }
}

void chemin_minimal(Graph * graph, int id_depart, int id_arriver)
{
    int taille_chemin;
    int distance;
    int* chemin = dijkstra(graph, id_depart, id_arriver, &distance, &taille_chemin);

    if (chemin && distance != INF) 
    {
        printf("Distance entre %s (%i) et %s (%i) : %i minutes \n", graph->station_names[id_depart],
                id_depart, graph->station_names[id_arriver], id_arriver, distance);
        printf("Chemin a emprunter: \n ~ ");

        for (int i = 0; i < taille_chemin - 1; i++) {
            int noeud = chemin[i];
            printf("%s (%i) -> ", graph->station_names[noeud], noeud);
        }
        printf("%s (%i) \n", graph->station_names[id_arriver], id_arriver);
        free(chemin);
    }
    else 
    {
        printf("Pas de chemins entre %s (%i) et %s (%i) \n", graph->station_names[id_depart],
                id_depart, graph->station_names[id_arriver], id_arriver);
    }
    
}

void degre_sortant(Graph * graph, int asc)
{
    Deg_Sta deg = degre_entry(graph); // on initialise le tableau des degres

    // Tri par selection
    Deg_Sta deg_selection = malloc(graph->V * sizeof(struct degre_station));
    memcpy(deg_selection, deg, graph->V * sizeof(struct degre_station));
    selection_sort(deg_selection, graph->V);
    printf("\n");

    // Trie par insertion
    Deg_Sta deg_insertion = malloc(graph->V * sizeof(struct degre_station));
    memcpy(deg_insertion, deg, graph->V * sizeof(struct degre_station));
    insertion_sort(deg_insertion, graph->V);
    printf("\n");

    // Trie rapide
    Deg_Sta deg_quick = malloc(graph->V * sizeof(struct degre_station));
    memcpy(deg_quick, deg, graph->V * sizeof(struct degre_station));
    quick_sort(deg_quick, graph->V);
    printf("\n");

    if (asc) 
    {
        printf("Par ordre ascendant: \n");
        for (int i = 0; i < graph->V; i++) {
                printf("Station %i - %s -> Degre Sortant : %i \n", deg_quick[i].id,
                    graph->station_names[deg_quick[i].id], deg_quick[i].degre);
        }
    } 
    else 
    {
        printf("Par ordre descendant: \n");
        for (int i = graph->V - 1; i >= 0; i--) {
                printf("Station %i - %s -> Degre Sortant : %i \n", deg_quick[i].id,
                    graph->station_names[deg_quick[i].id], deg_quick[i].degre);
        }
    }
    

    free(deg);
}