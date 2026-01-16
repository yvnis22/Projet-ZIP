# 🧩 Projet ZIP - Jeu de Parcours Logique

Le **Projet ZIP** est un casse-tête algorithmique développé en langage C dans le cadre d'une SAE (S1A). L'objectif est de tracer un chemin unique traversant l'intégralité d'une grille en respectant des points de passage numériques imposés.

---

## 📜 Règles du Jeu

Le jeu repose sur des contraintes logiques et algorithmiques strictes :
* **Complétion de la grille** : Le joueur doit passer une et une seule fois par chacune des cases de la grille.
* **Ordre numérique** : Des chiffres "presets" (de 1 à 12) sont placés sur la grille. Vous devez obligatoirement les atteindre dans l'ordre croissant (1, 2, 3...).
* **Déplacements** : Le curseur se déplace horizontalement ou verticalement (Haut, Bas, Gauche, Droite).
* **Interdiction des diagonales** : Les déplacements en diagonale ne sont pas autorisés.
* **Backtracking (Retour arrière)** : Si vous êtes bloqué, vous pouvez rebrousser chemin. Le programme effacera alors le parcours dans l'ordre inverse exact du chemin parcouru.

---

## 🎮 Commandes et Interface

L'interface utilise des codes couleurs ANSI pour afficher un dégradé fluide (du bleu au rouge) représentant la progression chronologique de votre chemin dans la grille.

### Contrôles au clavier (Mode Console)
| Touche | Action |
| :--- | :--- |
| **Z / W** | Déplacer le curseur vers le **Haut** |
| **S** | Déplacer le curseur vers le **Bas** |
| **Q / A** | Déplacer le curseur vers la **Gauche** |
| **D** | Déplacer le curseur vers la **Droite** |
| **B** | **Sauvegarder** la partie et quitter immédiatement |
| **X** | Quitter le programme sans sauvegarder |

### Menu Principal
1. **Nouvelle Partie** : Permet de configurer la taille de la grille (5x5 à 10x10) et le nombre de chiffres à placer.
2. **Continuer** : Charge l'état de la partie précédente depuis le fichier `sauvegarde.txt`.

---

## 🏗️ Architecture du Code

Le projet suit un découpage modulaire pour séparer les responsabilités :

### 🧠 Logique et Algorithmes
* **`algo_chemin.c`** : Gère la génération procédurale du niveau.
    * `hamiltonien` : Algorithme récursif de recherche de chemin passant par toutes les cases avec une sécurité de timeout pour éviter les blocages.
    * `placer_numeros_sur_chemin` : Répartit les objectifs numériques le long du chemin généré.
* **`deplacement.c`** : Implémente la validation des mouvements et la logique de backtracking (effacement des cases en reculant).
* **`gagne.c`** : Vérifie si toutes les cases (numero != 0) ont été visitées.

### 🖥️ Affichage et Système
* **`grille.c` & `grille.h`** : Définissent les structures `Case` et `Grille`. Gèrent l'affichage coloré et l'initialisation de la mémoire.
* **`fonctions_refresh.c` & `refresh.h`** : Utilisent l'API Windows (`gotoxy`, `cacher_curseur`) pour un rendu fluide et fixe sans clignotement de la console.
* **`main.c`** : Orchestre le menu, la génération du chemin hamiltonien et la boucle de jeu principale.

### 💾 Persistance des données
* **`sauvegarde.c` & `sauvegarde.h`** : Fonctions permettant d'écrire et de lire les dimensions de la grille, la position du curseur et l'état de chaque cellule dans un fichier texte.

---

## 🛠️ Installation et Compilation

### Prérequis
* Système d'exploitation : **Windows** (requis pour `windows.h` et `conio.h`).
* Compilateur : **GCC** ou tout environnement supportant le C.

### Compilation
Pour compiler l'ensemble des modules, utilisez la commande suivante :
```bash
gcc *.c -o ZIP_Game.exe
