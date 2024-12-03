#include "Jeu.h"
#include <iostream>
#include <fstream>
#include <sstream>

Jeu::Jeu(const std::string& fichierEntree, int delaiMs)
    : delaiMs(delaiMs), fichierEntree(fichierEntree) {
    if (!grille.chargerDepuisFichier(fichierEntree)) {
        std::cerr << "Erreur lors du chargement du fichier d'entrée : " << fichierEntree << std::endl;
    }
}

void Jeu::executerModeConsole() {
    int iterationsMax = 1000;
    int iteration = 0;

    // Créer le nom du dossier de sortie
    std::string dossierSortie = fichierEntree + "_out";

    // Sauvegarder l'état initial
    if (!grille.sauvegarderDansFichier(dossierSortie, iteration)) {
        std::cerr << "Erreur lors de la sauvegarde de l'état initial." << std::endl;
    }

    while (iteration < iterationsMax) {
        std::cout << "Itération " << iteration << ":" << std::endl;
        grille.afficherConsole();

        if (!grille.mettreAJour()) {
            std::cout << "L'automate s'est stabilisé à l'itération " << iteration << "." << std::endl;
            break;
        }

        iteration++;

        // Sauvegarder l'état actuel
        if (!grille.sauvegarderDansFichier(dossierSortie, iteration)) {
            std::cerr << "Erreur lors de la sauvegarde de l'état à l'itération " << iteration << "." << std::endl;
        }
    }
}

void Jeu::executerModeGraphique() {
    grille.afficherConsole(); // Afficher la grille initiale dans la console

    float tailleCellule = 20.0f; // Taille des cellules
    sf::RenderWindow fenetre(sf::VideoMode(grille.obtenirLargeur() * tailleCellule, grille.obtenirHauteur() * tailleCellule), "Jeu de la Vie");

    bool enCours = true;

    while (fenetre.isOpen()) {
        sf::Event evenement;
        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == sf::Event::Closed)
                fenetre.close();
        }

        if (enCours) {
            fenetre.clear(sf::Color::White);
            grille.dessiner(fenetre);
            fenetre.display();

            if (!grille.mettreAJour()) {
                std::cout << "L'automate s'est stabilisé." << std::endl;
                enCours = false;
            }

            // Pause pour ajuster le délai entre les itérations
            sf::sleep(sf::milliseconds(delaiMs));
        }
    }
}
