# Projet Métro – ENSISA (Projet-Metro-1A)

## Description
Ce projet consiste à développer un programme en C (norme C99) permettant de manipuler et d’analyser les données d’une ligne de métro à partir d’un **fichier texte**.

Le programme lit les données (stations, distances, connexions, etc.), puis propose un **menu interactif** permettant à l’utilisateur d’effectuer différentes opérations comme l’affichage des stations, le calcul de distances ou la recherche de chemins optimaux.

Il s’agit d’un projet académique réalisé en première année à l’ENSISA.


## Fonctionnalités
- Lecture et parsing d’un fichier texte contenant les données du métro
- Affichage de la liste des stations
- Calcul de la distance entre deux stations
- Recherche du **chemin minimal** entre deux stations
- Tri des stations selon différents critères
- Menu interactif en ligne de commande


## Technologies utilisées
- Langage : **C (C99)**
- Compilateur : **gcc**
- Make


## Compilation
- make (version finale)
- make debug (version avec debug) 
- make valgrind (make debug et execute valgrind qui detecte les fuites de memoire, merci Guillaume) 