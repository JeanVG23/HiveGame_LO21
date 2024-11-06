#include "Plateau.h"
#include "GameMaster.h"

int main() {
    // Création du plateau de jeu
    Plateau plateau;

    /*// Création et placement des insectes sur le plateau
    Insecte* reineAbeille = new ReineAbeille(Hexagon(0, 0));
    Insecte* fourmi = new Fourmi(Hexagon(1, 0));
    Insecte* sauterelle = new Sauterelle(Hexagon(-1, 1));
    Insecte* araignee = new Fourmi(Hexagon(0, 1));
    Insecte* coccinelle = new Coccinelle(Hexagon(1, 1));

    // Ajout des insectes au plateau
    plateau.ajouterInsecte(reineAbeille, Hexagon(0, 0));
    plateau.ajouterInsecte(fourmi, Hexagon(1, 0));
    plateau.ajouterInsecte(sauterelle, Hexagon(-1, 1));
    plateau.ajouterInsecte(araignee, Hexagon(0, 1));
    plateau.ajouterInsecte(coccinelle, Hexagon(1, 1));

    // Affichage du plateau pour vérifier le placement initial
    plateau.afficherPlateau();
    */
    // Initialisation du GameMaster pour gérer le jeu
    GameMaster master(plateau);
    master.startGame();
    /*
    // Libération de la mémoire
    delete reineAbeille;
    delete fourmi;
    delete sauterelle;
    delete araignee;
    delete coccinelle;
    */
    return 0;
}
