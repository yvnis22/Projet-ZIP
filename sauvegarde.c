#include "sauvegarde.h"
#include <stdio.h>
#include <stdlib.h>


/*
================================================================================
Fonction   : sauvegarder_partie
Auteur     : Emilien et Yanis
Param      : grille (Grille*) - Pointeur vers la grille
             curseur (Position*) - Pointeur vers la position
             nom_fichier (char*) - Destination
Traitement : Écrit les dimensions, la position du curseur, puis l'état de 
             chaque cellule (numéro et chiffre) dans un fichier texte.
Retour     : Aucun (void)
================================================================================
*/
void sauvegarder_partie(Grille *grille, Position *curseur, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");
/*    if (fichier == NULL) {
        printf("Erreur : Impossible de creer le fichier de sauvegarde.\n");
        return;
    }*/

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
    printf("Partie sauvegardee avec succes !\n");
}


/*
================================================================================
Fonction   : charger_partie
Auteur     : Emilien et Yanis
Param      : grille (Grille*) - Pointeur pour les données chargées
             curseur (Position*) - Pointeur pour la position chargée
             nom_fichier (char*) - Fichier source
Traitement : Ouvre le fichier en lecture, lit les dimensions, le curseur et 
             remplit la grille cellule par cellule.
Retour     : bool - true si le chargement a réussi, false sinon.
================================================================================
*/
bool charger_partie(Grille *grille, Position *curseur, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    // 1. Lire les dimensions
    if (fscanf(fichier, "%d %d", &grille->lignes, &grille->colonnes) != 2) {
        fclose(fichier); 
        return false;
    }

    // 2. Lire le curseur
    if (fscanf(fichier, "%d %d %d", &curseur->x, &curseur->y, &curseur->chiffre_actuel) != 3) {
        fclose(fichier); 
        return false;
    }

    // 3. Lire la grille
    for (int i = 0; i < grille->lignes; i++) {
        for (int j = 0; j < grille->colonnes; j++) {
            int num, chif;
            if (fscanf(fichier, "%d %d", &num, &chif) != 2) {
                fclose(fichier); 
                return false;
            }
            grille->cellules[i][j].numero = num;
            grille->cellules[i][j].chiffre = chif;
        }
    }

    fclose(fichier);
    return true;
}