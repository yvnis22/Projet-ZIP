# 🧩 Projet ZIP - Jeu de Parcours Logique

Bienvenue dans le **Projet ZIP**, une application développée en langage C dans le cadre d'une SAE en Département Informatique (S1A). Le but est de résoudre un casse-tête de parcours algorithmique en remplissant l'intégralité d'une grille générée dynamiquement.

---

## 📜 Règles du Jeu

Le jeu ZIP repose sur des contraintes logiques strictes :

* **Complétion de la grille** : Le joueur doit passer une et une seule fois par chacune des cases de la grille.
* **Ordre numérique** : Le parcours doit respecter l'ordre des numéros pré-placés (les "presets" : 1, 2, 3...) sur la grille.
* **Déplacements autorisés** : Le curseur peut se déplacer uniquement de manière orthogonale (Haut, Bas, Gauche, Droite).
* **Interdiction des diagonales** : Les déplacements en diagonale ne sont pas autorisés.
* **Backtracking (Retour arrière)** : Il est possible de rebrousser chemin pour corriger une erreur, mais le joueur doit repasser dans l'ordre inverse exact du chemin parcouru (effaçant ainsi son passage).

---

## 🎮 Comment Jouer ?

### Commandes au clavier

L'interface utilisateur s'exécute en mode console sous Windows. La navigation se fait désormais via les **flèches directionnelles**.

| Touche | Action |
| --- | --- |
| **⬆️ Flèche HAUT** | Déplacer le curseur vers le **Haut** |
| **⬇️ Flèche BAS** | Déplacer le curseur vers le **Bas** |
| **⬅️ Flèche GAUCHE** | Déplacer le curseur vers la **Gauche** |
| **➡️ Flèche DROITE** | Déplacer le curseur vers la **Droite** |
| **B** | **Sauvegarder** la partie et retourner au menu |
| **X** | Retourner au menu principal **sans sauvegarder** |

### Menu Principal

Au lancement, un menu graphique ASCII vous propose trois options :

1. **Nouvelle Partie** : Permet de configurer la taille de la grille (de 5x5 à 10x10) et le nombre de chiffres objectifs (jusqu'à 12).
2. **Continuer Partie** : Charge automatiquement l'état de la dernière partie depuis le fichier `sauvegarde.txt`.
3. **Quitter le Jeu** : Ferme l'application.

---

## 🛠️ Installation et Compilation

### Prérequis

* **Système d'exploitation** : Windows (nécessaire pour `windows.h`, `conio.h` et la gestion du curseur).
* **Encodage** : Console configurée en UTF-8 pour l'affichage des caractères spéciaux (cœurs, blocs).
* **Compilateur** : GCC (MinGW) recommandé.

### Compilation

Pour compiler le projet complet, ouvrez votre terminal dans le dossier du projet et exécutez :

```bash
gcc *.c -o ZIP_Game.exe

```

---

## 🏗️ Architecture du Projet

Le programme suit un **découpage modulaire** pour séparer la logique, l'affichage et la gestion des données :

* **`main.c`** :
  * Point d'entrée du programme.
  * Contient la **boucle principale** de l'application (Menu ↔ Jeu).
  * Gère l'initialisation et les transitions entre les écrans.


* **`grille.c` & `grille.h`** :
  * Gère la structure de données `Grille`.
  * `initialiser_grille` : Allocation mémoire et configuration.
  * `afficher_grille` : Rendu visuel avancé avec **dégradé de couleurs ANSI** (Rouge → Bleu) pour visualiser la progression du chemin.


* **`deplacement.c`** :
  * Moteur physique du jeu.
  * `deplacer_curseur` : Gère les collisions, valide l'ordre des presets et implémente la logique de **backtracking**.
  * Interprète les codes ASCII des flèches directionnelles.


* **`algo chemin.c`** :
  * Générateur de niveau procédural.
  * `hamiltonien` : Algorithme de recherche récursif (backtracking) pour garantir qu'une solution existe.
  * Intègre un **timeout** (sécurité temporelle) pour éviter les blocages lors de la génération de grandes grilles (10x10).
  * `placer_numeros_sur_chemin` : Distribue intelligemment les objectifs sur le chemin validé.


* **`sauvegarde.c`** :
  * Gestion de la persistance des données.
  * Sérialise la grille, la position du joueur et l'historique dans `sauvegarde.txt`.


* **`fonctions_refresh.c`** :
  * Outils d'optimisation d'affichage.
  * `gotoxy` : Permet de rafraîchir l'écran sans clignotement en déplaçant le curseur console.
  * `cacher_curseur` : Masque le curseur clignotant de Windows pour une meilleure esthétique.


* **`gagne.c`** :
  * `a_gagne` : Vérifie la condition de victoire (remplissage total de la grille).



---

### 👥 Auteurs

Projet réalisé par l'équipe :

* **Emilien BRANDO**
* **Yanis BENMIRA**
* **Anouk OBER**
* **London OSSETI-FORT**
* **Noah DELATTRE**
