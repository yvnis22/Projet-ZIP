# 🧩 Projet ZIP - Jeu de Parcours Logique

Bienvenue dans le **Projet ZIP**, une application développée en langage C dans le cadre d'une SAE en Département Informatique (S1A). Le but est de résoudre un casse-tête de parcours en remplissant l'intégralité d'une grille.

---

## 📜 Règles du Jeu

Le jeu ZIP repose sur des contraintes algorithmiques et logiques strictes :
* **Complétion de la grille** : Le joueur doit passer une et une seule fois par chacune des cases de la grille.
* **Ordre numérique** : Le parcours doit respecter l'ordre des numéros (1, 2, 3...) placés aléatoirement sur la grille.
* **Déplacements autorisés** : Le curseur peut se déplacer en bas, en haut, à gauche et à droite.
* **Interdiction des diagonales** : Les déplacements en diagonale ne sont pas autorisés.
* **Backtracking (Retour arrière)** : Il est possible de rebrousser chemin, mais le joueur doit alors repasser dans l'ordre inverse exact du chemin parcouru.

---

## 🎮 Comment Jouer ?

### Commandes au clavier
L'interface utilisateur s'exécute exclusivement en mode console sous Windows.

| Touche | Action |
| :--- | :--- |
| **Z / W** | Déplacer le curseur vers le **Haut** |
| **S** | Déplacer le curseur vers le **Bas** |
| **Q / A** | Déplacer le curseur vers la **Gauche** |
| **D** | Déplacer le curseur vers la **Droite** |
| **B** | **Sauvegarder** la partie en cours et quitter immédiatement |
| **X** | Quitter le programme sans sauvegarder |

### Menu Principal
Au lancement du jeu, un menu vous permet de choisir entre deux modes :
1. **Nouvelle Partie** : Permet de configurer la taille de la grille (minimum 5x5, maximum 10x10) et le nombre de chiffres à placer (jusqu'à 12).
2. **Continuer** : Charge automatiquement l'état de la partie précédente depuis le fichier `sauvegarde.txt`.

---

## 🛠️ Installation et Compilation

### Prérequis
* Système d'exploitation : **Windows** (obligatoire pour l'exécution finale).
* Compilateur : **GCC** ou tout environnement supportant le langage C.

---

## 🏗️ Architecture du Projet

Le programme suit un **découpage fonctionnel** strict pour séparer les responsabilités :

* **`main.c`** :
    * Gère le menu principal (Nouvelle partie / Charger) avec nettoyage de la console.
    * Initialise le générateur aléatoire (`srand`) et les structures de base.
    * Orchestre la boucle de jeu et la détection des touches de sauvegarde ou de sortie.
* **`grille.h` & `grille.c`** :
    * Définit les structures `Case`, `Grille` et `Position`.
    * `initialiser_grille` : Prépare la mémoire et met les cases à zéro.
    * `afficher_grille` : Gère le rendu visuel du jeu en console avec `system("cls")`.
* **`deplacement.c`** :
    * `deplacer_curseur` : Calcule les nouvelles coordonnées et vérifie la légalité du mouvement.
    * Implémente la logique de backtracking pour effacer les cases en reculant.
* **`algo chemin.c`** :
    * `hamiltonien` : Algorithme récursif permettant de générer un chemin passant par toutes les cases.
    * `placer_numeros_sur_chemin` : Répartit les numéros obligatoires le long du chemin généré.
* **`sauvegarde.h` & `sauvegarde.c`** :
    * `sauvegarder_partie` : Enregistre l'état de la grille, du curseur et de la progression dans `sauvegarde.txt`.
    * `charger_partie` : Restaure une partie précédente au lancement du jeu.
* **`gagne.c`** :
    * `a_gagne` : Parcourt la grille pour vérifier qu'aucune case vide (numero == 0) ne subsiste.

---

### Compilation
Pour compiler le projet complet (incluant tous les modules), utilisez la commande suivante dans votre terminal :
```bash
gcc *.c -o ZIP_Game.exe
```
--- 

### 👥 Auteurs
- Emilien BRANDO
- Yanis BENMIRA
- Anouk OBER
- London OSSETI-FORT
- Noah DELATTRE
