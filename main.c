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
Auteur     : Équipe
Param      : Aucun
Traitement : Point d'entrée du programme. Gère le menu, l'initialisation de
             la partie (nouvelle ou chargée), la génération du niveau et
             la boucle principale de jeu (inputs et affichage).
Retour     : int - Code de sortie (0).
================================================================================
*/
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    srand(time(NULL));
    
    Grille grille;
    Position curseur;
    int depart_x, depart_y, taille, nb_numeros;
    char choix_menu;
    bool partie_chargee = false;

    // --- 1. MENU INITIAL ---
    bool input_correct = false;
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

    // --- 3. INITIALISATION (Si nouvelle partie) ---
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

        // Boucle de génération avec timeout
        while (!trouve) {
            // Remise à zéro de la matrice visited
            for (int i = 0; i < taille; i++)
                for (int j = 0; j < taille; j++)
                    visited[i][j] = 0;

            // Nouveau départ aléatoire
            curseur = depart_aleatoire(&depart_x, &depart_y, taille);

            // Lancement de l'algo avec TIMEOUT LOCAL (0.9s)
            clock_t start_check = clock();
            
            if (hamiltonien(depart_x, depart_y, 1, taille, visited, start_check, 0.9)) {
                trouve = 1; 
            }
        }

        placer_numeros_sur_chemin(&grille, visited, taille, nb_numeros);

        // Trouver le '1' pour placer le curseur initial
        for (int i = 0; i < taille; i++) {
            for (int j = 0; j < taille; j++) {
                if (grille.cellules[i][j].chiffre == 1) {
                    curseur.x = j; curseur.y = i;
                    curseur.chiffre_actuel = 1;
                    grille.cellules[i][j].numero = 1;
                }
            }
        }

        // Nettoyage mémoire de génération
        for (int i = 0; i < taille; i++) free(visited[i]);
        free(visited);
    }
    
    // --- 4. BOUCLE DE JEU ---
    cacher_curseur();
    system("cls");

    while (true) {
        gotoxy(0, 0);

        afficher_grille(&grille, curseur);

        printf("ZQSD : Bouger | B : Sauvegarder & Quitter | X : Quitter sans sauvegarder      \n");

        char input = _getch();

        if (input == 'x' || input == 'X')
            break;

        if (input == 'b' || input == 'B') {
            sauvegarder_partie(&grille, &curseur, "sauvegarde.txt");
            _getch();
            break;
        }

        deplacer_curseur(&curseur, &grille, input);

        if (a_gagne(&curseur, &grille)) {
            _getch();
            break;
        }
    }

    return 0;
}