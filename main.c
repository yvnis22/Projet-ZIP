#include "grille.h"
#include "sauvegarde.h" 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int main() {
    srand(time(NULL));
    Grille grille;
    Position curseur;
    int depart_x, depart_y, taille, nb_numeros;
    char choix_menu;
    bool partie_chargee = false;

    // --- MENU INITIAL ---
    bool input_correct = false;


    while (!input_correct) {
        system("cls"); // Nettoie la console à chaque début de boucle
        
        printf("=== JEU ZIP ===\n");
        printf("1. Nouvelle Partie\n");
        printf("2. Continuer la partie precedente\n");
        printf("Choix : ");

        choix_menu = _getch();
        if (choix_menu == '1' || choix_menu == '2') 
            input_correct = true;
    }
    printf("%c\n", choix_menu);

    if (choix_menu == '2') {
        if (charger_partie(&grille, &curseur, "sauvegarde.txt")) {
            partie_chargee = true;
            printf("Chargement reussi !\n");
            system("pause");
        } else {
            printf("Aucune sauvegarde trouvee. Lancement d'une nouvelle partie...\n");
            system("pause");
        }
    }

    // --- INITIALISATION (Seulement si nouvelle partie) ---
    if (!partie_chargee) {
        printf("\nConfiguration de la partie\n");
        printf("Taille (5-10) : ");
        scanf("%d", &taille);
        if (taille < TAILLE_MIN || taille > TAILLE_MAX) taille = 5;

        printf("Nombre de numeros (1-12) : ");
        scanf("%d", &nb_numeros);
        if (nb_numeros < 1 || nb_numeros > NB_NUMEROS_MAX) nb_numeros = 5;

        // Allocation et génération (ton code actuel)
        int **visited = (int**) malloc(taille * sizeof(int *));
        for (int i = 0; i < taille; i++) {
            visited[i] = (int*)malloc(taille * sizeof(int));
            for (int j = 0; j < taille; j++) visited[i][j] = 0;
        }

        initialiser_grille(&grille, taille, taille);
        curseur = depart_aleatoire(&depart_x, &depart_y, taille);
        hamiltonien(depart_x, depart_y, 1, taille, visited);
        placer_numeros_sur_chemin(&grille, visited, taille, nb_numeros);

        // Trouver le '1' pour placer le curseur
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

    // --- BOUCLE DE JEU ---
    while (true) {
        afficher_grille(&grille, curseur);
        printf("\nZQSD : Bouger | B : Sauvegarder & Quitter | X : Quitter sans sauvegarder\n");

        char input = _getch();

        if (input == 'x' || input == 'X') break;

        // GESTION DE LA SAUVEGARDE
        if (input == 'b' || input == 'B') {
            sauvegarder_partie(&grille, &curseur, "sauvegarde.txt");
            _getch(); // Attendre avant de fermer
            break;
        }

        deplacer_curseur(&curseur, &grille, input);
        if (a_gagne(&curseur, &grille)) {
            system("pause");
            break;
        }
    }

    return 0;
}