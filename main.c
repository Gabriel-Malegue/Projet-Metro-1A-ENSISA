#include <stdio.h>

#include "graph.h"
#include "menu.h"
#include "dico.h"

int main() {
    struct Graph* g = prepare_graph("data/metro.txt");
    if (!g) {
        fprintf(stderr, "Le graphe n'a pas pu etre initialiser");
        return 1;
    }
        
    afficher_menu();

    return 0;
}
