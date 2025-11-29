#include "grille.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>


// Initialise une grille avec des dimensions specifiees et les numeros des cases a 0 par defaut
// -- Noah


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
    grille->cellules[2][4].chiffre = 1;
    grille->cellules[4][2].chiffre = 2;
    grille->cellules[2][1].chiffre = 3;
    grille->cellules[1][1].chiffre = 4;
    grille->cellules[0][3].chiffre = 5;
    grille->cellules[3][3].chiffre = 6;
    
}

void afficher_grille(Grille *grille, Position curseur) {
    system("cls");  // Pour Windows

    for (int i = 0; i < grille->lignes; i++) {
        for (int j = 0; j < grille->colonnes; j++) {
            // Affiche la position du curseur avec X 
            if (curseur.x == j && curseur.y == i) {
                if (grille->cellules[i][j].numero != 0) {
                    printf("[X] ", curseur.chiffre_actuel);

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