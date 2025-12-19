#include "grille.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>



Position depart_aleatoire(int *x, int *y, int taille_grille)
{
    while (true) {
        *x = rand() % taille_grille;
        *y = rand() % taille_grille;

        if (taille_grille*taille_grille % 2 == 1 && ((*x + *y) % 2 == 1)) {
            continue;
        }

        Position p = { *x, *y, 1 };
        return p;
    }
}




void aff(int** visited, int taille)
{
    for (int i=0; i<taille; i++)
    {
        for (int j=0; j<taille; j++)
        {
            printf ("%d ", visited[i][j]) ;
        }
        printf ("\n") ;
    }
}

bool est_valide(int x, int y, int grille, int **visite)
{
    return x >= 0 && x < grille && y >= 0 && y < grille && !(visite[x][y]);
}

int directionsx[4] = {0, 1, 0, -1};
int directionsy[4] = {-1, 0, 1, 0};

bool hamiltonien(int ligne, int colonne, int pas, int taille_grille, int **visite){
    // on commence par dire que la premiere case ou on est est deja visite
    visite[ligne][colonne] = pas;

    // si toutes les cases sont visites alors tout va bien
    if (pas == taille_grille * taille_grille){
        printf("trouve %d\n", pas );
        return true;
    }
    // on teste toutes les directions
    for (int i = 0; i < 4; i++){

        // cela nosu permet de changer de case sur la grille
        int new_l = ligne    + directionsx[i];
        int new_c = colonne + directionsy[i];
        // si le mouvement n'est pas out of bound ou n'est pas sur une case visite
        if (est_valide(new_l, new_c, taille_grille, visite)){

            // recursion : on teste avec pas plus un qui nous permet d'increm
            if (hamiltonien(new_l, new_c, pas + 1, taille_grille, visite))

                return true;
        }
    }



    visite[ligne][colonne] = 0;
    return false;
}


void placer_numeros_sur_chemin(Grille *grille, int **visited, int taille, int nb_numeros) {
    if (nb_numeros <= 0) return;
    
    int total_cases = taille * taille;
    
    // Calculer l'espacement approximatif entre les numéros
    // On veut répartir nb_numeros sur total_cases cases
    int espacement_base = total_cases / nb_numeros;
    
    // Créer un tableau pour stocker les positions (x, y) dans l'ordre du chemin
    typedef struct {
        int x, y;
    } coordonees;
    coordonees *chemin = (coordonees*)malloc(total_cases * sizeof(coordonees));
    
    // Remplir le tableau en trouvant chaque case dans l'ordre 1, 2, 3...
    for (int pas = 1; pas <= total_cases; pas++) {
        for (int i = 0; i < taille; i++) {
            for (int j = 0; j < taille; j++) {
                if (visited[i][j] == pas) {
                    chemin[pas-1].x = j;
                    chemin[pas-1].y = i;
                }
            }
        }
    }
    
    // Placer les numéros avec un peu de variation aléatoire
    for (int num = 1; num <= nb_numeros; num++) {
        int position;
        
        if (num == 1) {
            // Le premier numéro au début
            position = 0;
        } else if (num == nb_numeros) {
            // Le dernier numéro à la fin
            position = total_cases - 1;
        } else {
            // Les autres numéros répartis avec variation aléatoire
            int position_ideale = (num - 1) * espacement_base;
            // Ajouter une variation de ±20% pour éviter qu'ils soient trop réguliers
            int variation = espacement_base / 5;
            position = position_ideale + (rand() % (2 * variation + 1)) - variation;
            
            // S'assurer qu'on reste dans les limites
            if (position < num - 1) position = num - 1;
            if (position >= total_cases) position = total_cases - 1;
        }
        
        int x = chemin[position].x;
        int y = chemin[position].y;
        
        grille->cellules[y][x].chiffre = num;
    }
    
    free(chemin);
}

