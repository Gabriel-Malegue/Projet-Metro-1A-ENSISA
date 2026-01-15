#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "menu.h"
#include "dico.h"
#include "station.h"

int choisir_station(Dictionnary *dico)
{
    char station[64];
    scanf(" %63[^\n]", station);
    int id;

    if (is_number(station))
        return atoi(station);

    if (!get_value(dico, station, &id))
    {
        printf("Station %s non trouvée !\n", station);
        return -1;
    }

    return id;
}

void afficher_menu(Dictionnary *dico, Graph *graph)
{
    int nombre = 0;
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
        switch (nombre)
        {
        case 1:
            printf("Station dont vous souhaitez connaitre les informations: ");
            id = choisir_station(dico);
            if (id != -1)
            {
                printf("\n====INFORMATIONS====\n");
                info_station(graph, id);
            }
            break;

        case 2:
            printf("Station dont vous souhaitez connaitre les voisins: ");
            id = choisir_station(dico);
            if (id != -1)
            {
                printf("\n====STATIONS VOISINES====\n");
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

            printf("\n====CHEMIN MINIMAL====\n");
            chemin_minimal(graph, id_depart, id_arriver);
            break;

        case 4:
            printf("\n====TRI PAR DEGRE SORTANT====\n");

            char ordre[16];
            printf("Ordre du tri desire (asc pour ascendant dsc sinon): ");

            // vider stdin avant fgets sinon ca marche pas
            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            if (fgets(ordre, sizeof(ordre), stdin) != NULL) {
                ordre[strcspn(ordre, "\n")] = '\0'; // enlever le \n
            } else {
                strcpy(ordre, "dsc");
            }

            // valeur par défaut si vide
            if (ordre[0] == '\0') strcpy(ordre, "dsc");

            int ascendant = (strcmp(ordre, "asc") == 0) ? 1 : 0;

            degre_sortant(graph, ascendant);
            break;

        case 0:
            printf("Merci pour votre passage sur notre application made by Glgmch & Greehon\n");
            quitter = 1;
            break;

        default:
            printf("Selection invalide ! \nChoisir un nombre entre 0 et 4. \n");
            break;
        }
    }
}
