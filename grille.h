#ifndef GRILLE_H
#define GRILLE_H

#include <stdbool.h>

#define TAILLE_MIN 5
#define TAILLE_MAX 10
#define NB_NUMEROS_MAX 12

typedef struct {
    int numero; // un sorte de booleen, si il est a 0 c une case pas visité et si il est a un numero
    // decroissant par rapport auc curseur il est visité
    int chiffre; //si c'est un chiffre preset donc toute les valeurs 0<x<12 ou 0 si ce n'est pas un chiffre preset
} Case;

typedef struct {
    int lignes;
    int colonnes;
    Case cellules[TAILLE_MAX][TAILLE_MAX];
    // position grille
} Grille;

typedef struct {
    int x;
    int y;
    int chiffre_actuel; // permet de savoir a quel chiffre on est

} Position;

typedef struct {
    int x, y;
} Point;

typedef struct {
    int lignes;
    int colonnes;
    int nb_presets;
    const int (*presets)[TAILLE_MAX][TAILLE_MAX];
} GrillePresetInfo;

/*
Affiche la grille dans la console avec le curseur et les chiffres.
*/
void afficher_grille(Grille *grille, Position curseur);

/*
Initialise les structures de la grille avec des valeurs par défaut.
*/
void initialiser_grille(Grille* grille, int lignes, int colonnes);

/*
Gère la logique de déplacement du curseur et les règles de remplissage.
*/
void deplacer_curseur(Position *curseur, Grille *grille, char touche);

/*
Vérifie si une coordonnée est dans les limites et non visitée.
*/
bool est_valide(int x, int y, int taille_grille, int **visite);

/*
Retourne la position initiale codée en dur pour le début du jeu.
*/
Position get_pos1();

/*
Génère une position de départ aléatoire valide sur la grille.
*/
Position depart_aleatoire(int *x, int *y, int taille_grille);

/*
Algorithme de recherche de chemin hamiltonien par récursion.
*/
bool hamiltonien(int x, int y, int pas, int taille_grille, int **visite);

/*
Vérifie si toutes les cases de la grille ont été remplies.
*/
bool a_gagne(Position *curseur, Grille *grille);

/*
Affiche l'état numérique du tableau de visite (debug).
*/
void aff(int** visited, int taille) ;

/*
Répartit les points de passage (numéros) le long du chemin généré.
*/
void placer_numeros_sur_chemin(Grille *grille, int **visited, int taille, int nb_numeros);

#endif