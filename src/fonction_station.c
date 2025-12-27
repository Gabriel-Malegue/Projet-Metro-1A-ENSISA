#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dico.h"
#include "graph.h"
#include "menu.h"
#include "fonction_station.h"

void info_station(Dictionnary* dico, struct Graph* graph, int id){
    (void) dico;
    printf("Nom : (la faut trouver un moyen de recup le nom à partir de l'ID)\n");
    printf("ID : %i \n", id);

    int degre = 0;

    struct AdjListNode* curr = graph->array[id];
        while (curr) {
            degre++;
            curr = curr->next;
        }
    
    printf("Degré sortant : %i", degre);
}