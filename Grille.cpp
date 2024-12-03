#include "Grille.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h> // Pour mkdir
#include <sys/types.h>
#include <cstring>    // Pour strerror
#if defined(_WIN32)
#include <direct.h>   // Pour _mkdir sur Windows
#endif

Grille::Grille() : lignes(0), colonnes(0) {}

bool Grille::chargerDepuisFichier(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);
    if (!fichier.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier : " << nomFichier << std::endl;
        return false;
    }

    // Lire les dimensions de la grille depuis la première ligne
    if (!(fichier >> lignes >> colonnes)) {
        std::cerr << "Erreur lors de la lecture des dimensions de la grille." << std::endl;
        return false;
    }

    // Initialiser la grille avec les dimensions lues
    cellules.resize(lignes, std::vector<Cellule>(colonnes));

    // Lire l'état des cellules
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            int etat;
            if (!(fichier >> etat)) {
                std::cerr << "Erreur lors de la lecture de l'état de la cellule (" << i << ", " << j << ")." << std::endl;
                return false;
            }
            if (etat != 0 && etat != 1) {
                std::cerr << "État de cellule invalide (" << etat << ") à la position (" << i << ", " << j << ")." << std::endl;
                return false;
            }
            cellules[i][j].definirEtat(etat == 1);
        }
    }
    return true;
}

bool Grille::sauvegarderDansFichier(const std::string& dossier, int iteration) const {
    // Créer le dossier si nécessaire
#if defined(_WIN32)
    if (_mkdir(dossier.c_str()) != 0 && errno != EEXIST) {
        std::cerr << "Erreur lors de la création du dossier " << dossier << ": " << strerror(errno) << std::endl;
        return false;
    }
#else
    if (mkdir(dossier.c_str(), 0777) != 0 && errno != EEXIST) {
        std::cerr << "Erreur lors de la création du dossier " << dossier << ": " << strerror(errno) << std::endl;
        return false;
    }
#endif

    // Construire le nom du fichier de sortie
    std::ostringstream nomFichier;
    nomFichier << dossier << "/iteration_" << iteration << ".txt";

    std::ofstream fichier(nomFichier.str());
    if (!fichier.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier pour écriture : " << nomFichier.str() << std::endl;
        return false;
    }

    // Écrire les dimensions en première ligne
    fichier << lignes << " " << colonnes << "\n";

    // Écrire l'état des cellules
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            fichier << (cellules[i][j].estVivante() ? '1' : '0');
            if (j < colonnes - 1) fichier << ' ';
        }
        fichier << '\n';
    }
    return true;
}

void Grille::afficherConsole() const {
    for (int y = 0; y < obtenirHauteur(); ++y) {
        for (int x = 0; x < obtenirLargeur(); ++x) {
            std::cout << (cellules[y][x].estVivante() ? '#' : '.');
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int Grille::compterVoisinsVivants(int x, int y) const {
    int compteur = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < colonnes && ny >= 0 && ny < lignes && cellules[ny][nx].estVivante()) {
                ++compteur;
            }
        }
    }
    return compteur;
}

bool Grille::mettreAJour() {
    bool aChange = false;

    for (int y = 0; y < obtenirHauteur(); ++y) {
        for (int x = 0; x < obtenirLargeur(); ++x) {
            int voisinsVivants = compterVoisinsVivants(x, y);
            bool prochainEtat = (cellules[y][x].estVivante() && (voisinsVivants == 2 || voisinsVivants == 3)) ||
                                (!cellules[y][x].estVivante() && voisinsVivants == 3);

            if (cellules[y][x].estVivante() != prochainEtat) {
                aChange = true;
            }
            cellules[y][x].definirProchainEtat(prochainEtat);
        }
    }

    for (int y = 0; y < obtenirHauteur(); ++y) {
        for (int x = 0; x < obtenirLargeur(); ++x) {
            cellules[y][x].appliquerProchainEtat();
        }
    }

    return aChange;
}

void Grille::dessiner(sf::RenderWindow& fenetre) const {
    float tailleCellule = 20.0f; // Taille des cellules à l'écran
    sf::RectangleShape rectangle(sf::Vector2f(tailleCellule, tailleCellule));

    for (int y = 0; y < lignes; ++y) {
        for (int x = 0; x < colonnes; ++x) {
            rectangle.setPosition(x * tailleCellule, y * tailleCellule);
            if (cellules[y][x].estVivante()) {
                rectangle.setFillColor(sf::Color::Green);
            } else {
                rectangle.setFillColor(sf::Color(200, 200, 200)); // Gris clair pour les cellules mortes
            }
            fenetre.draw(rectangle);
        }
    }
}
