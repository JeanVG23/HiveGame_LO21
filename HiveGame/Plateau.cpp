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

void Plateau::afficherPlateauAvecPossibilites(const std::vector<Hexagon>& emplacementsPossibles) const {
    // Créer un nouveau plateau temporaire pour afficher les possibilités
    Plateau plateauTemp = *this;

    // Ajouter les emplacements possibles sous forme d'insectes "X" sur le plateau temporaire
    for (const Hexagon& hex : emplacementsPossibles) {
        if (plateauTemp.plateauMap.find(hex) == plateauTemp.plateauMap.end()) {
            plateauTemp.plateauMap[hex] = new InsecteFictif(hex);
        }
    }

    // Afficher le plateau temporaire avec les emplacements possibles
    plateauTemp.afficherPlateau();

    // Nettoyage automatique du plateau temporaire lorsqu'il est hors de portée
}

