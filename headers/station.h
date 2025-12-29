#ifndef FONCTION_STATION_H
#define FONCTION_STATION_H

#include "graph.h"

void info_station(Graph * graph, int id);
void station_voisine(Graph * graph, int id);
void chemin_minimal(Graph * graph, int id_depart, int id_arriver);
void degre_sortant(Graph * graph, int asc);

#endif