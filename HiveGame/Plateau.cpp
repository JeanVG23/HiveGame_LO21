#include "Plateau.h"

void Plateau::ajouterInsecte(Insecte* insecte, Hexagon position) {
    std::vector<Hexagon> emplacementsValides = insecte->placementsPossiblesDeBase(plateauMap);

    bool positionValide = std::find(emplacementsValides.begin(), emplacementsValides.end(), position) != emplacementsValides.end();

    if (nombreTours == 0) {
        std::cout << "Placement obligatoire du premier insecte." << std::endl;
        if (plateauMap.empty()) {
            plateauMap[position] = insecte;
            insectesSurPlateau.push_back(insecte);
            mettreAJourLimites(position);
            return;
        } else {
            std::cerr << "Erreur : placement initial incorrect." << std::endl;
            return;
        }
    }

    if (nombreTours == 4) {
        Insecte* reine = insecte->getOwner()->contientInsecte("Reine");
        if (reine && !plateauMap.count(reine->getCoords())) {
            if (positionValide) {
                plateauMap[position] = reine;
                insectesSurPlateau.push_back(reine);
                mettreAJourLimites(position);
                return;
            } else {
                std::cerr << "Erreur : emplacement invalide pour la Reine." << std::endl;
                return;
            }
        }
    }

    if (!positionValide) {
        std::cerr << "Erreur : emplacement invalide." << std::endl;
        return;
    }

    if (plateauMap.count(position)) {
        Insecte* insecteEnDessous = plateauMap[position];
        superposerInsecte(insecteEnDessous, insecte);
    } else {
        plateauMap[position] = insecte;
        insectesSurPlateau.push_back(insecte);
        mettreAJourLimites(position);
    }
}

void Plateau::afficherPossibiliteDeplacement(Insecte* insecte, const std::map<Hexagon, Insecte*>& plateau) {
    // Récupérer les déplacements possibles
    std::vector<Hexagon> deplacements = insecte->deplacementsPossibles(plateau);

    // Afficher les déplacements
    std::cout << "Déplacements possibles pour " << insecte->getNom() << " :\n";
    for (const Hexagon& hex : deplacements) {
        std::cout << "[" << hex.getQ() << ", " << hex.getR() << "]\n";
    }

    // Afficher visuellement sur le plateau si besoin
    afficherPlateauAvecPossibilites(deplacements);
}

void Plateau::afficherPossibilitePlacement(Insecte* insecte) {
    std::vector<Hexagon> placements;

    if (nombreTours == 1) {
        // Premier tour avec un insecte adverse placé : on place autour de cet insecte
        auto it = plateauMap.begin();
        placements = getVoisins(it->first);
    }else {
        placements = insecte->placementsPossiblesDeBase(plateauMap);
    }

    // Afficher le plateau avec les emplacements possibles marqués
    std::cout << "Emplacements possibles pour placer " << insecte->getNom() << " :\n";
    for (const Hexagon& hex : placements) {
        std::cout << "[" << hex.getQ() << ", " << hex.getR() << "]\n";
    }
    afficherPlateauAvecPossibilites(placements);
}

void Plateau::afficherPlateauAvecPossibilites(const std::vector<Hexagon>& emplacementsPossibles) {
    // Créer une copie temporaire du plateau
    std::map<Hexagon, Insecte*> plateauTemp = plateauMap;

    // Ajouter des insectes fictifs aux emplacements possibles
    for (const Hexagon& hex : emplacementsPossibles) {
        if (plateauTemp.find(hex) == plateauTemp.end()) { // Si l'emplacement est vide dans le plateau original
            plateauTemp[hex] = new InsecteFictif(hex);    // Ajouter un insecte fictif
        }
    }

    // Étendre les limites du plateau pour inclure tous les emplacements possibles
    for (const auto& [position, _] : plateauTemp) {
        if (position.getQ() < minQ) minQ = position.getQ();
        if (position.getQ() > maxQ) maxQ = position.getQ();
        if (position.getR() < minR) minR = position.getR();
        if (position.getR() > maxR) maxR = position.getR();
    }

    // Afficher le plateau avec les insectes fictifs
    for (int r = minR; r <= maxR; ++r) {
        if (r % 2 != 0) std::cout << "  ";  // Décalage pour aligner les hexagones visuellement

        for (int q = minQ; q <= maxQ; ++q) {
            Hexagon h(q, r);
            if (plateauTemp.count(h)) {
                std::cout << plateauTemp[h]->getNom() << "[" << h.getQ() << "," << h.getR() << "] ";
            } else {
                std::cout << ".[" << h.getQ() << "," << h.getR() << "] ";
            }
        }
        std::cout << std::endl;
    }

    // Nettoyer les insectes fictifs ajoutés au plateau temporaire
    for (const Hexagon& hex : emplacementsPossibles) {
        if (plateauTemp[hex]->getNom() == "?") {  // Vérifie si c'est un insecte fictif
            delete plateauTemp[hex];
            plateauTemp.erase(hex);
        }
    }
}

