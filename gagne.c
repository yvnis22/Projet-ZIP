#include "grille.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>



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