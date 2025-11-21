// voici l'enfer que jai ecrit 
// jai utiliser de l'ia dans les moments ou je bloquais, mais ct plus des problemes de syntaxes/contradictions.
#include "grille.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

// EN GROS. a chaque fois quon va hardcode une grille on doit connaitre la position du premier chiffre. 
// donc la position initiale du curseur
// cette fonction qui va normalement ce dupliquer plus tard si c pas foireux. elle sert a hardcode la 
// position initiale du curseur
Position get_pos1() {
    Position p = {4, 2,1};
    return p ;

}




void deplacer_curseur(Position *curseur, Grille *grille, char touche) {
    // permet de conserver les coordonnees actuels
    // cela permet de ne pas faire le mouvement de suite pour pouvoir voir si le mouvement est legal 
    int new_x = curseur->x;
    int new_y = curseur->y;
    // switch/case est une facon plus propre d'ecrire "if else if else if..."  
    switch (touche) { // on dit quon aimerait tester la variable touche 
        case 'w': case 'W': case 'z': case 'Z': // test les differents cas pour aller en haut
            if (curseur->y > 0) new_y--; // update que le nouvelles coordonnee et pas les actuels 
            break; // si c propre arretez de me faire chier xD

        case 's': case 'S': // pareil pour le bas
            if (curseur->y < grille->lignes - 1) new_y++;
            break;

        case 'a': case 'A': case 'q': case 'Q': // a gauche
            if (curseur->x > 0) new_x--;
            break;

        case 'd': case 'D':
            if (curseur->x < grille->colonnes - 1) new_x++; // a droite
            break;

        default:
            return;
    }
    
    // pour avoir le numero de la case et le numero de la case apres le mouvement
    // des fois ca marché quand je mettais ces variables mais des fois non, c pour ca
    // que des fois j'ecrit en entier ou des fois j'utilise les noms de variables.
    // POUR COMPRENDRE LE NOM DES VARIABLES DE STRUCTURES, VOIR LE HEADER (ex chiffre, numero, chiffre_actuel...)
    int numero_actuel = grille->cellules[curseur->y][curseur->x].numero;
    int nv_numero = grille->cellules[new_y][new_x].numero;

    //on teste si c une case quon a deja visité
    if (nv_numero != 0) {
        //  la on veut savoir si on a reculer 
        if (nv_numero == numero_actuel - 1) {


            if (grille->cellules[curseur->y][curseur->x].chiffre == curseur->chiffre_actuel){
                curseur->chiffre_actuel = curseur->chiffre_actuel -1 ;
            }
            else if (grille->cellules[curseur->y][curseur->x].chiffre == 1){
                curseur->chiffre_actuel = 1;
            }
               
            // Remettre la case on ou été à 0
            grille->cellules[curseur->y][curseur->x].numero = 0;
            
            // deplace le curseur
            curseur->x = new_x;
            curseur->y = new_y;
            //si on part d'un chiffre preset, on doit decrementer sinon on peut pas acceder 
            //au numero suivant 
            
            
            
            return;
        }
    }
    
    // DÉPLACEMENT NORMAL : vers une case vide (numero == 0) ou un chiffre preset
    if (nv_numero == 0) {
        // Si la case a un chiffre preset et que c'est le prochain dans l'ordre ex 1  2  3...
        if (grille->cellules[new_y][new_x].chiffre != 0 && 
            grille->cellules[new_y][new_x].chiffre == curseur->chiffre_actuel + 1) {
            // on se deplace
            curseur->x = new_x;
            curseur->y = new_y;
            //on incremente le numero pour avoir l'effet de backtracking
            grille->cellules[new_y][new_x].numero = numero_actuel + 1;
            // on passe le chiffre du curseur au nouveau chiffre preset 
            curseur->chiffre_actuel = grille->cellules[curseur->y][curseur->x].chiffre;
        }
        // la case "depart" est speciale, parce que si on revient dessus on ne doit PAS decrementer 
        // sinon notre chiffre actuel du curseur devient 0 donc impossible de passer a 2.
        if ( nv_numero == 1 && grille->cellules[new_y][new_x].chiffre == 1){
            grille->cellules[curseur->y][curseur->x].numero = 0;
            
            // Deplace le curseur
            curseur->x = new_x;
            curseur->y = new_y;

        }
        // si c'est une case vide on fait la procedure normale
        else if (grille->cellules[new_y][new_x].chiffre == 0) {
            // on se deplace
            curseur->x = new_x;
            curseur->y = new_y;
            //on incremente le numero pour avoir l'effet de backtracking
            grille->cellules[new_y][new_x].numero = numero_actuel + 1;
        }  
        
        
    }
}