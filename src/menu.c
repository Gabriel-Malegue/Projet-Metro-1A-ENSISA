#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "menu.h"
#include "dico.h"
#include "fonction_station.h"

int choisir_station(Dictionnary dico){
    char station[50];
    scanf(" %[^\n]",station);
    int id;
    if(is_number(station)==1){
        id=atoi(station);
    }
    else{
        if (!get_value(dico, station, &id)) {
            printf("Station %s non trouvée !\n", station);
            return -1;
        }
    }
    return id;
}

void afficher_menu(Dictionnary dico,struct Graph* graph){
    int nombre;
    int quitter = 0;

    while (quitter != 1) {
        printf("\n======== MENU RESEAU DE TRANSPORT ========\n");
        printf("1 - Afficher les informations d'une station\n");
        printf("2 - Lister les voisins d'une station\n");
        printf("3 - Chemin le plus rapide entre 2 stations\n");
        printf("4 - Afficher les stations triees par degre de connexion\n");
        printf("0 - Quitter\n");
        printf("Votre choix : ");

        if (scanf("%d", &nombre) != 1){
            printf("Entree invalide !\n");
        }
        int id;
        switch(nombre){
            case 1: 
                printf("Sur quelle station souhaitez-vous des information ?\n");
                id = choisir_station(dico);
                if (id != -1){
                    info_station(graph, id);
                }
                break;
            case 2: 
                printf("De quelle station souhaitez-vous connaitre les voisins ?\n");
                id = choisir_station(dico);
                if (id != -1) {
                    station_voisine(graph, id);
                } 
                break;
            case 3: 
                printf("Station de départ?\n");
                int id_depart = choisir_station(dico);

                printf("Station d'arriver?\n");
                int id_arriver = choisir_station(dico);

                if (id != -1) {
                    chemin_minimal(dico, graph, id_depart, id_arriver);
                } 
                break;
            case 4: 
                 degre_sortant(graph);
                break;
            case 0: 
                quitter = 1;
                break;
        }
    }
}
