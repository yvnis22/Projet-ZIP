#ifndef GRILLE_H
#define GRILLE_H

#include <stdbool.h>

// Definition des constantes pour la taille minimale et maximale de la grille ainsi que le nombre maximum de numeros
// -- Noah

#define TAILLE_MIN 5
#define TAILLE_MAX 10
#define NB_NUMEROS_MAX 12

// Definition des structures utilisees dans le jeu
// -- Noah
typedef struct {
    int numero;
    
} Case;

typedef struct {
    int lignes;
    int colonnes;
    Case cellules[TAILLE_MAX][TAILLE_MAX];
} Grille;

typedef struct {
    int x;
    int y;
} Position;

// Declaration des fonctions utilisees dans le jeu
// -- Noah

void afficher_grille(Grille *grille, Position curseur);
void initialiser_grille(Grille* grille, int lignes, int colonnes);
void deplacer_curseur(Position *curseur, Grille *grille, char touche);

// headers assez simple, faut juste reussir a naviguer entre les * ou les & ce que je galere encore

void afficher_grille(Grille *grille, Position curseur);
void initialiser_grille(Grille* grille, int lignes, int colonnes);
void deplacer_curseur(Position *curseur, Grille *grille, char touche);

// headers assez simple, faut juste reussir a naviguer entre les * ou les & ce que je galere encore

#endif   