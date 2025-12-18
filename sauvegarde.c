#include "sauvegarde.h"
#include <stdio.h>
#include <stdlib.h>

void sauvegarder_partie(Grille *grille, Position *curseur, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur : Impossible de creer le fichier de sauvegarde.\n");
        return;
    }

    // 1. Sauvegarder les dimensions
    fprintf(fichier, "%d %d\n", grille->lignes, grille->colonnes);

    // 2. Sauvegarder le curseur (x, y, chiffre_actuel)
    fprintf(fichier, "%d %d %d\n", curseur->x, curseur->y, curseur->chiffre_actuel);

    // 3. Sauvegarder chaque case de la grille
    for (int i = 0; i < grille->lignes; i++) {
        for (int j = 0; j < grille->colonnes; j++) {
            // On sauvegarde le 'numero' (passage) et le 'chiffre' (preset)
            fprintf(fichier, "%d %d ", grille->cellules[i][j].numero, grille->cellules[i][j].chiffre);
        }
        fprintf(fichier, "\n"); // Saut de ligne pour lisibilité dans le fichier txt
    }

    fclose(fichier);
    printf("Partie sauvegardee avec succes dans '%s' !\n", nom_fichier);
}

bool charger_partie(Grille *grille, Position *curseur, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        return false; // Le fichier n'existe pas
    }

    // 1. Lire les dimensions
    if (fscanf(fichier, "%d %d", &grille->lignes, &grille->colonnes) != 2) {
        fclose(fichier); return false;
    }

    // 2. Lire le curseur
    if (fscanf(fichier, "%d %d %d", &curseur->x, &curseur->y, &curseur->chiffre_actuel) != 3) {
        fclose(fichier); return false;
    }

    // 3. Lire la grille
    for (int i = 0; i < grille->lignes; i++) {
        for (int j = 0; j < grille->colonnes; j++) {
            int num, chif;
            if (fscanf(fichier, "%d %d", &num, &chif) != 2) {
                fclose(fichier); return false;
            }
            grille->cellules[i][j].numero = num;
            grille->cellules[i][j].chiffre = chif;
        }
    }

    fclose(fichier);
    return true;
}