#ifndef INSECTE_H
#define INSECTE_H
#include "Hexagon.h"
#include <string>
#include <vector>

class Insecte
{
private:
    Hexagon coords;
    Insecte *dessus = nullptr;
    Insecte *dessous = nullptr;
    std::string nom;
public:
    Insecte(std::string nom, Hexagon coords) : nom(nom), coords(coords) {}
    Hexagon getCoords() const { return coords; }
    std::string getNom() const { return nom; }
    virtual std::vector<Hexagon> deplacementsPossibles() const = 0; // La m�thode est virtuelle pour que chaque enfant ait la sienne
};

class ReineAbeille : public Insecte {
public:
    ReineAbeille(Hexagon coords) : Insecte("Reine", coords) {}
    std::vector<Hexagon> deplacementsPossibles() const {
        // Retourne une liste de coordonn�es hexagonales
        return {};
    }
};

class Fourmi : public Insecte {
public:
    Fourmi(Hexagon coords) : Insecte("Fourmi", coords) {}

    std::vector<Hexagon> deplacementsPossibles() const {
        // Logique pour les d�placements possibles de la fourmi
        return {};
    }
};

class Sauterelle : public Insecte {
public:
    Sauterelle(Hexagon coords) : Insecte("Sauterelle", coords) {}

    std::vector<Hexagon> deplacementsPossibles() const {
        // Retourne une liste de coordonn�es hexagonales
        return {};
    }
};

class Coccinelle : public Insecte {
public:
    Coccinelle(Hexagon coords) : Insecte("Coccinelle", coords) {}

    std::vector<Hexagon> deplacementsPossibles() const {
        // Retourne une liste de coordonn�es hexagonales
        return {};
    }
};

#endif // INSECTE_H
