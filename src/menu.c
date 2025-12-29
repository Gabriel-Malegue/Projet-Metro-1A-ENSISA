#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "menu.h"
#include "dico.h"
#include "station.h"

int choisir_station(Dictionnary * dico)
{
    char station[50];
    scanf(" %[^\n]", station);
    int id;

    if (is_number(station) == 1) {
        id = atoi(station);
    } else {
        if (!get_value(dico, station, &id))
        {
            printf("Station %s non trouvée !\n", station);
            return -1;
        }
    }
    return id;
}

void afficher_menu(Dictionnary * dico, Graph * graph)
{
    int nombre;
    int quitter = 0;

    while (quitter != 1)
    {
        printf("\n=============== MENU RESEAU DE TRANSPORT ===============\n");
        printf("1 - Afficher les informations d'une station\n");
        printf("2 - Lister les voisins d'une station\n");
        printf("3 - Chemin le plus rapide entre 2 stations\n");
        printf("4 - Afficher les stations triees par degre de connexion\n");
        printf("0 - Quitter\n");
        printf("Votre choix : ");

        if (scanf("%d", &nombre) != 1)
        {
            printf("Entree invalide !\n");
        }
        
        int id = -1;
        switch (nombre) {
        case 1:
            printf("Sur quelle station souhaitez-vous des information ?\n");
            id = choisir_station(dico);
            if (id != -1)
            {
                info_station(graph, id);
            }
            break;

        case 2:
            printf("De quelle station souhaitez-vous connaitre les voisins ?\n");
            id = choisir_station(dico);
            if (id != -1)
            {
                station_voisine(graph, id);
            }
            break;

        case 3:
            int id_depart = -1;
            int id_arriver = -1;

            while (id_depart < 0 || id_depart >= graph->V)
            {
                printf("Station de départ ?\n");
                id_depart = choisir_station(dico);
            }

            while (id_arriver < 0 || id_arriver >= graph->V || id_depart == id_arriver)
            {
                printf("Station d'arrivée ?\n");
                id_arriver = choisir_station(dico);
            }

            chemin_minimal(graph, id_depart, id_arriver);
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
