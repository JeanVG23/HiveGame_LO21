#include "GameMaster.h"

int getInput(const std::string& prompt, int minValue, int maxValue) {
    int choice;
    do {
        std::cout << prompt;
        std::cin >> choice;

        // V�rifier si l'input est valide
        if (std::cin.fail() || choice < minValue || choice > maxValue) {
            std::cin.clear(); // R�initialiser l'�tat d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer les caract�res restants
            choice = minValue - 1; // Forcer une nouvelle saisie
            std::cout << "S'il vous pla�t, entrez un nombre valide entre " << minValue << " et " << maxValue << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer les caract�res restants
        }
    } while (choice < minValue || choice > maxValue);
    return choice;
}

Insecte* GameMaster::selectionnerInsecte() {
    int x = getInput("Abscisse de la position du pion � d�placer : ", plateau.getMinQ(), plateau.getMaxQ());
    int y = getInput("Ordonn�e de la position du pion � d�placer : ", plateau.getMinR(), plateau.getMaxR());

    Insecte* currentInsecte = plateau.getInsecteAtCoords(x, y);
    if (!currentInsecte) {
        std::cout << "Aucun pion � cette position. Veuillez r�essayer." << std::endl;
        return selectionnerInsecte(); // Appel r�cursif jusqu'� obtenir un pion valide
    }
    return currentInsecte;
}
