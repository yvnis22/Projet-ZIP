#include "grille.h"
#include "sauvegarde.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h> // ncurses remplace conio.h

int main() {
    srand(time(NULL));
    Grille grille;
    Position curseur;
    int depart_x, depart_y, taille, nb_numeros;
    char choix_menu;
    bool partie_chargee = false;

    // --- INITIALISATION NCURSES ---
    initscr();
    cbreak();
    noecho();

    // --- MENU INITIAL ---
    mvprintw(0, 0, "  ▀▀                     ▀▀        ");
    mvprintw(1, 0, "  ██ ▄█▀█▄ ██ ██   ▀▀▀██ ██  ████▄ ");
    mvprintw(2, 0, " ▀██ ██▄█▀ ██ ██     ▄█▀ ██  ██ ██ ");
    mvprintw(4, 0, "  ██ ▀█▄▄▄ ▀██▀█   ▄██▄▄ ██▄ ████▀ ");
    mvprintw(5, 0, "  ██                         ██  ");
    mvprintw(6, 0, "▀▀▀                          ▀▀ ");
    mvprintw(9, 0, "1. Nouvelle Partie");
    mvprintw(10, 0, "2. Continuer la partie precedente");
    mvprintw(11, 0, "Choix : ");
    refresh();

    // LECTURE DU CHOIX (ncurses)
    choix_menu = getch();

    // DEBUG
    printw("\nVous avez choisi : %c\n", choix_menu);
    refresh();

    if (choix_menu == '2') {
        if (charger_partie(&grille, &curseur, "sauvegarde.txt")) {
            partie_chargee = true;
            printw("Chargement reussi !\n");
        } else {
            printw("Aucune sauvegarde trouvee. Nouvelle partie...\n");
        }
        printw("Appuyez sur une touche...");
        getch();
    }

    // --- INITIALISATION SI NOUVELLE PARTIE ---
    if (!partie_chargee) {
        endwin(); // quitter ncurses pour utiliser scanf proprement
        printf("\nConfiguration de la partie\n");
        printf("Taille (5-10) : ");
        scanf("%d", &taille);
        if (taille < TAILLE_MIN || taille > TAILLE_MAX) taille = 5;

        printf("Nombre de numeros (1-12) : ");
        scanf("%d", &nb_numeros);
        if (nb_numeros < 1 || nb_numeros > NB_NUMEROS_MAX) nb_numeros = 5;

        // Allocation du tableau visited
        int **visited = malloc(taille * sizeof(int *));
        for (int i = 0; i < taille; i++) {
            visited[i] = malloc(taille * sizeof(int));
            for (int j = 0; j < taille; j++) visited[i][j] = 0;
        }

        initialiser_grille(&grille, taille, taille);
        curseur = depart_aleatoire(&depart_x, &depart_y, taille);
        hamiltonien(depart_x, depart_y, 1, taille, visited);
        placer_numeros_sur_chemin(&grille, visited, taille, nb_numeros);

        // Trouver le '1'
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

        // Libération mémoire
        for (int i = 0; i < taille; i++) free(visited[i]);
        free(visited);

        // Retour à ncurses
        initscr();
        cbreak();
        noecho();
    }

    // --- BOUCLE DE JEU ---
    while (1) {
        afficher_grille(&grille, curseur);
        printw("\nZQSD : Bouger | B : Sauvegarder & Quitter | X : Quitter sans sauvegarder\n");
        refresh();

        char input = getch();

        if (input == 'x' || input == 'X') break;

        if (input == 'b' || input == 'B') {
            sauvegarder_partie(&grille, &curseur, "sauvegarde.txt");
            printw("Sauvegarde effectuee. Appuyez sur une touche...");
            getch();
            break;
        }

        deplacer_curseur(&curseur, &grille, input);

        if (a_gagne(&curseur, &grille)) {
            printw("Bravo, vous avez gagne !\n");
            printw("Appuyez sur une touche...");
            getch();
            break;
        }
    }

    endwin();
    return 0;
}
