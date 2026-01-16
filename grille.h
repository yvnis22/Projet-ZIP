#ifndef GRILLE_H
#define GRILLE_H

#include <stdbool.h>
#include <time.h>

#define TAILLE_MIN 5
#define TAILLE_MAX 10
#define NB_NUMEROS_MAX 12
#define TIME_LIMIT_SECONDS 1


// Codes de couleur ANSI pour le dégradé

#define RESET   "\033[0m"
// BLEU - Début du dégradé
#define b1  "\e[48;5;17m"  // Bleu très foncé
#define b2  "\e[48;5;18m"  // Bleu foncé
#define b3  "\e[48;5;19m"  // Bleu marine
#define b4  "\e[48;5;20m"  // Bleu
#define b5  "\e[48;5;21m"  // Bleu roi

// CYAN/TURQUOISE - Transition
#define c1  "\e[48;5;27m"  // Bleu vif
#define c2  "\e[48;5;33m"  // Cyan foncé
#define c3  "\e[48;5;39m"  // Cyan
#define c4  "\e[48;5;45m"  // Cyan clair
#define c5  "\e[48;5;51m"  // Cyan très clair

// VERT - Milieu
#define v1  "\e[48;5;40m"  // Vert foncé
#define v2  "\e[48;5;46m"  // Vert lime
#define v3  "\e[48;5;82m"  // Vert vif
#define v4  "\e[48;5;118m" // Vert clair
#define v5  "\e[48;5;154m" // Vert lime clair

// JAUNE - Transition
#define j1  "\e[48;5;190m" // Jaune-vert
#define j2  "\e[48;5;226m" // Jaune vif
#define j3  "\e[48;5;220m" // Jaune or
#define j4  "\e[48;5;214m" // Jaune-orange
#define j5  "\e[48;5;208m" // Orange clair

// ORANGE
#define o1  "\e[48;5;202m" // Orange
#define o2  "\e[48;5;196m" // Orange-rouge
#define o3  "\e[48;5;160m" // Rouge-orange
#define o4  "\e[48;5;124m" // Rouge foncé
#define o5  "\e[48;5;88m"  // Rouge bordeaux

#define ro "\e[38;5;205m" // ROSE_VIF (texte pour les chiffres)



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
Affiche la grille de jeu dans la console avec la position actuelle du curseur et les couleurs.
 */
void afficher_grille(Grille *grille, Position curseur);

/*
Initialise une grille avec les dimensions spécifiées et met toutes les cases à zéro.
 */
void  initialiser_grille(Grille* grille, int lignes, int colonnes);

/*
Gère le déplacement du curseur en fonction de la touche saisie et applique les règles du jeu.
 */
void deplacer_curseur(Position *curseur, Grille *grille, char touche);

/*
Vérifie si les coordonnées sont dans la grille et si la case n'a pas encore été visitée.
 */
bool est_valide(int x, int y, int taille_grille, int **visite);

/*
Génère une position de départ aléatoire respectant les contraintes de parité pour le chemin hamiltonien.
 */
Position depart_aleatoire(int *x, int *y, int taille_grille);

/*
Algorithme récursif qui tente de trouver un chemin hamiltonien dans la grille avec une limite de temps.
 */
int hamiltonien(int x, int y, int pas, int taille_grille, int **visite, clock_t debut_temps, double limite_temps);

/*
Vérifie si le joueur a gagné en parcourant toutes les cases de la grille.
 */
bool a_gagne(Position *curseur, Grille *grille);

/*
Place les numéros (objectifs) sur la grille en suivant le chemin hamiltonien généré.
 */
void placer_numeros_sur_chemin(Grille *grille, int **visited, int taille, int nb_numeros);

/*
Gère la boucle de tentatives pour trouver un chemin hamiltonien valide dans le temps imparti.
 */
int hamiltonien_boucle(int hamiltonien_resultat, time_t TIME, double TIME_LIMIT);

#endif
