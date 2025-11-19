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
        }
    }
}

void afficher_grille(Grille *grille, Position curseur) {
    system("cls");  // For Windows

    for (int i = 0; i < grille->lignes; i++) {
        for (int j = 0; j < grille->colonnes; j++) {
            // Afficher la position du curseur avec un marqueur spécial
            if (curseur.x == j && curseur.y == i) {
                if (grille->cellules[i][j].numero != 0) {
                    printf("[%d]", grille->cellules[i][j].numero);
                } 
            }
            else if (grille->cellules[i][j].numero != 0) {
                printf("[%d] ", grille->cellules[i][j].numero);
            }

            else {
                printf("[ ] ");
            }
        }
        printf("\n");
    }
}

void deplacer_curseur(Position *curseur, Grille *grille, char touche) {
    int new_x = curseur->x;
    int new_y = curseur->y;

    switch (touche) {
        case 'w': case 'W': case 'z': case 'Z':
            if (curseur->y > 0) new_y--;
            break;

        case 's': case 'S':
            if (curseur->y < grille->lignes - 1) new_y++;
            break;

        case 'a': case 'A': case 'q': case 'Q':
            if (curseur->x > 0) new_x--;
            break;

        case 'd': case 'D':
            if (curseur->x < grille->colonnes - 1) new_x++;
            break;

        default:
            return;
    }
    
    // Obtenir le numéro de la case actuelle
    int numero_actuel = grille->cellules[curseur->y][curseur->x].numero;
    int nv_numero = grille->cellules[new_y][new_x].numero;
    
    // Le joueur peut se déplacer si :
    // 1. La case de destination est vide (numero == 0)
    // 2. La case de destination a le numéro (n-1) où n est le numéro actuel (retracer ses pas)
    if (nv_numero == 0) {
        // Avancer : nouvelle case, on incrémente
        curseur->x = new_x;
        curseur->y = new_y;
        grille->cellules[new_y][new_x].numero = numero_actuel + 1;
    }
    else if (nv_numero == numero_actuel - 1) {
        // Reculer : retourner sur ses pas, on efface la case actuelle
        grille->cellules[curseur->y][curseur->x].numero = 0;
        curseur->x = new_x;
        curseur->y = new_y;
    }
    // Sinon, le déplacement n'est pas autorisé (ne rien faire)
}
