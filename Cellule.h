#ifndef CELLULE_H
#define CELLULE_H

class Cellule {
private:
    bool vivante;       // État actuel de la cellule
    bool prochainEtat;  // État futur de la cellule
    bool obstacle;      // Indique si la cellule est un obstacle (true = obstacle)

public:
    Cellule();                      // Constructeur par défaut
    Cellule(bool etatInitial, bool estObstacle = false); // Constructeur avec état initial et option obstacle

    bool estVivante() const;        // Retourne si la cellule est vivante
    bool estObstacle() const;       // Retourne si la cellule est un obstacle
    void definirEtat(bool etat);    // Définit l'état actuel
    void definirProchainEtat(bool etat); // Définit l'état futur
    void appliquerProchainEtat();   // Applique l'état futur
    void definirObstacle(bool estObstacle); // Définit si la cellule est un obstacle
};

#endif
