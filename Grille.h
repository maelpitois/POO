#ifndef GRILLE_H
#define GRILLE_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>  
#include "Cellule.h"

// Classe reprÃ©sentant la grille contenant les cellules.
class Grille {
private:
    int lignes;  // Nombre de lignes dans la grille
    int colonnes; // Nombre de colonnes dans la grille
    std::vector<std::vector<Cellule>> cellules; // Matrice des cellules

public:
    Grille();

    bool chargerDepuisFichier(const std::string& nomFichier);
    bool sauvegarderDansFichier(const std::string& dossier, int iteration) const;
    bool mettreAJour();
    int compterVoisinsVivants(int x, int y) const;

    int obtenirHauteur() const { return lignes; }
    int obtenirLargeur() const { return colonnes; }
    const std::vector<std::vector<Cellule>>& obtenirCellules() const { return cellules; }
};

#endif