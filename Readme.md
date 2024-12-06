# Jeu de la Vie

#### https://github.com/maelpitois/POO

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
- Architecture MVC :
    - Modèle (Model) : La classe `Grille` représente la grille du jeu et les règles de l'automate.
    - Vue (View) : La classe `Vue` permet l'affichage dans la console ou la fenêtre graphique.
    - Contrôleur (Controller) : La classe `Controleur` permet l'interaction entre la vue et le modèle.

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

### 3. Vue.h et Vue.cpp
Ces fichiers gèrent l'affichage du jeu, en console ou dans une fenêtre graphique.

- Fonctionnalités :
  - afficherConsole : Affiche la grille dans la console.
  - afficherGraphique : Affiche la grille dans une fenêtre graphique à l'aide de SFML.

### 4. Controleur.h et Controleur.cpp
Ces fichiers orchestrent l'interaction entre le modèle et la vue.

- Fonctionnalités :
  - lancerModeConsole : Gère l'exécution en mode console.
  - lancerModeGraphique : Gère l'exécution en mode graphique, avec une gestion du délai entre chaque itération.

### 5. main.cpp
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


# Documentation Technique : Jeu de la Vie

## 1. Structure du projet
Le projet est structuré en plusieurs fichiers pour organiser clairement les responsabilités :

  - Cellule.h et Cellule.cpp : Définit les cellules du jeu.
  - Grille.h et Grille.cpp : Définit la grille contenant les cellules.
  - Controleur.h et Controleur.cpp : Gère l'exécution du jeu en mode console ou graphique.
  - main.cpp : Point d'entrée du programme, permettant à l'utilisateur de configurer et lancer le jeu.

Chaque fichier a été conçu pour séparer les responsabilités et utiliser au mieux la programmation orientée objet.

## 2. Fichiers et Classes

### 2.1 Cellule.h et Cellule.cpp
Rôle : Gère les propriétés et comportements individuels des cellules.

- Propriétés :
  - vivante : Booléen indiquant si la cellule est vivante (true) ou morte (false).
  - prochainEtat : Booléen stockant l'état calculé pour la prochaine itération.
  - obstacle : Booléen indiquant si la cellule est un obstacle (true) ou non (false).

#### Méthodes :
  - Cellule() : Constructeur par défaut, initialise une cellule morte et non-obstacle.
  - Cellule(bool etatInitial, bool estObstacle = false) : Constructeur avec état initial et possibilité de définir un obstacle.
  - bool estVivante() const : Retourne si la cellule est vivante.
  - bool estObstacle() const : Retourne si la cellule est un obstacle.
  - void definirEtat(bool etat) : Définit l'état actuel de la cellule si elle n'est pas un obstacle.
  - void definirProchainEtat(bool etat) : Définit l'état futur de la cellule si elle n'est pas un obstacle.
  - void appliquerProchainEtat() : Applique l'état futur à l'état actuel, sauf pour les obstacles.

#### Interactions :
Une cellule est utilisée par la classe Grille comme unité de base pour représenter une position dans la grille.

### 2.2 Grille.h et Grille.cpp
Rôle : Gére la mise à jour des cellules.

#### Propriétés :
  - lignes : Nombre de lignes dans la grille.
  - colonnes : Nombre de colonnes dans la grille.
  - cellules : Matrice 2D de cellules (std::vector<std::vector<Cellule>>).

#### Méthodes :
  - Grille() : Constructeur par défaut, initialise une grille vide.
  - bool chargerDepuisFichier(const std::string& nomFichier) :
      - Charge les dimensions et états des cellules depuis un fichier.
      - Gère les états obstacles (valeurs 2 et 3).
  - bool sauvegarderDansFichier(const std::string& dossier, int iteration) const :
    - Sauvegarde l'état actuel de la grille dans un fichier pour une itération donnée.
  - bool mettreAJour() :
    - Calcule les prochains états pour toutes les cellules.
    - Applique les nouveaux états.
    - Retourne false si l'automate s'est stabilisé (aucun changement d'état).
  - int compterVoisinsVivants(int x, int y) const :
    - Retourne le nombre de voisins vivants autour d'une cellule donnée.
#### Interactions :
- La classe Grille est utilisée par Controleur pour manipuler l'état global de la simulation

### 2.3 Vue.h et Vue.cpp 
Rôle : Représente une grille rectangulaire composée de cellules et gère l'évolution des états

#### Propriétés :

#### Méthodes : 
 - void afficherGraphique(sf::RenderWindow& fenetre)  :
    - Dessine la grille dans une fenêtre graphique à l'aide de rectangles colorés.
- void afficherConsole() const :
    - Affiche la grille dans la console avec des symboles (#, ., X, O).

### 2.4 Controleur.h et Controleur.cpp
Rôle : Permet l'exécution du jeu en mode console ou graphique.

#### Propriétés :
  - vue : instance de la classe Vue.
  - grille : Instance de la classe Grille.
  - delaiMs : Délai entre les itérations en mode graphique (en millisecondes).
  - fichierEntree : Chemin du fichier contenant la grille initiale.

#### Méthodes :
  - Controleur(const std::string& fichierEntree, int delaiMs) :
    - Initialise le jeu en chargeant la grille depuis un fichier.
  - void executerModeConsole() :
    - Affiche les grilles successives dans la console.
    - Sauvegarde chaque état dans des fichiers.
    - Arrête l'exécution si l'automate se stabilise.
  - void executerModeGraphique() :
    - Ouvre une fenêtre graphique pour afficher l'évolution de la grille.
    - Permet une animation fluide avec un délai contrôlé.

#### Interactions :
- La classe Jeu utilise la classe Grille pour manipuler les cellules et gère l'interface utilisateur (console ou graphique).

### 2.5 main.cpp
Rôle : Interagit avec l'utilisateur pour configurer et lancer le jeu.

#### Fonctionnement :
  - Demande à l'utilisateur de fournir le chemin du fichier d'entrée.
  - Permet de choisir entre le mode console et le mode graphique.
  - Initialise une instance de Controleur avec les paramètres fournis.
  - Lance le mode correspondant (console ou graphique).

#### Interactions :
- Crée une instance de Controleur et délègue le contrôle à cette instance.

