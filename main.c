#include <stdio.h>
#include "graph.h"

int main() {
    struct Graph *g = PrepareGraph("metro.txt");
    if (!g)
        return 1;

    return 0;
}
