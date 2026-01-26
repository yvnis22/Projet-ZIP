#include "grille.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

/*
================================================================================
Fonction   : initialiser_grille
Auteur     : Anouk
Param      : grille (Grille*) - Pointeur vers la structure à initialiser
             lignes (int) - Nombre de lignes souhaité
             colonnes (int) - Nombre de colonnes souhaité
Traitement : Définit les dimensions de la grille (bornées par MIN/MAX) et 
             initialise toutes les cellules à 0.
Retour     : Aucun (void)
================================================================================
*/
void initialiser_grille(Grille *grille, int lignes, int colonnes) {
    if (!grille) return;
    
    // Bornage des dimensions
    if (lignes < TAILLE_MIN) lignes = TAILLE_MIN;
    if (lignes > TAILLE_MAX) lignes = TAILLE_MAX;
    if (colonnes < TAILLE_MIN) colonnes = TAILLE_MIN;
    if (colonnes > TAILLE_MAX) colonnes = TAILLE_MAX;

    grille->lignes = lignes;
    grille->colonnes = colonnes;

    // Initialisation des données
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            grille->cellules[i][j].numero = 0;
            grille->cellules[i][j].chiffre = 0;
        }
    }
}

/*
================================================================================
Fonction   : afficher_grille
Auteur     : Anouk
Param      : grille (Grille*) - Pointeur vers la grille
             curseur (Position) - Position actuelle du joueur pour affichage
Traitement : Affiche la grille caractère par caractère en appliquant un 
             dégradé de couleurs ANSI basé sur la progression du chemin.
Retour     : Aucun (void)
================================================================================
*/
void afficher_grille(Grille *grille, Position curseur) {
    // Tableau de couleurs avec un dégradé fluide : ROUGE -> JAUNE -> VERT -> CYAN -> BLEU
    const char* couleurs[] = {
        o5, o4, o3, o2, o1,      
        j5, j4, j3, j2, j1,      
        v5, v4, v3, v2, v1,      
        c5, c4, c3, c2, c1,      
        b5, b4, b3, b2, b1       
    };
    int nb_couleurs = 25;
    int total_cases = grille->lignes * grille->colonnes;

    // Pré-calcul pour le mapping des couleurs (optionnel dans l'algo actuel mais conservé)
    int numero_par_chiffre[NB_NUMEROS_MAX + 1] = {0};
    for (int i = 0; i < grille->lignes; i++) {
        for (int j = 0; j < grille->colonnes; j++) {
            if (grille->cellules[i][j].chiffre != 0) {
                // Trouver le numéro qui devrait être à cette position
                // On doit chercher dans la solution hamiltonienne
                // Ici, on suppose que le numéro est stocké dans la cellule
                // On mappe le chiffre preset au numéro de case
                // On ajoute 1 pour que les numéros commencent à 1
                // et non à 0
                // Cela permet de colorer correctement les presets
                // basé sur leur position dans le chemin
                // Exemple : si le chiffre preset est 3 et qu'il est à la 10ème case
                // alors numero_par_chiffre[3] = 10
                // Cela sera utilisé plus tard pour colorer les presets
                // selon leur position dans le chemin
                numero_par_chiffre[grille->cellules[i][j].chiffre] = i * grille->colonnes + j + 1;
            }
        }
    }

    for (int i = 0; i < grille->lignes; i++) {
        for (int j = 0; j < grille->colonnes; j++) {
            int numero_case = grille->cellules[i][j].numero;

            // 1. Affichage du CURSEUR (X / Coeur)
            if (curseur.x == j && curseur.y == i) {
                int index_couleur = (numero_case - 1) * nb_couleurs / total_cases;
                if (index_couleur >= nb_couleurs) index_couleur = nb_couleurs - 1;
                if (index_couleur < 0) index_couleur = 0;

                printf("%s| ♥  |%s ", couleurs[index_couleur], RESET);
            }
            // 2. Affichage des cases VISITÉES (Chemin coloré)
            else if (numero_case != 0) {
                int index_couleur = (numero_case - 1) * nb_couleurs / total_cases;
                if (index_couleur >= nb_couleurs) index_couleur = nb_couleurs - 1;
                if (index_couleur < 0) index_couleur = 0;

                printf("%s|    |%s ", couleurs[index_couleur], RESET);
            }
            // 3. Affichage des CHIFFRES PRESETS (Objectifs)
            else if (grille->cellules[i][j].chiffre != 0) {
                int chiffre = grille->cellules[i][j].chiffre;

                // Si la case a été visitée (cas rare ici car géré par le if précédent, 
                // mais conservé pour robustesse d'affichage)
                if (grille->cellules[i][j].numero != 0) {
                    int max_chiffre = 0;
                    // Recherche du max pour calibrer la couleur
                    for (int pi = 0; pi < grille->lignes; pi++) {
                        for (int pj = 0; pj < grille->colonnes; pj++) {
                            if (grille->cellules[pi][pj].chiffre > max_chiffre) {
                                max_chiffre = grille->cellules[pi][pj].chiffre;
                            }
                        }
                    }

                    int numero_estime = (chiffre - 1) * total_cases / max_chiffre + 1;
                    int index_couleur = (numero_estime - 1) * nb_couleurs / total_cases;
                    if (index_couleur >= nb_couleurs) index_couleur = nb_couleurs - 1;
                    if (index_couleur < 0) index_couleur = 0;

                    if (chiffre < 10) printf("%s| %d  |%s ", couleurs[index_couleur], chiffre, RESET);
                    else printf("%s| %d |%s ", couleurs[index_couleur], chiffre, RESET);
                }
                // Affichage standard du chiffre (non visité) en rose
                else {
                    if (chiffre < 10) printf(ro "| %d  |" RESET " ", chiffre);
                    else printf(ro "| %d |" RESET " ", chiffre);
                }
            }
            // 4. Affichage des cases VIDES
            else {
                printf("|    | ");
            }
        }
        printf("\n");
    }
}