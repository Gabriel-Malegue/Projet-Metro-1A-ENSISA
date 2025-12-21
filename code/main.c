#include <stdio.h>

#include "graph.h"
#include "menu.h"

int main() {
    struct Graph* g = PrepareGraph("code/data/metro.txt");
    if (!g)
        return 1;

    affichermenu();
    return 0;
}
