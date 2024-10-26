#ifndef PLATEAU_H
#define PLATEAU_H

#include <iostream>
#include <map>
#include <vector>
#include "Hexagon.h"
#include "Insecte.h"

class Plateau {
private:
    std::map<Hexagon, Insecte*> plateauMap;
    std::vector<Insecte*> insectesSurPlateau; // On peut supprimer et faire un deck de joueur, quand un joueur pose un insecte, alors l'insecte disparait de son deck gr�ce � ajouter Insecte
    //std::vector<Action*> historiqueDesActions;
    //std::vector<Extension*> extensionsActivees;
    int nombreRetoursArriere;
    int nombreTours;
    int minR, maxR, minQ, maxQ;

public:
    Plateau() : nombreRetoursArriere(3), nombreTours(0), minR(0), maxR(0), minQ(0), maxQ(0) {} // Initialisation par d�faut

    void ajouterInsecte(Insecte* insecte) {
        plateauMap[insecte->getCoords()] = insecte; // Ajouter � la carte
        insectesSurPlateau.push_back(insecte); // Garder une r�f�rence � l'insecte
        mettreAJourLimites(insecte->getCoords()); // Mettre � jour les limites lors de l'ajout
    }

    void deplacerInsecte(Insecte* insecte, const Hexagon& nouvellePosition) {
        // Mettre � jour la position de l'insecte
        mettreAJourLimites(insecte->getCoords());
    }

    void superposerInsecte(Insecte* currentInsecte, Insecte* newInsecte) {
        newInsecte->setDessous(currentInsecte);
        currentInsecte->setDessus(newInsecte);
        currentInsecte->setCoords(newInsecte->getCoords());
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
                    std::cout << plateauMap.at(h)->getNom() << "   "; // L'insecte existe alors je r�cup�re son nom
                } else {
                    std::cout << ".   ";  // Aucun insecte � cet emplacement
                }
            }
            std::cout << std::endl;
        }
    }
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
};

#endif // PLATEAU_H
