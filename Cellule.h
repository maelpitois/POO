#ifndef CELLULE_H
#define CELLULE_H

class Cellule {
private:
    bool vivante;       // État actuel de la cellule (vivante ou morte)
    bool prochainEtat;  // État suivant de la cellule

public:
    Cellule();                      // Constructeur par défaut
    Cellule(bool etatInitial);      // Constructeur avec état initial

    bool estVivante() const;        // Vérifie si la cellule est vivante
    void definirEtat(bool etat);    // Définit l'état actuel
    void definirProchainEtat(bool etat); // Définit l'état suivant
    void appliquerProchainEtat();   // Applique l'état suivant
};

#endif