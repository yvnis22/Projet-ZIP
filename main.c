#include "grille.h"
#include "sauvegarde.h" // N'oublie pas d'inclure ton nouveau header
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // Pour _getch() sous Windows

int main() {
    Grille grille;
    Position curseur;
    char choix_menu;
    bool partie_chargee = false;

    // --- MENU PRINCIPAL ---
    printf("=== JEU ZIP ===\n");
    printf("N - Nouvelle Partie\n");
    printf("C - Continuer la partie precedente\n");
    printf("Votre choix : ");
    
    do {
        choix_menu = _getch();
    } while (choix_menu != 'n' && choix_menu != 'N' && choix_menu != 'c' && choix_menu != 'C');
    printf("%c\n", choix_menu); // Feedback visuel

    // --- LOGIQUE DE CHARGEMENT OU INITIALISATION ---
    if (choix_menu == 'c' || choix_menu == 'C') {
        if (charger_partie(&grille, &curseur, "sauvegarde.txt")) {
            printf("Partie chargee !\n");
            partie_chargee = true;
            system("pause"); // Laisse le temps de lire
        } else {
            printf("Aucune sauvegarde trouvee ou erreur de lecture. Demarrage d'une nouvelle partie...\n");
            system("pause");
        }
    }

    // Si on a choisi Nouvelle Partie OU si le chargement a échoué
    if (!partie_chargee) {
        int taille, nb_numeros;
        
        printf("\n--- Configuration Nouvelle Partie ---\n");
        printf("Taille de la grille (5-10) [defaut 5]: ");
        if (scanf("%d", &taille) != 1) taille = 5; // Securite si l'utilisateur tape des lettres
        if (taille < TAILLE_MIN || taille > TAILLE_MAX) taille = 5;

        // Note: Ton code original demandait nb_numeros mais ne l'utilisait pas encore dans initialiser_grille
        // Je le laisse pour respecter ta structure.
        printf("Nombre de numeros (1-12) [defaut 5]: ");
        if (scanf("%d", &nb_numeros) != 1) nb_numeros = 5;
        if (nb_numeros < 1 || nb_numeros > NB_NUMEROS_MAX) nb_numeros = 5;

        // Initialisation standard
        initialiser_grille(&grille, taille, taille);
        
        // Configuration initiale du curseur (Hardcode comme dans ton fichier original)
        curseur = get_pos1();
        grille.cellules[curseur.y][curseur.x].numero = 1; 
        grille.cellules[curseur.y][curseur.x].chiffre = 1; 
    }

    // --- BOUCLE DE JEU ---
    while (true) {
        afficher_grille(&grille, curseur);

        printf("\nZ/Q/S/D : Deplacer | B : Sauvegarder & Quitter | X : Quitter sans sauver\n");
        printf("Input: ");

        char input = _getch();
        // printf("%c\n", input); // Optionnel : afficher la touche pressée

        // QUITTER SANS SAUVER
        if (input == 'x' || input == 'X')
            break;

        // SAUVEGARDER ET QUITTER
        if (input == 'b' || input == 'B') {
            sauvegarder_partie(&grille, &curseur, "sauvegarde.txt");
            printf("A bientot !\n");
            break;
        }

        deplacer_curseur(&curseur, &grille, input);

        if (a_gagne(&curseur, &grille)){
            // Optionnel : Supprimer la sauvegarde si on gagne pour forcer une nouvelle partie ?
            // remove("sauvegarde.txt"); 
            system("pause");
            break;
        }
    }

    return 0;
}