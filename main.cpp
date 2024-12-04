#include <iostream>
#include <string>
#include "Jeu.h"

int main() {
    std::string fichierEntree;
    std::string mode;
    int delaiMs = 100; // Valeur par défaut pour le délai en millisecondes

    // Demander à l'utilisateur de fournir le chemin du fichier d'état initial
    std::cout << "Entrez le chemin du fichier d'état initial : ";
    //std::cin Enregiste la valeur d'entrer
    std::cin >> fichierEntree;

    // Demander à l'utilisateur de choisir le mode d'exécution
    std::cout << "Choisissez le mode (console/graphique) : ";
    //std::cin Enregiste la valeur d'entrer
    std::cin >> mode;

    if (mode == "graphique") {
        // Demander à l'utilisateur de spécifier le délai pour le mode graphique
        std::cout << "Entrez le délai entre les itérations (en millisecondes) : ";
        //std::cin Enregiste la valeur d'entrer
        std::cin >> delaiMs;

        // Valider le délai saisi
        if (delaiMs <= 0) {
        // std::cerr "caractere error =  Pour print pour une erreur"
            std::cerr << "Délai invalide. Utilisation de la valeur par défaut de 100 ms." << std::endl;
            delaiMs = 100;
        }
    }

    // Initialiser le jeu avec le nouveau constructeur
    Jeu jeu(fichierEntree, delaiMs);

    // Lancer le mode correspondant
    if (mode == "console") {
        jeu.executerModeConsole();
    } else if (mode == "graphique") {
        jeu.executerModeGraphique();
    } else {
        // std::cerr "caractere error =  Pour print pour une erreur"
        std::cerr << "Mode invalide ! Veuillez choisir 'console' ou 'graphique'." << std::endl;
    }

    return 0;
}