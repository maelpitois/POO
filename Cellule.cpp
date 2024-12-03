#include "Cellule.h"

Cellule::Cellule() : vivante(false), prochainEtat(false) {}

Cellule::Cellule(bool etatInitial) : vivante(etatInitial), prochainEtat(false) {}

bool Cellule::estVivante() const {
    return vivante;
}

void Cellule::definirEtat(bool etat) {
    vivante = etat;
}

void Cellule::definirProchainEtat(bool etat) {
    prochainEtat = etat;
}

void Cellule::appliquerProchainEtat() {
    vivante = prochainEtat;
}
