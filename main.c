#include <stdio.h>

#include "graph.h"
#include "menu.h"
#include "dico.h"


// Partie pour correctement afficher les accents (UTF-8)
#include <locale.h>

#ifdef _WIN32
    #include <windows.h>
#endif

static void init_utf8(void) {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #else
    setlocale(LC_ALL, "");
    #endif
}
// Fin partie affichage UTF-8


int main() {
    // Initalisation de l'affichage en UTF-8
    init_utf8();

    // Prepare le dictionnaire
    Dictionnary * dico = NULL; 

    // Prepare le graph, intialise le dictionnaire
    Graph * graph = prepare_graph("data/test.txt", &dico);
    if (!graph) {
        fprintf(stderr, "Le graphe n'a pas pu etre initialiser\n");
        return 1;
    }
    
    // Affichage
    afficher_menu(dico, graph);

    //Libérage de la mémoire
    free_dictionnary(dico);
    free_graph(graph);

    return 0;
}
