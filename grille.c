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
    // initialise les numero des cases a 0 
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            grille->cellules[i][j].numero = 0;
        }
    }
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
            // Affiche les nombres a la suite 
            else if (grille->cellules[i][j].numero != 0) {
                printf("[%c] ", 254);  // ■ en CP437

            }
            // Affiche les cases vides
            else {
                printf("[ ] ");
            }
        }
        printf("\n");
    }
}

void deplacer_curseur(Position *curseur, Grille *grille, char touche) {
    // permet de conserver les coordonnees actuels
    // cela permet de ne pas faire le mouvement de suite pour pouvoir voir si le mouvement est legal 
    int new_x = curseur->x;
    int new_y = curseur->y;
    // switch/case est une facon plus propre d'ecrire "if else if else if..."  
    switch (touche) { // on dit quon aimerait tester la variable touche 
        case 'w': case 'W': case 'z': case 'Z': // test les differents cas pour aller en haut
            if (curseur->y > 0) new_y--; // update que le nouvelles coordonnee et pas les actuels 
            break; // si c propre arretez de me faire chier xD

        case 's': case 'S': // pareil pour le bas
            if (curseur->y < grille->lignes - 1) new_y++;
            break;

        case 'a': case 'A': case 'q': case 'Q': // a gauche
            if (curseur->x > 0) new_x--;
            break;

        case 'd': case 'D':
            if (curseur->x < grille->colonnes - 1) new_x++; // a droite
            break;

        default:
            return;
    }
    
    // pour avoir le numero de la case et le numero de la case apres le mouvement
    int numero_actuel = grille->cellules[curseur->y][curseur->x].numero;
    int nv_numero = grille->cellules[new_y][new_x].numero;
    // je laisse la descrpition de l'IA qui est assez claire
    // javais utiliser chatgpt juste pour le systeme de backtracking en gros retracer ses pas 
    // la logique est assez simple :
    // Le joueur peut se déplacer si :
    // 1. La case de destination est vide (numero == 0)
    // 2. La case de destination a le numéro (n-1) où n est le numéro actuel (retracer le chemin )
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
    // on laisse un else vide pour pouvoir dire que le deplacement es illegal donc juste on refresh l'input
}
