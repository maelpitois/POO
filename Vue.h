#ifndef VUE_H
#define VUE_H

#include "Grille.h"
#include <SFML/Graphics.hpp>

// Classe gerant l'affichage de la grille (console ou graphique)
class Vue {
public:
    static void afficherConsole(const Grille& grille);
    static void afficherGraphique(const Grille& grille, sf::RenderWindow& fenetre);
};

#endif