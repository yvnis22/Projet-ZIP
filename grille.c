#include "grille.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>


/*
================================================================================
Fonction   : initialiser_grille
Auteur     : Anouk et Noah
Param      : grille (Grille*) - Pointeur vers la grille à initialiser
             lignes (int) - Nombre de lignes souhaitées
             colonnes (int) - Nombre de colonnes souhaitées
Traitement : Définit les dimensions de la grille en respectant les bornes
             min/max et initialise toutes les cases à zéro.
Retour     : Aucun (void)
================================================================================
*/
void initialiser_grille(Grille *grille, int lignes, int colonnes) {

    if (!grille) return;
    if (lignes < TAILLE_MIN) lignes = TAILLE_MIN;
    if (lignes > TAILLE_MAX) lignes = TAILLE_MAX;
    if (colonnes < TAILLE_MIN) colonnes = TAILLE_MIN;
    if (colonnes > TAILLE_MAX) colonnes = TAILLE_MAX;
    
    
    grille->lignes = lignes;
    grille->colonnes = colonnes;
    // initialise les numero et les chiffres des cases a 0 
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            grille->cellules[i][j].numero = 0;
            grille->cellules[i][j].chiffre = 0;
            
        }
    }
    
}

/*
================================================================================
Fonction   : afficher_grille
Auteur     : Anouk et Noah
Param      : grille (Grille*) - Pointeur vers la grille à afficher
             curseur (Position) - Position actuelle du joueur
Traitement : Nettoie l'écran et parcourt la grille pour afficher soit le
             curseur [X], soit les chiffres [n], soit les cases remplies,
             soit les cases vides.
Retour     : Aucun (void)
================================================================================
*/
void afficher_grille(Grille *grille, Position curseur) {
    system("cls");  // Pour Windows

    for (int i = 0; i < grille->lignes; i++) {
        for (int j = 0; j < grille->colonnes; j++) {
            // Affiche la position du curseur avec X 
            if (curseur.x == j && curseur.y == i) {
                if (grille->cellules[i][j].numero != 0) {
                    printf("[X] ");
                } 
            }
            else if ( grille->cellules[i][j].chiffre != 0){
                printf("[%d] ", grille->cellules[i][j].chiffre);
            }
            // Affiche les nombres a la suite 
            else if (grille->cellules[i][j].numero != 0) {
                printf("[%c] ", 254);
            }
            // Affiche les cases vides
            else {
                printf("[ ] ",grille->cellules[i][j].numero );
            }
        }
        printf("\n");
    }
}