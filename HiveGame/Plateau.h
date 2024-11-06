#ifndef PLATEAU_H
#define PLATEAU_H
#pragma ONCE
#include <iostream>
#include <map>
#include <vector>
#include "Hexagon.h"
#include "Insecte.h"
#include "Joueur.h"

class Plateau {
private:
    std::map<Hexagon, Insecte*> plateauMap;
    std::vector<Insecte*> insectesSurPlateau; // On peut supprimer et faire un deck de joueur, quand un joueur pose un insecte, alors l'insecte disparait de son deck gr�ce � ajouter Insecte
    //std::vector<Action*> historiqueDesActions;
    //std::vector<Extension*> extensionsActivees;
    int nombreRetoursArriere;
    unsigned int nombreTours;
    int minR, maxR, minQ, maxQ;

public:
    Plateau() : nombreRetoursArriere(3), nombreTours(0), minR(0), maxR(0), minQ(0), maxQ(0) {} // Initialisation par d�faut
    unsigned int getTour(){return nombreTours;}
    void incrementerTour(){++nombreTours;}

    void ajouterInsecte(Insecte* insecte, Hexagon position);

    void deplacerInsecte(Insecte* insecte, const Hexagon& nouvellePosition) {
        plateauMap.erase(insecte->getCoords()); // Retirer l'insecte de sa position actuelle
        insecte->setCoords(nouvellePosition); // Mettre � jour les coordonn�es de l'insecte
        plateauMap[nouvellePosition] = insecte; // Ajouter l'insecte � la nouvelle position
        mettreAJourLimites(nouvellePosition); // Mettre � jour les limites
    }


    void superposerInsecte(Insecte* currentInsecte, Insecte* newInsecte) {
        newInsecte->setDessous(currentInsecte);
        currentInsecte->setDessus(newInsecte);
        newInsecte->setCoords(currentInsecte->getCoords());
        plateauMap[newInsecte->getCoords()] = newInsecte;
        mettreAJourLimites(newInsecte->getCoords()); // Mettre � jour les limites lors de la superposition
    }


    void afficherPlateau() const {
        // Utiliser les limites minR, maxR, minQ, maxQ pour afficher le plateau
        for (int r = minR; r <= maxR; ++r) {
            if (r % 2 != 0) std::cout << "  "; // pour essayer de faire ressembler � un hexagone ptdr c immonde

            for (int q = minQ; q <= maxQ; ++q) {
                Hexagon h(q, r);
                if (plateauMap.count(h)) {
                    std::cout << plateauMap.at(h)->getNom() << "[" << h.getQ() << " " << h.getR() << "] "; // L'insecte existe alors je r�cup�re son nom
                } else {
                    std::cout << ".[" << h.getQ() << " " << h.getR() << "] "; // Aucun insecte � cet emplacement
                }
            }
            std::cout << std::endl;
        }
    }

    void afficherPlateauAvecPossibilites(const std::vector<Hexagon>& emplacementsPossibles) const;

    int getMinR() const { return minR; }
    int getMaxR() const { return maxR; }
    int getMinQ() const { return minQ; }
    int getMaxQ() const { return maxQ; }

    void mettreAJourLimites(const Hexagon& coords) {
        if (coords.getR() < minR) minR = coords.getR();
        if (coords.getR() > maxR) maxR = coords.getR();
        if (coords.getQ() < minQ) minQ = coords.getQ();
        if (coords.getQ() > maxQ) maxQ = coords.getQ();
    }

    void afficherPossibilitePlacement(Insecte* insecte);
    void afficherPlateauAvecPossibilites(const std::vector<Hexagon>& emplacementsPossibles);
    void afficherPossibiliteDeplacement(Insecte* insecte, const std::map<Hexagon, Insecte*>& plateau);

    Insecte* getInsecteAtCoords(int q , int r){
        Hexagon h(q , r);
        if (!(plateauMap.count(h))){return nullptr;}
        return plateauMap[h];
    }
    // Ajout dans la section publique de Plateau
    const std::vector<Insecte*>& getInsectesSurPlateau() const {
        return insectesSurPlateau;
    }
    std::map<Hexagon, Insecte*> getPlateauMap() {
        return plateauMap;
    }
    std::vector<Hexagon> getVoisinsInsectePlateau(Insecte *insecte){
        Hexagon coords = insecte->getCoords();
        std::vector<Hexagon> voisins;
        voisins.push_back(Hexagon(coords.getQ()+1, coords.getR()));
        voisins.push_back(Hexagon(coords.getQ()-1, coords.getR()));
        voisins.push_back(Hexagon(coords.getQ()+1, coords.getR()-1));
        voisins.push_back(Hexagon(coords.getQ()-1, coords.getR()-1));
        voisins.push_back(Hexagon(coords.getQ(), coords.getR()-1));
        voisins.push_back(Hexagon(coords.getQ(), coords.getR()+1));
        return voisins;
    }
    Insecte *getReineAbeille(Joueur *joueur) const{
        for (const auto& [key, value] : plateauMap){ // https://en.cppreference.com/w/cpp/container/map
            if (value->getNom() == "Reine" && value->getOwner() == joueur){
                return value;
            }
        }
        return nullptr;
    }
    bool estEntouree(Insecte *insecte) {
        std::vector<Hexagon> voisins = getVoisinsInsectePlateau(insecte);
        for (const Hexagon& voisin : voisins) {
            // V�rifiez si la case voisine est occup�e
            if (plateauMap.find(voisin) == plateauMap.end()) {
                return false; // Si une case voisine est vide, la reine n'est pas entour�e
            }
        }
        return true; // Toutes les cases voisines sont occup�es
    }

};

#endif // PLATEAU_H
