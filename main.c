#include "grille.h"
#include "sauvegarde.h" 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // Pour _getch() sous Windows

/*
================================================================================
FONCTION   : main
AUTEURS    : Noah et Anouk
TRAITEMENT : Point d'entrée du programme. Gère le menu principal, l'initialisation 
             de la grille (nouvelle partie ou chargement) et la boucle de jeu 
             principale incluant les déplacements et la sauvegarde.
RETOUR     : int (0 pour succès)
================================================================================
*/
int main() {
    // --- INITIALISATION DES VARIABLES ---
    Grille grille;
    Position curseur;
    srand(time(NULL));

    int depart_x, depart_y;
    char choix_menu;
    bool partie_chargee = false;
    bool input_correct = false;


    // --- 1. MENU PRINCIPAL ---
    while (!input_correct) {
        system("cls"); 
        
        printf("=== JEU ZIP ===\n");
        printf("1. Nouvelle Partie\n");
        printf("2. Continuer la partie precedente\n");
        printf("Choix : ");

        choix_menu = _getch();
        if (choix_menu == '1' || choix_menu == '2') {
            input_correct = true;
        }
    }
    printf("%c\n", choix_menu);


    // --- 2. GESTION DU CHARGEMENT ---
    if (choix_menu == '2') {
        if (charger_partie(&grille, &curseur, "sauvegarde.txt")) {
            printf("Partie chargee !\n");
            partie_chargee = true;
            system("pause"); 
        } else {
            printf("Aucune sauvegarde trouvee ou erreur de lecture. Demarrage d'une nouvelle partie...\n");
            system("pause");
        }
    }


    // --- 3. CONFIGURATION NOUVELLE PARTIE ---
    // Si on a choisi Nouvelle Partie OU si le chargement a échoué
    if (!partie_chargee) {
        system("cls");
        int taille, nb_numeros;

        printf("--- Configuration Nouvelle Partie ---\n");

        // Saisie de la TAILLE
        printf("\nTaille de la grille (5-12) [defaut 5]: ");
        if (scanf("%d", &taille) != 1) {
            taille = 5; 
            while (getchar() != '\n'); 
        } 
        else if (taille < TAILLE_MIN || taille > TAILLE_MAX) {
            taille = 5; 
        }

        // Saisie du NOMBRE DE NUMEROS
        printf("\nNombre de numeros (1-10) [defaut 5]: ");
        if (scanf("%d", &nb_numeros) != 1) {
            nb_numeros = 5;
            while (getchar() != '\n'); 
        } 
        else if (nb_numeros < 1 || nb_numeros > NB_NUMEROS_MAX) {
            nb_numeros = 5;
        }

        // --- ALLOCATION ET GENERATION DU CHEMIN ---
        int **visited = (int**) malloc(taille * sizeof(int *));
        for (int i = 0; i < taille; i++) {
            visited[i] = (int*)malloc(taille * sizeof(int));
            for (int j = 0; j < taille; j++) {
                visited[i][j] = 0;
            }
        }

        int **path = (int**)malloc(taille * taille * sizeof (int*));
        for (int i = 0; i < taille; i++) {
            path[i] = (int*)malloc(2 * sizeof (int));
        }

        // Initialisation de la structure de jeu
        curseur = depart_aleatoire(&depart_x, &depart_y, taille);

        initialiser_grille(&grille, taille, taille);
        hamiltonien(depart_x, depart_y, 1, taille, visited);
        aff(visited, taille);
    
        // Placement des numéros cibles
        placer_numeros_sur_chemin(&grille, visited, taille, nb_numeros);

        // Positionnement initial du curseur sur le chiffre 1
        for (int i = 0; i < taille; i++) {
            for (int j = 0; j < taille; j++) {
                if (grille.cellules[i][j].chiffre == 1) {
                    curseur.x = j;
                    curseur.y = i;
                    curseur.chiffre_actuel = 1;
                    grille.cellules[i][j].numero = 1;
                }
            }
        }
    }


    // --- 4. BOUCLE DE JEU PRINCIPALE ---
    while (true) {
        system("cls"); // Optionnel : pour rafraîchir l'affichage proprement
        afficher_grille(&grille, curseur);

        printf("\nZ/Q/S/D : Deplacer | B : Sauvegarder & Quitter | X : Quitter sans sauver\n");

        char input = _getch();

        // Action : QUITTER
        if (input == 'x' || input == 'X') {
            break;
        }

        // Action : SAUVEGARDER
        if (input == 'b' || input == 'B') {
            sauvegarder_partie(&grille, &curseur, "sauvegarde.txt");
            printf("A bientot !\n");
            break;
        }

        // Action : MOUVEMENT
        deplacer_curseur(&curseur, &grille, input);

        // Vérification VICTOIRE
        if (a_gagne(&curseur, &grille)) {
            system("pause");
            break;
        }
    }

    return 0;
}