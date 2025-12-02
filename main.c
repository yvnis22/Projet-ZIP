// Inclusion des bibliotheques necessaires
// -- Noah 🍆

#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h> // ajout pour ncurses


// définition de la grille selon les choix de l'utilisateur puis initialisation de celle ci 
// -- Noah 

int main() {

    //démarrage ncurses 🍆🍆
    initscr();      
    //On appuie pas sur entrée, les inputs sont directement pris en compte (caca)      🍆🍆
    cbreak();             
    //On affiche pas les touches🍆🍆
    noecho();             

    gerer_interface(); //procédure écrite dans .h. 🍆🍆
    gerer_input(); //procédure qui attends les inputs utilisateur zobzoubazobzobzobzouba🍆🍆
      

    Grille grille;
    int taille = 5; // valeur par défaut obviii 5x5 grille mais au final 5x30 training for maximum sex aptitudes
    int nb_numeros; //g pas capté mais j'ai juste adapté en ncurses ce que ça faisait lolol 🍆🍆

    // menu de sélection de la taille de la grille
    const char *options[] = {
        "5x5", "6x6", "7x7", "8x8", "9x9", "10x10"      //si besoin on rajoutera d'autres tailles, un peu comme le besoin d'inventer une nouvelle taille de préservatif pour mon PICO-penis
    };
    int nb_options = 6;
    int choix = 0; // index du bouton sélectionné (0)

    while (1) {
        clear(); //effacer l ecran puis le recharger, je vais littéralement spammer ça
        mvprintw(0, 0, "Jeu ZIP - Configuration de la partie\n");   //self explanatory
        mvprintw(2, 0, "Choisissez la taille de la grille avec les fleches ou ZQSD puis validez avec ENTREE :");//self explanatory 🍆🍆🍆🍆🍆🍆

        for (int i = 0; i < nb_options; i++) {
            if (i == choix) {
                attron(A_REVERSE); // met en surbrillance l'option sélectionnée pour montrer sur quelle option on est en tant qu utilisateur
                mvprintw(4 + i, 5, "[ %s ]", options[i]);               //En gros si i==choix, on surbrille, sinon affichage normal
                attroff(A_REVERSE);
            } else {
                mvprintw(4 + i, 5, "[ %s ]", options[i]);
            }
        }
        refresh(); //cette merde est ultra importante sinon rien ne s'affiche

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

    // demande du nombre de numeros (me suis pas fait chier ça va rester un scanf mais en scanw hihihihihihihihihihihihhihi 🍆🍆)
    printw("entres le nombre de numeros que tu souhaites (1-12) sinon 5 automatiquement : ");
    refresh();   //mise a jour de l'écran et non pas effaçage. 🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆
    scanw("%d", &nb_numeros);  //comme un scanf mais immédiat
    if (nb_numeros < 1 || nb_numeros > NB_NUMEROS_MAX){ nb_numeros = 5;} //condition pour confirmer l'affichage de la grille 🍆🍆🍆🍆

    initialiser_grille(&grille, taille, taille);

    // met le curseur et le numero de la premiere case a 1 
    Position curseur = {0, 0};
    grille.cellules[0][0].numero = 1;

    // declare la variable qui va nous servir a input 
    char input;

    while (true) {
        clear(); // efface l’écran avant réaffichage
        afficher_grille(&grille, curseur); //de noah la lalalalalalalalalala 

        printw("\n utilise ZQSD (or WASD) pour te deplacer. APPUIE SUR X POUR QUITTER.\n");
        refresh(); //mise a jour ecran

        //fonction pour lier une touche à un input FAHHHH
        input = getch(); // FAHHHH

        // mets fin au programme 
        if (input == 'x' || input == 'X')  //EN GROS systeme pour quitter la partie, conditionnelle if on appuie sur x ou X ça quitte.
            break;
        // appelle la fonction qui fait tout les deplacements de Anoul !!!!!!!!!!!!!!!
        deplacer_curseur(&curseur, &grille, input);
        
    }

    endwin(); // fin ncurses 🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆 nettoyage de la circonférence du cylindre

    return 0;

    
}
