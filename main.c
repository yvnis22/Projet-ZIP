#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void afficher_grille( Grille *grille, Position curseur) {
    system("cls"); // For Windows (VSCode)

    for (int i = 0; i < grille->lignes; i++) {
        for (int j = 0; j < grille->colonnes; j++) {

            if (curseur.x == j && curseur.y == i){
                printf("[X] "); // Current cell
                grille->cellules[i][j].visite = true ;}
            else if (grille->cellules[i][j].numero != 0)
                printf("[%d] ", grille->cellules[i][j].numero); // Future ZIP numbers

            else if (grille->cellules[i][j].visite == true){
                printf("[U] "); // visited cell
            }
            else
                printf("[ ] "); // Empty cell
        }
        printf("\n");
    }
}


int main() {

    Grille grille;
    int taille;
    int nb_numeros; 

    printf("Jeu ZIP - Configuration de la partie\n");
    printf("Entrez la taille de la grille souhaitee (entre 5 et 10 inclus) sinon 5 automatiquement : ");
    scanf("%d", &taille);
    if (taille < TAILLE_MIN || taille > TAILLE_MAX) taille = 5;

    printf("Entrez le nombre de numeros souhaite (entre 1 et 12 inclus) sinon 5 automatiquement : ");
    scanf("%d", &nb_numeros);
    if (nb_numeros < 1 || nb_numeros > NB_NUMEROS_MAX){ nb_numeros = 5;}

    initialiser_grille(&grille, taille, taille);

    Position curseur = {0, 0};
    for (int i = 0; i < taille; ++i)
        for (int j = 0; j < taille; ++j)
            if (grille.cellules[i][j].numero == 1)
                curseur = (Position){j, i};
    char input;

while (true) {
    afficher_grille(&grille, curseur);

    printf("\nUse ZQSD (or WASD) to move. Press 'x' to quit.\n");
    printf("Input: ");

    scanf(" %c", &input);

    if (input == 'x' || input == 'X')
        break;

    deplacer_curseur(&curseur, grille.lignes, grille.colonnes, input);
}

printf("Fin du jeu.\n");


}