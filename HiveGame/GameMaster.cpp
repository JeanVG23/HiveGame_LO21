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
