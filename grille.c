#include "grille.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>



void afficher_grille(Grille *grille, Position curseur) {
    clear();

    for (int i = 0; i < grille->lignes; i++) {
        for (int j = 0; j < grille->colonnes; j++) {

            // Curseur
            if (curseur.x == j && curseur.y == i) {
                attron(COLOR_PAIR(2) | A_BOLD);
                printw("[X] ");
                attroff(COLOR_PAIR(2) | A_BOLD);
                continue;
            }

            // Chiffre (1,2,3...)
            if (grille->cellules[i][j].chiffre != 0) {
                attron(COLOR_PAIR(3) | A_BOLD);
                printw("[%d] ", grille->cellules[i][j].chiffre);
                attroff(COLOR_PAIR(3) | A_BOLD);
                continue;
            }

            // Chemin (#)
            if (grille->cellules[i][j].numero != 0) {
                attron(COLOR_PAIR(4));
                printw("[#] ");
                attroff(COLOR_PAIR(4));
                continue;
            }

            // Case vide
            attron(COLOR_PAIR(1));
            printw("[ ] ");
            attroff(COLOR_PAIR(1));
        }
        printw("\n");
    }

    refresh();
}



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

