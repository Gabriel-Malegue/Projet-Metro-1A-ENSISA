#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"
#include "graph.h"

Deg_Sta degre_entry(struct Graph* graph){
    Deg_Sta tableau_deg = malloc(graph->V * sizeof(struct degre_station));

    for(int i = 0; i < graph->V; i++){
        tableau_deg[i].id = i;

        int degre = 0;
        struct AdjListNode* curr = graph->array[i];

        while(curr){ //on recup en fonction du degré sortant
            degre++;
            curr = curr->next;
        }
        tableau_deg[i].degre = degre;
    }

    return tableau_deg;
}


void selection_sort(Deg_Sta arr, int n){
    int comparaison = 0;
    int swap = 0;

    for(int i = 0; i < n-1; i++){
        int min = i;

        for(int j = i + 1; j < n; j++){
            if (arr[j].degre < arr[min].degre)
                min = j;
            comparaison++;
        }

        if(min != i){
            struct degre_station tmp = arr[i];
            arr[i] = arr[min];
            arr[min] = tmp;
            swap++;
        }
    }
    printf("Statistique pour le tri par selection\n");
    printf("Comparaisons : %d\n", comparaison);
    printf("Swaps : %d\n", swap);
}

void insertion_sort(Deg_Sta arr, int n){
    int comparaison = 0;
    int swap = 0;

    for(int i = 1; i < n; i++){
        struct degre_station key = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j].degre > key.degre){
            arr[j+1] = arr[j];
            j--;
            comparaison++;
            swap++;
        }
        comparaison++;
        arr[j+1] = key;
    }
    printf("Statistique pour le tri par insertion\n");
    printf("Comparaisons : %d\n", comparaison);
    printf("Swaps : %d\n", swap);
}