#pragma once
#ifndef INSECTE_H
#define INSECTE_H
#include "Hexagon.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>


class Joueur; // D�claration anticip�e de Joueur pour �viter l'inclusion circulaire


class Insecte
{
private:
    Hexagon coords;
    Insecte *dessus = nullptr;
    Insecte *dessous = nullptr;
    Joueur *owner;
    std::string nom;
public:
    Insecte& operator =(const Insecte &i){
        if(this != &i){
            coords = i.getCoords();
            dessus = i.dessus;
            dessous = i.dessous;
            owner = i.owner;
            nom = i.getNom();
        }
        return *this;
    }
    Insecte(std::string nom, Hexagon coords) : coords(coords) , nom(nom) {}
    Hexagon getCoords() const { return coords; }
    std::string getNom() const { return nom; }
    void setDessus(Insecte *insecte){
        dessus = insecte;
    }
    void setDessous(Insecte *insecte){
        dessous = insecte;
    }
    void setCoords(Hexagon newCoords){
        coords = newCoords;
    }

    virtual std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p) = 0;

    Joueur *getOwner() const {return owner;}

    std::vector<Hexagon> placementsPossiblesDeBase(const std::map<Hexagon, Insecte*>& plateau) const;
};


class ReineAbeille : public Insecte {
public:
    ReineAbeille(Hexagon coords) : Insecte("Reine", coords) {}
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p) override;
    bool estEntouree(const std::map<Hexagon, Insecte*>& p) const;
};


class Fourmi : public Insecte {
public:
    Fourmi(Hexagon coords) : Insecte("Fourmi", coords) {}
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p);
};


class Sauterelle : public Insecte {
public:
    Sauterelle(Hexagon coords) : Insecte("Sauterelle", coords) {}
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p);
};


class Coccinelle : public Insecte {
public:
    Coccinelle(Hexagon coords) : Insecte("Coccinelle", coords) {}
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p);
};


class Scarabee : public Insecte {
public:
    Scarabee(Hexagon coords) : Insecte("Scarabee", coords) {}
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p);
};


class Araignee : public Insecte {
public:
    Araignee(Hexagon coords) : Insecte("Araign�e", coords) {}
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p);
};


class Moustique : public Insecte {
public:
    Moustique(Hexagon coords) : Insecte("Moustique", coords) {}
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p);
};

class InsecteFictif : public Insecte {
public:
    InsecteFictif(Hexagon coords) : Insecte("X", coords) {}

    // Implémentation correcte de la fonction pure virtuelle
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p) override {
        return {}; // Pas de déplacement pour cet insecte fictif
    }
};



std::vector<Hexagon> deplacementsPossiblesReineAbeille(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesFourmi(Hexagon coords, std::map<Hexagon, Insecte*> p, std::vector<Hexagon>& cheminInsecte, std::set<Hexagon>& deplacements);
std::vector<Hexagon> deplacementsPossiblesSauterelle(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesCoccinelle(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesScarabee(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesAraignee(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesMoustique(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> getVoisins(Hexagon coords);
std::vector<Hexagon> casesAdjacentesVides(const Hexagon& coords, const std::map<Hexagon, Insecte*>& plateau);
std::vector<Hexagon> casesAdjacentesOccupees(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> getLongueurChaine(Insecte *i, std::map<Hexagon, Insecte*> p, std::vector<Hexagon> chemin);
bool getChaineBrisee(Insecte *i, std::map<Hexagon, Insecte*> p, std::vector<Hexagon> chemin);
bool getGlissementPossible(const  Insecte *i, const  std::map<Hexagon, Insecte*> p, const Hexagon destination);

#endif // INSECTE_H
