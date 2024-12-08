#include "Vue.h"
#include <iostream>

void Vue::afficherConsole(const Grille& grille) {
    for (int y = 0; y < grille.obtenirHauteur(); ++y) {
        for (int x = 0; x < grille.obtenirLargeur(); ++x) {
            const auto& cellule = grille.obtenirCellules()[y][x];
            if (cellule.estObstacle()) {
                std::cout << (cellule.estVivante() ? "X" : "O");
            } else {
                std::cout << (cellule.estVivante() ? "#" : ".");
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Vue::afficherGraphique(const Grille& grille, sf::RenderWindow& fenetre) {
    float tailleCellule = 20.0f;
    sf::RectangleShape rectangle(sf::Vector2f(tailleCellule, tailleCellule));

    for (int y = 0; y < grille.obtenirHauteur(); ++y) {
        for (int x = 0; x < grille.obtenirLargeur(); ++x) {
            const auto& cellule = grille.obtenirCellules()[y][x];
            rectangle.setPosition(x * tailleCellule, y * tailleCellule);

            if (cellule.estObstacle()) {
                rectangle.setFillColor(cellule.estVivante() ? sf::Color::Red : sf::Color(100, 100, 100));
            } else {
                rectangle.setFillColor(cellule.estVivante() ? sf::Color::White : sf::Color::Black);
            }
            fenetre.draw(rectangle);
        }
    }
}
    