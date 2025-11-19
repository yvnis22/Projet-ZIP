#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>




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
    grille.cellules[0][0].numero = 1;
    
    // Mark starting position as visited
    
    
    
    
    char input;

    while (true) {
        afficher_grille(&grille, curseur);

        printf("\nUse ZQSD (or WASD) to move. Press 'x' to quit.\n");
        printf("Input: ");

        // Clear input buffer before reading
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        input = getchar();

        if (input == 'x' || input == 'X')
            break;

        deplacer_curseur(&curseur, &grille, input);
        
        
       
        
        
        
    }

    return 0;
}