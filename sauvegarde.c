#include "sauvegarde.h"
#include <stdio.h>
#include <stdlib.h>

/*
Fonction   : sauvegarder_partie
Auteur     : Yanis & Emilien
Param      : grille (Grille*) - Pointeur vers la structure de la grille
             curseur (Position*) - Pointeur vers la position du joueur
             nom_fichier (char*) - Nom du fichier de sauvegarde
Traitement : Ouvre le fichier en écriture. Ecrit les dimensions, la position
             du curseur, puis l'état de chaque cellule (numéro et chiffre).
             Gère l'erreur d'ouverture de fichier.
Retour     : void
*/
void sauvegarder_partie(Grille *grille, Position *curseur, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");
    
    // Sécurité : on vérifie que le fichier est bien ouvert
    if (fichier == NULL) {
        printf("Erreur : Impossible de creer le fichier de sauvegarde %s.\n", nom_fichier);
        return;
    }

    // 1. Sauvegarder les dimensions
    fprintf(fichier, "%d %d\n", grille->lignes, grille->colonnes);

    // 2. Sauvegarder le curseur (x, y, chiffre_actuel)
    fprintf(fichier, "%d %d %d\n", curseur->x, curseur->y, curseur->chiffre_actuel);

    // 3. Sauvegarder chaque case de la grille
    for (int i = 0; i < grille->lignes; i++) {
        for (int j = 0; j < grille->colonnes; j++) {
            // On sauvegarde le 'numero' (passage) et le 'chiffre' (valeur)
            fprintf(fichier, "%d %d ", grille->cellules[i][j].numero, grille->cellules[i][j].chiffre);
        }
        fprintf(fichier, "\n"); // Saut de ligne pour la lisibilité
    }

    fclose(fichier);
    printf("Partie sauvegardee avec succes !\n");
}

/*
Fonction   : charger_partie
Auteur     : Emilien & Yanis
Param      : grille (Grille*) - Pointeur pour stocker les données
             curseur (Position*) - Pointeur pour stocker la position
             nom_fichier (char*) - Nom du fichier à lire
Traitement : Ouvre le fichier en lecture. Récupère les dimensions, le curseur
             et remplit la grille. Renvoie false si erreur.
Retour     : bool - true si succès, false sinon
*/
bool charger_partie(Grille *grille, Position *curseur, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    
    // Sécurité : le fichier existe-t-il ?
    if (fichier == NULL) {
        // Ce n'est pas forcément une erreur grave (ex: première partie), 
        // donc on ne fait pas de printf d'erreur ici, on renvoie juste false.
        return false; 
    }

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
