// Inclusion des bibliotheques necessaires
// -- Noah 

#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h> // ajout pour ncurses


// définition de la grille selon les choix de l'utilisateur puis initialisation de celle ci 
// -- Noah 

int main() {

    //démarrage ncurses -LONDON-
    initscr();      
    //CBREAK = on a pas a appuyer sur entrer pour effectuer un input -LONDON-
    cbreak();             
    //On affiche pas les charactères saisis dans le terminal (NOECHO)
    noecho();             

    gerer_interface(); //procédure écrite dans .h pour gérer l'interface
    gerer_input(); //procédure qui attends les inputs utilisateur
      

    Grille grille;
    int taille = 5; // valeur par défaut 5x5
    int nb_numeros; //PLACEHOLDER avant la création de l'algorithme de création aléatoire de grille

    // menu de sélection de la taille de la grille
    const char *options[] = {
        "5x5", "6x6", "7x7", "8x8", "9x9", "10x10"      
    };
    int nb_options = 6;
    int choix = 0; // index du bouton sélectionné (0) (cest une liste dans laquelle on navigue)

    while (1) {     //while (1) est une boucle infinie
        clear(); //effacer l ecran puis le recharger
        mvprintw(0, 0, "Jeu ZIP - Configuration de la partie\n");   //self explanatory, affichage à l'écran d'un menu de configuration.
        mvprintw(2, 0, "Choisissez la taille de la grille avec les fleches ou ZS puis validez avec ENTREE :"); //

        for (int i = 0; i < nb_options; i++) {
            if (i == choix) {
                attron(A_REVERSE); //activation surbrillance de l'option (pour démarquer des autres)
                mvprintw(4 + i, 5, "[ %s ]", options[i]);      
                attroff(A_REVERSE); //désactivation de la surbrillance de l'option
            } else {
                mvprintw(4 + i, 5, "[ %s ]", options[i]);    //affichage de base
            }
        }
        refresh(); //rafraichir l'écran du terminal après les changements

        int input = getch();
        if (input == 'z' || input == 'Z') {   //monter dans le menu
            if (choix > 0) choix--;
        } else if (input == 's' || input == 'S') {          //descendre dans le menu
            if (choix < nb_options - 1) choix++;
        } else if (input == '\n') { // touche entrée
            taille = 5 + choix; // car options commencent à 5x5
            break;
        }
    }

    // PLACEHOLDER avant l'ajout de la procédure de génération de grille automatique
    printw("entres le nombre de numeros que tu souhaites (1-12) sinon 5 automatiquement : ");
    refresh();   //mise a jour de l'écran
    scanw("%d", &nb_numeros);  //comme un scanf mais immédiat
    if (nb_numeros < 1 || nb_numeros > NB_NUMEROS_MAX){ nb_numeros = 5;} //condition pour confirmer l'affichage de la grille 

    initialiser_grille(&grille, taille, taille);

    // met le curseur et le numero de la premiere case a 1 
    Position curseur = {0, 0};
    grille.cellules[0][0].numero = 1;

    // declare la variable qui va nous servir a input 
    char input;

    while (true) {
        clear(); // efface l’écran avant réaffichage
        afficher_grille(&grille, curseur); //de noah

        printw("\n utilise ZQSD (or WASD) pour te deplacer. APPUIE SUR X POUR QUITTER.\n"); 
        refresh(); //mise a jour ecran

        //fonction pour lier une touche à un input 
        input = getch(); 

        // mets fin au programme 
        if (input == 'x' || input == 'X')  //si on appuie sur 'X', on stoppe tout.
            break;
        // appelle la fonction qui fait tout les deplacements de Anouk
        deplacer_curseur(&curseur, &grille, input);
        
    }

    endwin(); // fin ncurses 

    return 0;

    
}
