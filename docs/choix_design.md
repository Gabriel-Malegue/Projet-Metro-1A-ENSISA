# SUPPORT AU RAPPORT FINAL

Ce fichier vient completer les commentaires du code et documente les choix qu'on a fait lors de l'implementation du systeme de gestion du metro. Il permettera aussi de rediger le rapport final du projet.  

On decrira notre approche a l'implementation module par module, *sans suivre d'ordre particulier*. Lorsqu'on fait reference a un module, on parle a la fois du code source (.c) et du fichier interface (.h).  

## DICO

Il s'agit d'un fichier recuperer a un ancien projet, auquel on a readapter la mise en page et les commentaires (originalement en anglais). Les fichiers decrivent le code pour un dictionnaire qui utilise un hashing FNV1-a avec les coefficients de la version 32 bits.  

Les coefficients 32 bits etaient suffisant pour la quantite de donnees que l'on traite et permet de gagner en calcul par rapport a la version 64 bits. 

## DIJKSTRA

Il s'agit aussi d'une implementation recuperee a un ancien projet (d'ou la fonction inutile si toujours presente dans la version finale). On a choisit l'implementation Dijkstra *basique* avec des lsites chainees en O(V^2). La quantitee relativement faible de donnees fait que l'on a pas besoin de plus. Une implementation avec une file prioritaire nous aurait fait un temps de calcul de O( (V + E) * log V ), et cela aurait ete legermenet plus rapide ici.   

Notons que notre implementation est techniqiuement en O(V^2 + E) et que V^2 l'emporte dans la majoritee des cas, or si on a un graph assez dense (E de l'ordre de V^2), la version implementee le remporte sur la version avec file de prioritee. L'ideale biensur, serait de calculer le nombre d'arcs au prealable et choisir une des deux versions.  

## TRIE

Le fichier trie comporte toutes les fonctions de trie en rapport avec les degres sortant des stations. L'implementation est tres specifique au probleme, c.a.d que les fonctions de trie prennent directement des arguments de type definis comme Deg_Sta (degre station).  

Cela rends le fichier moins utilisable mais plus facile a comprendre dans le contexte du projet, et rends notre implementation plus securise que des fonctions qui prendront des pointeurs de type void en argument, comme notamment la fonction quick sort de la librairie standard ([doc en ligne](https://koor.fr/C/cstdlib/qsort.wp)), qui a du etre ecrite avec plus de mesures de precaution en tete pour une utilisation plus generale.  

## STATION

Maitre gabriel a fait un excellent travail et je ne pense pas pouvoir bien tout decrire

## GRAPH

Maitre gabriel a fait un excellent travail et je ne pense pas pouvoir bien tout decrire

## MENU

Menu principal, prends les donnees a l'aide de scanf et fgets. fgets necessite de vider le buffer avant utilisation mais apporte l'avantage de ne pas planter lorsqu'un utilisateur fait uen entree vide (Sur Windows en tout cas). Le melange de scanf et fgets n'est pas tres commun, ca marche ici mais on aurait egalement pu garder que des fgets ou scanf pour uniformiser le code.

## MAIN / ARCHITECTURE DES DEPENDENCES

On a eviter de creer un god-file, sur lequel depends tout notre projet. On s'est contenter d'initialiser la sortie de la console en UTF-8 pour bien afficher tous les characteres correctements (l'encodage ASCII est intrinseque au C mais cause des problemes lors de l'affichage de characteres speciaux genre e accent etc.), puis d'appeler une fonction qui initalise le graph et le dictionnaire afin de les passer au module [MENU](#menu), qui lui a son tour les passe au module [STATION](#station) en fonction des appels utilisateur. Les fonctions sont donc appelees sur mesure et pas a l'avance.  