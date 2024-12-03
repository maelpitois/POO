#ifndef JEU_H
#define JEU_H

#include "Grille.h"
#include <SFML/Graphics.hpp>

class Jeu {
private:
    Grille grille;
    int delaiMs; // Délai entre les itérations pour le mode graphique
    std::string fichierEntree;

public:
    Jeu(const std::string& fichierEntree, int delaiMs);
    void executerModeConsole();    // Mode console
    void executerModeGraphique();  // Mode graphique
};

#endif