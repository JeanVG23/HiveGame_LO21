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
    Insecte(std::string nom, Hexagon coords) : nom(nom), coords(coords) {}
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
};


class ReineAbeille : public Insecte {
public:
    ReineAbeille(Hexagon coords) : Insecte("Reine", coords) {}
};


class Fourmi : public Insecte {
public:
    Fourmi(Hexagon coords) : Insecte("Fourmi", coords) {}
};


class Sauterelle : public Insecte {
public:
    Sauterelle(Hexagon coords) : Insecte("Sauterelle", coords) {}
};


class Coccinelle : public Insecte {
public:
    Coccinelle(Hexagon coords) : Insecte("Coccinelle", coords) {}
};


class Scarabee : public Insecte {
public:
    Scarabee(Hexagon coords) : Insecte("Scarabee", coords) {}
};


class Araignee : public Insecte {
public:
    Araignee(Hexagon coords) : Insecte("Araign�e", coords) {}
};


class Moustique : public Insecte {
public:
    Moustique(Hexagon coords) : Insecte("Moustique", coords) {}
};
std::vector<Hexagon> deplacementsPossiblesReineAbeille(const Insecte *i, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesFourmi(Hexagon coords, std::map<Hexagon, Insecte*> p, std::vector<Hexagon>& cheminInsecte, std::set<Hexagon>& deplacements);
std::vector<Hexagon> deplacementsPossiblesSauterelle(const Insecte *i, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesCoccinelle(const Insecte *i, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesScarabee(const Insecte *i, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesAraignee(const Insecte *i, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesMoustique(const Insecte *i, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> getVoisins(Hexagon coords);
std::vector<Hexagon> casesAdjacentesVides(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> casesAdjacentesOccupees(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> getLongueurChaine(Insecte *i, std::map<Hexagon, Insecte*> p, std::vector<Hexagon> chemin);
bool getChaineBrisee(Insecte *i, std::map<Hexagon, Insecte*> p, std::vector<Hexagon> chemin);
bool getGlissementPossible(const  Insecte *i, const  std::map<Hexagon, Insecte*> p, const Hexagon destination);

#endif // INSECTE_H
