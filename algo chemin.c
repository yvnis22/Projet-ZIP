#include "grille.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>


/*
================================================================================
Fonction   : depart_aleatoire
Auteur     : Anouk
Param      : x (int*) - Pointeur pour stocker l'abscisse générée
             y (int*) - Pointeur pour stocker l'ordonnée générée
             taille_grille (int) - Dimension de la grille carrée
Traitement : Génère des coordonnées aléatoires et vérifie la parité pour 
             assurer la faisabilité d'un chemin hamiltonien sur grille impaire.
Retour     : Position - La position de départ générée.
================================================================================
*/
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



/*
================================================================================
Fonction   : afficher
Auteur     : Anouk
Param      : visited (int**) - Tableau 2D des passages
             taille (int) - Dimension de la grille
Traitement : Affiche la matrice des passages pour le débogage de l'algorithme.
Retour     : Aucun (void)
================================================================================
*/
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

/*
================================================================================
Fonction   : est_valide
Auteur     : Anouk
Param      : x (int) - Coordonnée X à tester
             y (int) - Coordonnée Y à tester
             grille (int) - Taille de la grille
             visite (int**) - Tableau des cases déjà visitées
Traitement : Vérifie si la case est dans les limites et n'a pas encore été visitée.
Retour     : bool - true si la case est accessible, false sinon.
================================================================================
*/
bool est_valide(int x, int y, int grille, int **visite)
{
    return x >= 0 && x < grille && y >= 0 && y < grille && !(visite[x][y]);
}

int directionsx[4] = {0, 1, 0, -1};
int directionsy[4] = {-1, 0, 1, 0};

/*
================================================================================
Fonction   : hamiltonien
Auteur     : Anouk
Param      : ligne (int) - Ligne actuelle
             colonne (int) - Colonne actuelle
             pas (int) - Nombre de cases déjà visitées
             taille_grille (int) - Dimension de la grille
             visite (int**) - Tableau de suivi du chemin
Traitement : Explore récursivement toutes les directions pour trouver un 
             chemin passant par chaque case une et une seule fois.
Retour     : bool - true si un chemin complet est trouvé.
================================================================================
*/
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

/*
================================================================================
Fonction   : placer_numeros_sur_chemin
Auteur     : Anouk
Param      : grille (Grille*) - Pointeur vers la structure de jeu
             visited (int**) - Résultat de l'algorithme hamiltonien
             taille (int) - Taille de la grille
             nb_numeros (int) - Nombre de chiffres "indices" à placer
Traitement : Extrait le chemin ordonné, calcule un espacement régulier avec
             une part d'aléa, et place les chiffres indices sur la grille.
Retour     : Aucun (void)
================================================================================
*/
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