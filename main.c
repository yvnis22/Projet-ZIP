#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
//#include <ncurses/ncurses.h>




int main() {

    srand(time(NULL));
    int depart_x, depart_y;
    Grille grille;
    int taille;
    int nb_numeros;

    printf("Jeu ZIP - Configuration de la partie\n");
    printf("Entrez la taille de la grille souhaitee (entre 5 et 10 inclus) sinon 5 automatiquement : ");
    scanf("%d", &taille);
    if (taille < TAILLE_MIN || taille > TAILLE_MAX) taille = 5;

    printf("Entrez le nombre de numeros souhaite (entre 1 et 12 inclus) sinon 5 automatiquement : ");
    scanf("%d", &nb_numeros);
    if (nb_numeros < 1 || nb_numeros > NB_NUMEROS_MAX) nb_numeros = 5;


    int **visited = (int**) malloc(taille * sizeof(int *));
    for (int i = 0; i < taille; i++)
    {
        visited[i] = (int*)malloc(taille * sizeof(int));
        for (int j = 0; j < taille; j++)
            visited[i][j] = 0;
    }

    int **path = (int**)malloc(taille * taille * sizeof (int*));
    for (int i=0; i<taille; i++)
        path[i]=(int*)malloc(2 * sizeof (int));


   
    
    
    Position curseur = depart_aleatoire(&depart_x, &depart_y, taille);
    printf ("departx=%d, departy=%d\n",depart_x, depart_y) ;
    getchar() ;
    initialiser_grille(&grille, taille, taille);
    // Après avoir trouvé le chemin hamiltonien
    hamiltonien(depart_x, depart_y, 1, taille, visited);
    aff(visited, taille);

    // Placer les numéros preset sur le chemin
    placer_numeros_sur_chemin(&grille, visited, taille, nb_numeros);

    // Le curseur commence toujours au numéro 1
    // Trouver où est le numéro 1 et placer le curseur là
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (grille.cellules[i][j].chiffre == 1) {
                curseur.x = j;
                curseur.y = i;
                curseur.chiffre_actuel = 1;
                grille.cellules[i][j].numero = 1;
            }
        }
    }



    // grille.cellules[curseur.y][curseur.x].numero = 1;
    //grille.cellules[curseur.y][curseur.x].chiffre = 1;






    while (true) {
        afficher_grille(&grille, curseur);

        printf("\nUse ZQSD (or WASD) to move. Press 'x' to quit.\n");
        printf("Input: ");

        char input = _getch();
        printf("%c\n", input);

        if (input == 'x' || input == 'X')
            break;

        deplacer_curseur(&curseur, &grille, input);
        if (a_gagne(&curseur, &grille)){
            break;
        }
    }
    for (int i = 0; i < taille; i++)
        free(visited[i]);
    free(visited);
    free(path);

    return 0;
}
