// Inclusion des bibliotheques necessaires
// -- Noah

#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// définition de la grille selon les choix de l'utilisateur puis initialisation de celle ci 
// -- Noah 

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

    // met le curseur est le numero de la premiere case a 1 
    Position curseur = {0, 0};
    grille.cellules[0][0].numero = 1;

    // declare la variable qui va nous servir a input 
    char input;

    while (true) {
        afficher_grille(&grille, curseur);

        printf("\nUse ZQSD (or WASD) to move. Press 'x' to quit.\n");
        printf("Input: ");

        // nettoie tout les characteres speciaux(enter) et la memoire de getchar, copie colle ia mais a rechercher 
        // une methode plus simple/comprehensible
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        input = getchar();

        // mets fin au programme 
        if (input == 'x' || input == 'X')
            break;
        // appelle la fonction qui fait tout 
        deplacer_curseur(&curseur, &grille, input);
        
    }

    return 0;
    
}