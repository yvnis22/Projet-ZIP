#include "grille.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

void initialiser_grille(Grille *grille, int lignes, int colonnes) {
    if (!grille) return;
    if (lignes < TAILLE_MIN) lignes = TAILLE_MIN;
    if (lignes > TAILLE_MAX) lignes = TAILLE_MAX;
    if (colonnes < TAILLE_MIN) colonnes = TAILLE_MIN;
    if (colonnes > TAILLE_MAX) colonnes = TAILLE_MAX;
    
    grille->lignes = lignes;
    grille->colonnes = colonnes;
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            grille->cellules[i][j].numero = 0;
            grille->cellules[i][j].visite = false;
        }
    }
}



    

void deplacer_curseur(Position *curseur, int lignes, int colonnes, char touche) {
    switch (touche) {
        case 'w': case 'W': case 'z': case 'Z':
            if (curseur->y > 0) curseur->y--;
            break;

        case 's': case 'S':
            if (curseur->y < lignes - 1) curseur->y++;
            break;

        case 'a': case 'A': case 'q': case 'Q':
            if (curseur->x > 0) curseur->x--;
            break;

        case 'd': case 'D':
            if (curseur->x < colonnes - 1) curseur->x++;
            break;

        default:
            break;
    }
}
