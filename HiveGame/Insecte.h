#pragma once
#ifndef INSECTE_H
#define INSECTE_H
#include "Hexagon.h"
#include <string>
#include <vector>

class Joueur; // Déclaration anticipée de Joueur pour éviter l'inclusion circulaire
class Insecte
{
private:
    Hexagon coords;
    Insecte *dessus = nullptr;
    Insecte *dessous = nullptr;
    Joueur *owner;
    std::string nom;
public:
    Insecte(std::string nom, Hexagon coords) : nom(nom), coords(coords) {}
    Hexagon getCoords() const { return coords; }
    std::string getNom() const { return nom; }
    virtual std::vector<Hexagon> deplacementsPossibles() const = 0; // La méthode est virtuelle pour que chaque enfant ait la sienne
    void setDessus(Insecte *insecte){
        dessus = insecte;
    }
    void setDessous(Insecte *insecte){
        dessous = insecte;
    }
    void setCoords(Hexagon newCoords){
        coords = newCoords;
    }
};

class ReineAbeille : public Insecte {
public:
    ReineAbeille(Hexagon coords) : Insecte("Reine", coords) {}
    std::vector<Hexagon> deplacementsPossibles() const {
        // Retourne une liste de coordonnées hexagonales
        return {};
    }
};

class Fourmi : public Insecte {
public:
    Fourmi(Hexagon coords) : Insecte("Fourmi", coords) {}

    std::vector<Hexagon> deplacementsPossibles() const {
        // Logique pour les déplacements possibles de la fourmi
        return {};
    }
};

class Sauterelle : public Insecte {
public:
    Sauterelle(Hexagon coords) : Insecte("Sauterelle", coords) {}

    std::vector<Hexagon> deplacementsPossibles() const {
        // Retourne une liste de coordonnées hexagonales
        return {};
    }
};

class Coccinelle : public Insecte {
public:
    Coccinelle(Hexagon coords) : Insecte("Coccinelle", coords) {}

    std::vector<Hexagon> deplacementsPossibles() const {
        // Retourne une liste de coordonnées hexagonales
        return {};
    }
};
class Scarabee : public Insecte {
public:
    Scarabee(Hexagon coords) : Insecte("Scarabee", coords) {}

    std::vector<Hexagon> deplacementsPossibles() const {
        // Retourne une liste de coordonnées hexagonales
        return {};
    }
};
class Araignee : public Insecte {
public:
    Araignee(Hexagon coords) : Insecte("Araignée", coords) {}

    std::vector<Hexagon> deplacementsPossibles() const {
        // Retourne une liste de coordonnées hexagonales
        return {};
    }
};

class Moustique : public Insecte {
public:
    Moustique(Hexagon coords) : Insecte("Moustique", coords) {}

    std::vector<Hexagon> deplacementsPossibles() const {
        // Retourne une liste de coordonnées hexagonales
        return {};
    }
};
#endif // INSECTE_H
