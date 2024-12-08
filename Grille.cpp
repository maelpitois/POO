#include "Grille.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem> 
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
    namespace fs = std::filesystem;

    // Vérifier et créer le dossier si nécessaire
    try {
        if (!fs::exists(dossier)) {
            if (!fs::create_directories(dossier)) {
                std::cerr << "Erreur : Impossible de créer le dossier " << dossier << std::endl;
                return false;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Erreur lors de la manipulation du système de fichiers : " << e.what() << std::endl;
        return false;
    }

    // Construire le chemin complet du fichier de sortie
    fs::path cheminFichier = fs::path(dossier) / ("iteration_" + std::to_string(iteration) + ".txt");

    // Construire le nom du fichier de sortie
    std::ostringstream nomFichier;
    nomFichier << dossier << "/iteration_" << iteration << ".txt";

    // Ouvrir le fichier en écriture
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



