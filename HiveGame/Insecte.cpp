#include "Insecte.h"


std::vector<Hexagon> getVoisins(Hexagon coords)const;{
        std::vector voisins;
        voisins.push_back(Hexagon(coords.q+1, coords.r));
        voisins.push_back(Hexagon(coords.q, coords.r+1));
        voisins.push_back(Hexagon(coords.q-1, coords.r));
        voisins.push_back(Hexagon(coords.q, coords.r-1));
        voisins.push_back(Hexagon(coords.q+1, coords.r-1));
        voisins.push_back(Hexagon(coords.q-1, coords.r+1));
        return voisins;
    }

std::vector<Hexagon> casesAdjacentesVides(Hexagon coords, Plateau p){
    std::vector<Hexagon> vides; //On d�clare la liste des hexagons adjacents vides, pour le moment elle ne contient rien

    std::vector<Hexagon> voisins = getVoisins(coords); //On d�clare la liste des voisins de l'hexagon cible
    for(size_t i; i<6; i++){
        for(size_t n; n<p.plateauMap.size(); n++){
            auto it = p.plateauMap.begin();
            std::advance(it, n); // On parcours chaque voisins et v�rifions si ses coordonn�es sont d�j� enregistr�es dans le plateau,
                                 //si c'est le cas cela signifie qu'il y a un insecte sur cette case
            if(it != p.plateauMap.end()){
                const Hexagon &hex = it->first;
                if(voisins.at(i).getQ() != hex.getQ() || voisins.at(i).getR()!=hex.getR()){
                    vides.push_back(voisins.at(i));
                }
            }
        }
    }
    return vides;
}

