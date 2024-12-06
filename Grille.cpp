#include "Grille.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h> // Pour mkdir
#include <sys/types.h>
#include <cstring>    // Pour strerror

Grille::Grille() : lignes(0), colonnes(0) {}

bool Grille::chargerDepuisFichier(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);
    if (!fichier.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << std::endl;
        return false;
    }

    // Lire les dimensions
    if (!(fichier >> lignes >> colonnes)) {
        std::cerr << "Erreur : Format invalide dans le fichier, dimensions non lisibles." << std::endl;
        return false;
    }

    // Redimensionner la grille
    cellules.resize(lignes, std::vector<Cellule>(colonnes));

    // Lire les cellules ligne par ligne
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            int etat;
            if (!(fichier >> etat)) {
                std::cerr << "Erreur : Lecture invalide à la cellule (" << i << ", " << j << ")." << std::endl;
                return false;
            }
            if (etat < 0 || etat > 3) {
                std::cerr << "Erreur : État de cellule invalide (" << etat << ") à la position (" << i << ", " << j << ")." << std::endl;
                return false;
            }

            // Créer la cellule selon l'état
            bool vivant = (etat == 1 || etat == 3);
            bool obstacle = (etat == 2 || etat == 3);
            cellules[i][j] = Cellule(vivant, obstacle);
        }
    }

    return true;
}


bool Grille::sauvegarderDansFichier(const std::string& dossier, int iteration) const {
    // Créer le dossier si nécessaire

    if (mkdir(dossier.c_str(), 0777) != 0 && errno != EEXIST) {
         // std::cerr "caractere error =  Pour print pour une erreur"
        std::cerr << "Erreur lors de la création du dossier " << dossier << ": " << strerror(errno) << std::endl;
        return false;
    }


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
            if (cellules[i][j].estObstacle()) {
                fichier <<(cellules[i][j].estVivante() ? 'X' : 'O');
            } else 
                fichier << (cellules[i][j].estVivante() ? '#' : '.');
            if (j < colonnes - 1) fichier << ' ';
        }
        fichier << '\n';
    }
    return true;
}

void Grille::afficherConsole() const {
    for (int y = 0; y < obtenirHauteur(); ++y) {
        for (int x = 0; x < obtenirLargeur(); ++x) {
            if (cellules[y][x].estObstacle()) {
                std::cout <<(cellules[y][x].estVivante() ? 'X' : 'O');
            } else 
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

    // Calculer les prochains états pour chaque cellule
    for (int y = 0; y < lignes; ++y) {
        for (int x = 0; x < colonnes; ++x) {
            if (cellules[y][x].estObstacle()) {
                continue; // Ignorer les cellules obstacles
            }

            int voisinsVivants = compterVoisinsVivants(x, y);
            bool prochainEtat = (cellules[y][x].estVivante() && (voisinsVivants == 2 || voisinsVivants == 3)) ||
                                (!cellules[y][x].estVivante() && voisinsVivants == 3);

            if (cellules[y][x].estVivante() != prochainEtat) {
                aChange = true; // Au moins une cellule a changé
            }
            cellules[y][x].definirProchainEtat(prochainEtat);
        }
    }

    // Appliquer les états calculés
    for (int y = 0; y < lignes; ++y) {
        for (int x = 0; x < colonnes; ++x) {
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
            if (cellules[y][x].estObstacle()) {
                rectangle.setFillColor(cellules[y][x].estVivante() ? sf::Color::Red : sf::Color(100, 100, 100));//Couleur Gris clair 
            } else {
                rectangle.setFillColor(cellules[y][x].estVivante() ? sf::Color::White : sf::Color(0, 0, 0)); //Couleur Noir
            }
            fenetre.draw(rectangle);
        }
    }
}
