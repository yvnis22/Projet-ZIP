#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "grille.h"
#include <stdbool.h>

/**
 * Sauvegarde l'état actuel de la partie dans un fichier.
 * Auteur : Gemini (pour aider Noah)
 */
void sauvegarder_partie(Grille *grille, Position *curseur, const char *nom_fichier);

/**
 * Charge une partie depuis un fichier.
 * Retourne true si le chargement a réussi, false sinon.
 */
bool charger_partie(Grille *grille, Position *curseur, const char *nom_fichier);

#endif