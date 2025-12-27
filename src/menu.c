#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "menu.h"
#include "dico.h"
#include "fonction_station.h"

void afficher_menu(Dictionnary* dico,struct Graph* graph) {
    int nombre;
    int quitter = 0;

    while (quitter != 1) {
        printf("\n===== MENU RESEAU DE TRANSPORT =====\n");
        printf("1 - Afficher les informations d'une station\n");
        printf("2 - Lister les voisins d'une station\n");
        printf("3 - Calculer un chemin minimal\n");
        printf("4 - Afficher les stations triees par degre\n");
        printf("0 - Quitter\n");
        printf("Votre choix : ");

        if (scanf("%d", &nombre) != 1) {
            printf("Entree invalide !\n");
        }

        switch(nombre) {
            case 1: 
                char station[20];
                printf("Sur quelle station souhaitez-vous des information ?\n");
                scanf(" %[^\n]",station);
                int id;
                if(is_number(station)==1){
                    id=atoi(station);
                }
                else{
                    if (!get_value(*dico, station, &id)) {
                        printf("Station %s non trouvée !\n", station);
                        break;
                    }
                }
                info_station(dico, graph, id);
                break;
            case 2: printf("Appelle fonction 2 \n"); break;
            case 3: printf("Appelle fonction 3 \n"); break;
            case 4: printf("Appelle fonction 4 \n"); break;
            case 0: quitter = 1;break;
        }
    }
}
