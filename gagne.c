#include "grille.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>


/*
================================================================================
Fonction   : a_gagne
Auteur     : Anouk
Param      : curseur (Position*) - Pointeur vers la position actuelle
             grille (Grille*) - Pointeur vers la grille de jeu
Traitement : Parcourt l'intégralité de la grille. Si une seule case possède
             un 'numero' égal à 0, la partie n'est pas finie.
Retour     : bool - true si toutes les cases sont visitées, false sinon.
================================================================================
*/
bool a_gagne(Position *curseur, Grille *grille){
    for ( int i = 0 ; i < grille->lignes ; i++ ){
        for ( int j = 0; j < grille->colonnes ; j++){
            if (grille->cellules[i][j].numero == 0 ){
                return false; 
            }
        }
    }
    printf("Fini !");
    return true;
}