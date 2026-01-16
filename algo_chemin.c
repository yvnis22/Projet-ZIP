#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "grille.h"

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
Position depart_aleatoire(int *x, int *y, int taille_grille) {
    while (true) {
        *x = rand() % taille_grille;
        *y = rand() % taille_grille;
        
        if (taille_grille * taille_grille % 2 == 1 && ((*x + *y) % 2 == 1)) {
            continue;
        }

        Position p = { *x, *y, 1 };
        return p;
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
bool est_valide(int x, int y, int grille, int **visite) {
    return x >= 0 && x < grille && y >= 0 && y < grille && !(visite[x][y]);
}

// Directions pour se déplacer dans la grille
int directionsx[4] = {0, 1, 0, -1};
int directionsy[4] = {-1, 0, 1, 0};

/*
================================================================================
Fonction   : hamiltonien
Auteur     : Anouk
Param      : ligne, colonne (int) - Coordonnées actuelles
             pas (int) - Étape actuelle dans le chemin (1 à N*N)
             taille_grille (int) - Taille de la grille
             visite (int**) - Matrice de suivi du chemin
             debut_temps (clock_t) - Temps de départ pour le timeout
             limite_temps (double) - Durée max autorisée en secondes
Traitement : Algorithme récursif (backtracking) pour trouver un chemin 
             hamiltonien passant par toutes les cases. Inclut une sécurité 
             temporelle pour éviter les blocages sur les grandes grilles.
Retour     : int - 1 si un chemin est trouvé, 0 sinon.
================================================================================
*/
int hamiltonien(int ligne, int colonne, int pas, int taille_grille, int **visite, clock_t debut_temps, double limite_temps) {
    
    // Vérification du timeout
    double temps_ecoule = (double)(clock() - debut_temps) / CLOCKS_PER_SEC;
    if (temps_ecoule > limite_temps) {
        return 0; 
    }
   
    visite[ligne][colonne] = pas;

    // Condition d'arrêt : Chemin complet trouvé
    if (pas == taille_grille * taille_grille) {
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        int new_l = ligne + directionsx[i];
        int new_c = colonne + directionsy[i];

        if (est_valide(new_l, new_c, taille_grille, visite)) {
            if (hamiltonien(new_l, new_c, pas + 1, taille_grille, visite, debut_temps, limite_temps)) {
                return 1;
            }
            
            // Vérification post-récursion pour arrêter proprement en cas de timeout
            if ((double)(clock() - debut_temps) / CLOCKS_PER_SEC > limite_temps) {
                visite[ligne][colonne] = 0; 
                return 0;
            }
        }
    }

    // Backtracking : on libère la case
    visite[ligne][colonne] = 0;
    return 0;
}

/*
================================================================================
Fonction   : placer_numeros_sur_chemin
Auteur     : Anouk / Équipe
Param      : grille (Grille*) - Grille à modifier
             visited (int**) - Le chemin hamiltonien généré
             taille (int) - Taille de la grille
             nb_numeros (int) - Nombre de chiffres presets à placer
Traitement : Répartit les chiffres (objectifs) le long du chemin généré
             avec une variation aléatoire pour éviter la linéarité parfaite.
Retour     : Aucun (void)
================================================================================
*/
void placer_numeros_sur_chemin(Grille *grille, int **visited, int taille, int nb_numeros) {
    if (nb_numeros <= 0) return;
    
    int total_cases = taille * taille;
    int espacement_base = total_cases / nb_numeros;
    
    typedef struct {
        int x, y;
    } coordonees;
    
    coordonees *chemin = (coordonees*)malloc(total_cases * sizeof(coordonees));
    
    // Reconstruction linéaire du chemin
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
    
    // Placement des numéros
    for (int num = 1; num <= nb_numeros; num++) {
        int position;
        
        if (num == 1) {
            position = 0;
        } else if (num == nb_numeros) {
            position = total_cases - 1;
        } else {
            // Calcul position avec bruit aléatoire
            int position_ideale = (num - 1) * espacement_base;
            int variation = espacement_base / 5;
            position = position_ideale + (rand() % (2 * variation + 1)) - variation;
            
            if (position < num - 1) position = num - 1;
            if (position >= total_cases) position = total_cases - 1;
        }
        
        int x = chemin[position].x;
        int y = chemin[position].y;
        
        grille->cellules[y][x].chiffre = num;
    }
    
    free(chemin);
}
