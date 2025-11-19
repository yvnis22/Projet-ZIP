#ifndef GRILLE_H
#define GRILLE_H

#include <stdbool.h>

#define TAILLE_MIN 5
#define TAILLE_MAX 10
#define NB_NUMEROS_MAX 12

typedef struct {
    int numero;
    bool visite;
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

typedef struct {
    int lignes;
    int colonnes;
    int nb_presets;
    const int (*presets)[TAILLE_MAX][TAILLE_MAX];
} GrillePresetInfo;

void initialiser_grille(Grille* grille, int lignes, int colonnes);
void deplacer_curseur(Position *curseur, int lignes, int colonnes, char touche);
#endif   