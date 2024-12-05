# Jeu de la Vie

Ce projet implémente le célèbre jeu de la vie de John Conway en C++ avec deux modes :

- Mode console : affiche les états successifs de la grille dans la console et les sauvegarde dans des fichiers.

- Mode graphique : affiche la grille et son évolution dans une fenêtre graphique à l'aide de la bibliothèque SFML.

### Fonctionnalités principales : 

- Lecture d'une grille initiale depuis un fichier d'entrée.
  
- Évolution de la grille selon les règles du jeu de la vie :
    - Une cellule vivante reste vivante si elle a 2 ou 3 voisins vivants.
    - Une cellule morte devient vivante si elle a exactement 3 voisins vivants.

- Gestion des cellules obstacles :
    - Les cellules marquées comme obstacles ne changent jamais d'état.
    - Les obstacles peuvent être vivants ou morts.

- Deux modes d'exécution :
   - Console : Affiche la grille dans la console, sauvegarde chaque état dans des fichiers.
   - Graphique : Affiche la grille dans une fenêtre avec des animations.

### Prérequis :
- Logiciels nécessaires :
  - Un compilateur compatible C++17 (g++ recommandé).

- La bibliothèque SFML pour l'affichage graphique.

### Installation sur Ubuntu :

- sudo apt-get install libsfml-dev

## Structure des fichiers : 

### 1. Cellule.h et Cellule.cpp

Ces fichiers définissent une cellule du jeu de la vie.

- Propriétés :
  - vivante : État actuel de la cellule.
  - prochainEtat : État futur calculé.
  - obstacle : Si la cellule est un obstacle.

- Fonctionnalités :
 - Définir et appliquer les états.
 - Identifier les cellules vivantes et obstacles.

### 2. Grille.h et Grille.cpp
Ces fichiers définissent une grille rectangulaire contenant les cellules.

- Propriétés :
  - lignes : Nombre de lignes de la grille.
  - colonnes : Nombre de colonnes.
  - cellules : Matrice de cellules.

- Fonctionnalités :
  - Charger une grille depuis un fichier.
  - Sauvegarder une grille dans un fichier.
  - Mettre à jour les états des cellules.
  - Compter les voisins vivants d'une cellule.
  - Dessiner la grille dans la console ou dans une fenêtre graphique.

### 3. Jeu.h et Jeu.cpp
Ces fichiers définissent le jeu de la vie lui-même.

- Propriétés :
  - Une instance de Grille.
  - Un délai (en millisecondes) pour le mode graphique.

- Fonctionnalités :
  - Mode console : affiche les grilles dans la console et les sauvegarde.
  - Mode graphique : affiche les grilles dans une fenêtre animée.

### 4. main.cpp
Ce fichier permet d'éxecuter le programme.

- Permet à l'utilisateur de :
  - Fournir un fichier d'entrée contenant la grille initiale.
  - Choisir entre le mode console et le mode graphique.
  - Définir un délai pour le mode graphique.
- Structure d'un fichier d'entrée :
  - Le fichier d'entrée contient la grille initiale.

  - Première ligne : dimensions de la grille (lignes et colonnes).
  - Les lignes suivantes : les états des cellules : 
      - 0 : Cellule morte.
      - 1 : Cellule vivante.
      - 2 : Cellule obstacle morte.
      - 3 : Cellule obstacle vivante.

### Exemple :

![{5C44B8D1-9CE7-4BE9-9520-EF830CB9D1CE}](https://github.com/user-attachments/assets/73da93e5-530e-4cd0-987f-5f935e90cc5e)


### Compilation et Exécution :
1. Compilation
  - Utilisez g++ pour compiler les fichiers :

    - g++ -o jeu_de_la_vie main.cpp Jeu.cpp Grille.cpp Cellule.cpp -lsfml-graphics -lsfml-window -lsfml-system

  - Ou utilisez un makefile pour compiler :
      - make

2. Exécution
  - Lancez le programme en ligne de commande :

    - ./jeu_de_la_vie

### Explications des Modes : 
- Mode Console :
  - L'utilisateur fournit un fichier d'entrée.
  - Le programme affiche les états successifs de la grille dans la console.
  - Chaque itération est sauvegardée dans un fichier texte dans un dossier <nom_du_fichier_dentree>_out.

- Mode Graphique :
  - L'utilisateur fournit un fichier d'entrée.
  - Le programme affiche une fenêtre graphique représentant la grille.
  - L'évolution de la grille est animée avec un délai ajustable entre chaque itération.

### Exemple de Sortie : 

- Mode Console :

### Itération 0 :
![{BFF2DE68-8328-4562-930A-7FC53554727D}](https://github.com/user-attachments/assets/9ec4884e-983d-4013-a197-844f41f8e1fb)



### Itération 1 :
![{542BEBE7-8E3C-42B3-9E8B-352E13C32A51}](https://github.com/user-attachments/assets/80216391-cbc0-4cee-a633-dc32c6c2ac76)


- Mode Graphique : 
  - Une fenêtre s'ouvre avec des couleurs :
    - Vert : cellules vivantes normales.
    - Noir : cellules mortes normales.
    - Rouge : obstacles vivants.
    - Gris foncé : obstacles morts.

### Optimisations Implémentées

- Prévention des fuites mémoire :

  - Utilisation de conteneurs STL (std::vector) pour une gestion automatique de la mémoire.

  - Lisibilité et efficacité :

    - Division des responsabilités en plusieurs fichiers .h et .cpp entre les classes Cellule, Grille et Jeu.

### À Propos des Couleurs :

- Console :
    - "#" : Cellule vivante normale.
    - "." : Cellule morte normale.
    - "X" : Cellule obstacle vivante.
    - "O" : Cellule obstacle morte.
- Graphique : 
    - Blanc : Cellule vivante normale.
    - Noir : Cellule morte normale.
    - Rouge : Cellule obstacle vivante.
    - Gris foncé : Cellule obstacle morte.
