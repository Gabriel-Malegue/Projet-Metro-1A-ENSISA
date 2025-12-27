#ifndef FONCTION_STATION_H
#define FONCTION_STATION_H

void info_station(struct Graph* graph, int id);
void station_voisine( struct Graph* graph, int id);
void chemin_minimal(Dictionnary* dico, struct Graph* graph, int id_depart, int id_arriver);
void degre_sortant(Dictionnary* dico, struct Graph* graph, int id);

#endif