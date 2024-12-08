#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include "Grille.h"
#include "Vue.h"

class Controleur {
private:
    Vue vue;
    Grille grille;
    int delaiMs;
    std::string fichierEntree;

public:
    Controleur(const std::string& fichierEntree, int delai);
    void lancerModeConsole();
    void lancerModeGraphique();
};

#endif