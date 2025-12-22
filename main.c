#include <stdio.h>

#include "graph.h"
#include "menu.h"

int main() {
    struct Graph* g = PrepareGraph("data/metro.txt");
    if (!g) {
        fprintf(stderr, "Le graphe n'a pas pu etre initialiser");
        return 1;
    }
        
    affichermenu();
    return 0;
}
