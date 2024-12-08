#include "Controleur.h"
#include <iostream>
#include <string>

int main() {
    std::string fichierEntree;
    std::string mode;
    int delaiMs = 100;

    std::cout << "Entrez le chemin du fichier d'état initial : ";
    std::cin >> fichierEntree;

    std::cout << "Choisissez le mode (console/graphique) : ";
    std::cin >> mode;

    if (mode == "graphique") {
        std::cout << "Entrez le délai entre les itérations (en millisecondes) : ";
        std::cin >> delaiMs;

        if (delaiMs <= 0) {
            std::cerr << "Erreur : délai invalide, valeur par défaut (100 ms) utilisée." << std::endl;
            delaiMs = 100;
        }
    }

    Controleur controleur(fichierEntree, delaiMs);

    if (mode == "console") {
        controleur.lancerModeConsole();
    } else if (mode == "graphique") {
        controleur.lancerModeGraphique();
    } else {
        std::cerr << "Mode invalide. Veuillez choisir 'console' ou 'graphique'." << std::endl;
    }

    return 0;
}
