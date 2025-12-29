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


// Trie par selection
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
        struct degre_station tmp = arr[i];
        arr[i] = arr[min];
        arr[min] = tmp;
        swap++;
    
    }
    printf("Statistique pour le tri par selection\n");
    printf("Comparaisons : %d\n", comparaison);
    printf("Swaps : %d\n", swap);
}


// Trie par insertion
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


// Trie rapide
int comp_q;
int swap_q;

int partition(Deg_Sta arr, int l, int r){
    int p = arr[r].degre;
    int i = l-1;
    for(int j = l; j < r; j++){
        if(arr[j].degre < p){
            i++;
            struct degre_station tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            swap_q++;
        }
        comp_q++;
    }
    struct degre_station tmp = arr[i+1];
    arr[i+1] = arr[r];
    arr[r] = tmp;
    swap_q++;
    return i+1;
}

void quick_sort_rec(Deg_Sta arr, int l, int r){
    if (l < r) {
        int p = partition(arr, l, r);
        quick_sort_rec(arr, l, p - 1);
        quick_sort_rec(arr, p + 1, r);
    }
}

void quick_sort(Deg_Sta arr, int n){
    comp_q = 0;
    swap_q = 0;
    quick_sort_rec(arr, 0, n - 1);

    printf("Statistique pour le tri rapide\n");
    printf("Comparaisons : %d\n", comp_q);
    printf("Swaps : %d\n", swap_q);
}