#include "Insecte.h"


std::vector<Hexagon> getVoisins(Hexagon coords){
        std::vector<Hexagon> voisins;
        voisins.push_back(Hexagon(coords.getQ()+1, coords.getR()));
        voisins.push_back(Hexagon(coords.getQ()-1, coords.getR()));
        voisins.push_back(Hexagon(coords.getQ()+1, coords.getR()-1));
        voisins.push_back(Hexagon(coords.getQ()-1, coords.getR()-1));
        voisins.push_back(Hexagon(coords.getQ(), coords.getR()-1));
        voisins.push_back(Hexagon(coords.getQ(), coords.getR()+1));
        return voisins;
    }

std::vector<Hexagon> casesAdjacentesVides(Hexagon coords, std::map<Hexagon, Insecte*> p){
    std::vector<Hexagon> vides; //On d�clare la liste des hexagons adjacents vides, pour le moment elle ne contient rien
    std::vector<Hexagon> voisins = getVoisins(coords); //On d�clare la liste des voisins de l'hexagon cible
    for(size_t i=0; i<6; i++){
        for(size_t n=0; n<p.size(); n++){
            auto it = p.begin();
            std::advance(it, n); // On parcours chaque voisin et v�rifions si ses coordonn�es sont d�j� enregistr�es dans le plateau,
                                 //si c'est le cas cela signifie qu'il y a un insecte sur cette case
            if(it != p.end()){
                const Hexagon &hex = it->first;
                if(voisins.at(i).getQ() != hex.getQ() || voisins.at(i).getR()!=hex.getR()){
                    vides.push_back(voisins.at(i));
                }
            }
        }
    }
    return vides;
}

std::vector<Hexagon> casesAdjacentesOccupees(Hexagon coords, std::map<Hexagon, Insecte*> p){
    std::vector<Hexagon> occupees; //On d�clare la liste des hexagons adjacents occup�es, pour le moment elle ne contient rien
    std::vector<Hexagon> voisins = getVoisins(coords); //On d�clare la liste des voisins de l'hexagon cible
    std::vector<Hexagon> vides = casesAdjacentesVides(coords, p);
    for (size_t i=0; i<6; i++){
        for(size_t j=0; j<vides.size(); j++){
            if(voisins.at(i).getQ()!=vides.at(j).getQ() || voisins.at(i).getR()!=vides.at(j).getR()){
                occupees.push_back(voisins.at(i)); //On compare la liste des voisins et celle des cases adjacentes vides, la diff�rence correspond aux cases occup�es
            }
        }
    }
    return occupees;
}

bool Insecte::getLongueurChaine(std::map<Hexagon, Insecte*> p, std::map<Hexagon> chemin){
    std::vector<Hexagon> voisinOccupee = casesAdjacentesOccupees(this.getCoords(), p);
    for (size_t i=0; i<voisinOccupee.size(); i++){
        for(size_t j=0, j<chemin.size(); j++){
            if(voisinOccupee.at(i) != chemin.at(i)){
                chemin.push_back(voisinOccupee.at(i));
                Insecte::getLongueurChaine(p, chemin);
            }
        }
    }

}

















