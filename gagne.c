#include "grille.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

/*
================================================================================
Fonction   : a_gagne
Auteur     : Anouk
Param      : curseur (Position*) - Position actuelle (non utilisé ici mais standard)
             grille (Grille*) - Pointeur vers la grille
Traitement : Parcourt toute la grille pour vérifier si toutes les cases ont 
             été visitées (numero != 0).
Retour     : bool - true si la grille est remplie, false sinon.
================================================================================
*/
bool a_gagne(Position *curseur, Grille *grille) {
    for (int i = 0; i < grille->lignes; i++) {
        for (int j = 0; j < grille->colonnes; j++) {
            // Si une seule case a le numéro 0, la partie n'est pas finie
            if (grille->cellules[i][j].numero == 0) {
                return false;
            }
        }
    }
    printf("Fini !");
    return true;
}