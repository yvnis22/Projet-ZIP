#include "grille.h"
#include "sauvegarde.h" 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "refresh.h"

int hamiltonien_boucle(int path, time_t start_time, double time_limit);

/*
================================================================================
Fonction   : main
Auteur     : Anouk, Emilien, Noah, Yanis, London
Param      : Aucun
Traitement : Point d'entrée. Boucle principale qui gère le retour au menu.
Retour     : int - Code de sortie (0).
================================================================================
*/
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    srand(time(NULL));
    
    // Variable pour maintenir le programme ouvert tant qu'on ne choisit pas "Quitter"
    bool programme_en_cours = true; 

    while (programme_en_cours) {
        Grille grille;
        Position curseur;
        int depart_x, depart_y;
        char choix_menu = '0'; // Réinitialisation
        bool partie_chargee = false;

        // --- MENU INITIAL ---
        bool input_correct = false;
        while (!input_correct) {
            system("cls"); 
            
            // Affichage de l'ASCII Art 
            printf("  ▀▀                     ▀▀        \n");
            printf("  ██ ▄█▀█▄ ██ ██   ▀▀▀██ ██  ████▄ \n");
            printf("  ██ ██▄█▀ ██ ██     ▄█▀ ██  ██ ██ \n");
            printf("  ██ ▀█▄▄▄ ▀██▀█   ▄██▄▄ ██  ████▀ \n");
            printf("  ██                         ██  \n");
            printf("▀▀▀                          ▀▀ \n");
            printf("\n\n");
            printf("-------------------------------\n");
            printf("      1. Nouvelle Partie       \n");
            printf("      2. Continuer Partie      \n");
            printf("      3. Quitter le Jeu        \n"); 
            printf("-------------------------------\n");
            printf("Choix : ");

            choix_menu = _getch();
            if (choix_menu == '1' || choix_menu == '2' || choix_menu == '3') {
                input_correct = true;
            }
        }

        // --- GESTION DE LA SORTIE DEFINITIVE ---
        if (choix_menu == '3') {
            programme_en_cours = false;
            printf("\nAu revoir !\n");
            break; // Sort de la boucle principale et ferme le programme
        }

        // --- GESTION DU CHARGEMENT ---
        if (choix_menu == '2') {
            if (charger_partie(&grille, &curseur, "sauvegarde.txt")) {
                printf("\nPartie chargee avec succes !\n");
                partie_chargee = true;
                system("pause"); 
            } else {
                printf("\nAucune sauvegarde trouvee ou erreur. Retour au menu...\n");
                system("pause");
                continue; // Revient au début de la boucle while (au menu)
            }
        }

        // --- INITIALISATION (Si nouvelle partie) ---
        if (!partie_chargee) {
            system("cls");
            int taille, nb_numeros;

            printf("--- Configuration Nouvelle Partie ---\n");

            // Saisie de la TAILLE
            printf("\nTaille de la grille (5-10) [defaut 5]: ");
            if (scanf("%d", &taille) != 1) {
                taille = 5; 
                while (getchar() != '\n'); 
            } 
            else if (taille < TAILLE_MIN || taille > TAILLE_MAX) {
                taille = 5; 
            }

            // Saisie du NOMBRE DE NUMEROS
            printf("\nNombre de numeros (1-12) [defaut 5]: ");
            if (scanf("%d", &nb_numeros) != 1) {
                nb_numeros = 5;
                while (getchar() != '\n'); 
            } 
            else if (nb_numeros < 1 || nb_numeros > NB_NUMEROS_MAX) {
                nb_numeros = 5;
            }

            // Allocation et génération du chemin hamiltonien
            int **visited = (int**) malloc(taille * sizeof(int *));
            for (int i = 0; i < taille; i++) {
                visited[i] = (int*)malloc(taille * sizeof(int));
                for (int j = 0; j < taille; j++) visited[i][j] = 0;
            }

            initialiser_grille(&grille, taille, taille);
            int trouve = 0;

            printf("\nGeneration du niveau en cours...\n"); // feedback visuel

            while (!trouve) {
                for (int i = 0; i < taille; i++)
                    for (int j = 0; j < taille; j++)
                        visited[i][j] = 0;

                curseur = depart_aleatoire(&depart_x, &depart_y, taille);
                clock_t start_check = clock();
                
                if (hamiltonien(depart_x, depart_y, 1, taille, visited, start_check, 0.9)) {
                    trouve = 1; 
                }
            }

            placer_numeros_sur_chemin(&grille, visited, taille, nb_numeros);

            for (int i = 0; i < taille; i++) {
                for (int j = 0; j < taille; j++) {
                    if (grille.cellules[i][j].chiffre == 1) {
                        curseur.x = j; curseur.y = i;
                        curseur.chiffre_actuel = 1;
                        grille.cellules[i][j].numero = 1;
                    }
                }
            }
            for (int i = 0; i < taille; i++) free(visited[i]);
            free(visited);
        }

        // --- BOUCLE DE JEU ---
        cacher_curseur();
        system("cls");

        bool retour_menu = false; // Flag pour sortir de la boucle de jeu proprement

        while (!retour_menu) {
            gotoxy(0, 0);
            afficher_grille(&grille, curseur);

            printf("\nflèches directionnelles : Bouger | B : Sauvegarder & Menu | X : Menu Principal\n");

            char input = _getch();

            // CAS 'X' : Retour Menu sans sauvegarder
            if (input == 'x' || input == 'X') {
                retour_menu = true; // Casse la boucle de jeu, mais pas la boucle programme
            }

            // CAS 'B' : Sauvegarder et Retour Menu
            else if (input == 'b' || input == 'B') {
                sauvegarder_partie(&grille, &curseur, "sauvegarde.txt");
                printf("\nPartie sauvegardee. Appuyez sur une touche pour revenir au menu.");
                _getch();
                retour_menu = true;
            }
            else {
                deplacer_curseur(&curseur, &grille, input);

                // CAS VICTOIRE
                if (a_gagne(&curseur, &grille)) {
                    system("cls");
                    afficher_grille(&grille, curseur); // Affiche la grille complète une dernière fois
                    printf("\n\nBRAVO ! VOUS AVEZ GAGNE !\n");
                    printf("1. Retourner au Menu Principal\n");
                    printf("2. Quitter le jeu\n");
                    printf("Choix : ");
                    
                    char choix_fin;
                    do {
                        choix_fin = _getch();
                    } while (choix_fin != '1' && choix_fin != '2');

                    if (choix_fin == '2') {
                        programme_en_cours = false; // Arrête tout le programme
                    }
                    // Si choix_fin == '1', on ne fait rien, retour_menu devient true juste après
                    retour_menu = true;
                }
            }
        }
        // Fin de la boucle de jeu, on remonte au début du 'while (programme_en_cours)' -> Menu
    }

    return 0;
}