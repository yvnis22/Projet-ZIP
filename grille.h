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
    int numero; // un sorte de booleen, si = 0, c'est une case pas encore visité, et si = n > 0, 
    // permet d'identifier le chemin effectué par le curseur dans un ordre croissant.
    int chiffre; //soit un chiffre preset donc toute les valeurs 0 < x < 12 ou bien 0 si ce n'est pas un chiffre preset.
} Case;

typedef struct {
    int lignes;
    int colonnes;
    Case cellules[TAILLE_MAX][TAILLE_MAX];
} Grille;

typedef struct {
    int x;
    int y;
    int chiffre_actuel; // permet de savoir a quel chiffre on est  
} Position;


typedef struct {
    int lignes;
    int colonnes;
    int nb_presets;
    const int (*presets)[TAILLE_MAX][TAILLE_MAX];
} GrillePresetInfo;


void afficher_grille(Grille *grille, Position curseur);
void initialiser_grille(Grille* grille, int lignes, int colonnes);
void deplacer_curseur(Position *curseur, Grille *grille, char touche);


Position get_pos1();

bool a_gagne(Position *curseur, Grille *grille);


#endif   