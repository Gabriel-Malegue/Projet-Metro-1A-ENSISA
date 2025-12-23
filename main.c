#include <stdio.h>

#include "graph.h"
#include "menu.h"
#include "dico.h"

#define DICT_SIZE 512 // Taille maximale pour le dictionnaire


int main() {
    // Prepare le dictionnaire
    Dictionnary dico = initialize_dictionnary(DICT_SIZE);

    // Prepare le graph, intialise le dictionnaire
    struct Graph* g = prepare_graph("data/metro.txt", dico);
    if (!g) {
        fprintf(stderr, "Le graphe n'a pas pu etre initialiser\n");
        return 1;
    }
    
    // Affichage
    afficher_menu();

    free_dictionnary(dico);
    free_graph(g);
    return 0;
}
