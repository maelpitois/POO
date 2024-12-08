#include "Cellule.h"

// Constructeur par défaut
Cellule::Cellule() : vivante(false), prochainEtat(false), obstacle(false) {}

// Constructeur avec état initial et option obstacle
Cellule::Cellule(bool etatInitial, bool estObstacle)
    : vivante(etatInitial), prochainEtat(false), obstacle(estObstacle) {}

// Retourne si la cellule est vivante
bool Cellule::estVivante() const {
    return vivante;
}

// Retourne si la cellule est un obstacle
bool Cellule::estObstacle() const {
    return obstacle;
}

// Définit l'état actuel
void Cellule::definirEtat(bool etat) {
    if (!obstacle) { // Ne change pas si la cellule est un obstacle
        vivante = etat;
    }
}

// Définit l'état futur
void Cellule::definirProchainEtat(bool etat) {
    if (!obstacle) { // Ne change pas si la cellule est un obstacle
        prochainEtat = etat;
    }
}

// Applique l'état futur
void Cellule::appliquerProchainEtat() {
    if (!obstacle) { // Ne change pas si la cellule est un obstacle
        vivante = prochainEtat;
    }
}

// Définit si la cellule est un obstacle
void Cellule::definirObstacle(bool estObstacle) {
    obstacle = estObstacle;
}