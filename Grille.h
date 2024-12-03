#ifndef GRILLE_H
#define GRILLE_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Cellule.h"

class Grille {
private:
    int lignes;  // Nombre de lignes
    int colonnes;  // Nombre de colonnes
    std::vector<std::vector<Cellule>> cellules; // Grille de cellules

public:
    Grille();  // Constructeur par dÃ©faut

    bool chargerDepuisFichier(const std::string& nomFichier);
    bool sauvegarderDansFichier(const std::string& dossier, int iteration) const;
    void afficherConsole() const;
    bool mettreAJour();
    int compterVoisinsVivants(int x, int y) const;
    void dessiner(sf::RenderWindow& fenetre) const;

    int obtenirHauteur() const { return lignes; }
    int obtenirLargeur() const { return colonnes; }
};

#endif