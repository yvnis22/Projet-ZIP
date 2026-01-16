#include "grille.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

/*
================================================================================
Fonction   : deplacer_curseur
Auteur     : Équipe
Param      : curseur (Position*) - Pointeur vers la position actuelle
             grille (Grille*) - Pointeur vers la grille de jeu
             touche (char) - Caractère saisi par l'utilisateur (z,q,s,d)
Traitement : Gère le déplacement du curseur en vérifiant les collisions,
             le backtracking (retour arrière) et la progression sur les
             chiffres prédéfinis.
Retour     : Aucun (void)
================================================================================
*/
void deplacer_curseur(Position *curseur, Grille *grille, char touche) {
    // Conservation des coordonnées actuelles avant validation
    int new_x = curseur->x;
    int new_y = curseur->y;

    // Gestion des inputs (Haut, Bas, Gauche, Droite)
    switch (touche) {
        case 'w': case 'W': case 'z': case 'Z': // Haut
            if (curseur->y > 0) new_y--;
            break;

        case 's': case 'S': // Bas
            if (curseur->y < grille->lignes - 1) new_y++;
            break;

        case 'a': case 'A': case 'q': case 'Q': // Gauche
            if (curseur->x > 0) new_x--;
            break;

        case 'd': case 'D': // Droite
            if (curseur->x < grille->colonnes - 1) new_x++;
            break;

        default:
            return;
    }

    // Vérification de sécurité des limites de la grille
    if (new_x < 0 || new_x >= grille->colonnes || new_y < 0 || new_y >= grille->lignes) {
        return;
    }

    // Récupération des numéros de passage (ordre de visite)
    int numero_actuel = grille->cellules[curseur->y][curseur->x].numero;
    int nv_numero = grille->cellules[new_y][new_x].numero;

    // --- CAS 1 : RETOUR EN ARRIÈRE (Backtracking) ---
    // On teste si la case cible a déjà été visitée
    if (nv_numero != 0) {
        // On vérifie si c'est exactement la case précédente
        if (nv_numero == numero_actuel - 1) {

            // Gestion de la décrémentation du "chiffre actuel" (preset)
            if (grille->cellules[curseur->y][curseur->x].chiffre == curseur->chiffre_actuel) {
                curseur->chiffre_actuel = curseur->chiffre_actuel - 1;
            } 
            else if (grille->cellules[curseur->y][curseur->x].chiffre == 1) {
                curseur->chiffre_actuel = 1;
            }

            // Remettre la case que l'on quitte à 0 (non visitée)
            grille->cellules[curseur->y][curseur->x].numero = 0;

            // Appliquer le déplacement
            curseur->x = new_x;
            curseur->y = new_y;

            return;
        }
    }

    // --- CAS 2 : DÉPLACEMENT NORMAL (Progression) ---
    // Vers une case vide ou un chiffre preset
    if (nv_numero == 0) {
        
        // Sous-cas A : La case contient un chiffre preset (ex: 2, 3, 4...)
        // On doit vérifier si c'est bien le chiffre suivant attendu
        if (grille->cellules[new_y][new_x].chiffre != 0 &&
            grille->cellules[new_y][new_x].chiffre == curseur->chiffre_actuel + 1) {
            
            curseur->x = new_x;
            curseur->y = new_y;
            
            // On marque la case comme visitée (incrément du numéro de passage)
            grille->cellules[new_y][new_x].numero = numero_actuel + 1;
            
            // Mise à jour du chiffre actuel du joueur
            curseur->chiffre_actuel = grille->cellules[curseur->y][curseur->x].chiffre;
        }
        
        // Sous-cas B : Cas spécial du retour au départ (chiffre 1)
        if (nv_numero == 1 && grille->cellules[new_y][new_x].chiffre == 1) {
            grille->cellules[curseur->y][curseur->x].numero = 0;
            curseur->x = new_x;
            curseur->y = new_y;
        }
        
        // Sous-cas C : La case est vide et sans preset
        else if (grille->cellules[new_y][new_x].chiffre == 0) {
            curseur->x = new_x;
            curseur->y = new_y;
            // On marque la visite
            grille->cellules[new_y][new_x].numero = numero_actuel + 1;
        }
    }
}