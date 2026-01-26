#include "grille.h"
#include "sauvegarde.h" 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

/*
================================================================================
Fonction   : gotoxy
Auteur     : Anouk
Param      : x (int) - Coordonnée colonne
             y (int) - Coordonnée ligne
Traitement : Déplace le curseur de la console à une position précise pour 
             permettre un affichage fixe sans clignotement.
Retour     : Aucun (void)
================================================================================
*/
void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*
================================================================================
Fonction   : cacher_curseur
Auteur     : Anouk
Param      : Aucun
Traitement : Utilise l'API Windows pour rendre le curseur de saisie invisible 
             pendant l'affichage de la grille.
Retour     : Aucun (void)
================================================================================
*/
void cacher_curseur() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}