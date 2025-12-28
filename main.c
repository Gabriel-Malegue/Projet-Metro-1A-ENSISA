#include <stdio.h>

#include "graph.h"
#include "menu.h"
#include "dico.h"

#define DICT_SIZE 512 // Taille maximale pour le dictionnaire


int main() {
    // Prepare le dictionnaire
    Dictionnary dico = NULL; 

    // Prepare le graph, intialise le dictionnaire
    struct Graph* graph = prepare_graph("data/metro.txt", &dico);
    if (!graph) {
        fprintf(stderr, "Le graphe n'a pas pu etre initialiser\n");
        return 1;
    }
    
    // Affichage
    afficher_menu(dico,graph);

    //Libérage de la mémoire
    free_dictionnary(dico);
    free_graph(graph);

    return 0;
}
