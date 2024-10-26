#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "Joueur.h"
#include "Plateau.h"
#include <iostream>
#include <memory>
#include <limits>
int getInput(const std::string& prompt, int minValue, int maxValue);
class GameMaster {
private:
    Plateau plateau;
    Joueur *joueur1;
    Joueur *joueur2;
    unsigned int mode;
    unsigned int tour;
public:
    GameMaster() : joueur1(nullptr), joueur2(nullptr) , mode(0) {}
    GameMaster(Plateau plateau) : joueur1(nullptr), joueur2(nullptr) , mode(0) , plateau(plateau){}
    void startGame() {
        std::cout << "\nD�marrage du jeu HiveGame en cours...\n" << std::endl;
        mode = getInput("Merci de s�lectionner le mode de jeu :\n1 - Joueur vs Joueur (JvJ)\n2 - Joueur vs IA (JvIA)\n", 1, 2);
        std::cout << "Vous avez s�lectionn� le mode : " << (mode == 1 ? "JvJ" : "JvIA") << "\n";
        if (mode == 1) {
            std::string nom;
            std::cout << "\nMerci de saisir le nom du premier Joueur" << std::endl;
            std::cin >> nom;

            joueur1 = new Joueur(nom);  // Cr�er le joueur 1
            std::cout << "Joueur 1 cr�� : " << joueur1->getName() << std::endl;

            std::cout << "\nMerci de saisir le nom du second Joueur" << std::endl;
            std::cin >> nom;

            joueur2 = new Joueur(nom);  // Cr�er le joueur 2
            std::cout << "Joueur 2 cr�� : " << joueur2->getName() << std::endl;

            std::cout << "\nHiveGame : Le joueur 1 sera " << joueur1->getName()
                      << " et le joueur 2 sera " << joueur2->getName() << ".\n";
        } else {
            std::string nom;
            std::cout << "\nMerci de saisir le nom du Joueur" << std::endl;
            std::cin >> nom;

            joueur1 = new Joueur(nom);  // Cr�er le joueur
            joueur2 = new Joueur("IA");
            std::cout << "Joueur cr�� : " << joueur1->getName() << std::endl;
        }

        jouer();

        /* G�n�rer le plateau */
    }

    void choixExtensions(){}//Objet publique extension qui contient une liste d'extension et propose de les choisir
    void jouer(){
        // Fonction � appeler while true;
        Joueur *current = nullptr;
        current = (tour % 2) == 0 ? joueur1 : joueur2;
        std::cout <<"\nC'est au tour de : " << current->getName() << std::endl;
        int nbChoix;
        int choice = 0;
        do {
            std::cout << "Que voulez-vous faire ? :\n"
                      << "1 - D�placer un pion \n" << std::endl;
            if (current->getDeckSize() > 0) {
                std::cout << "2 - Placer un pion \n" << std::endl;
            }
            std::cin >> choice;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                choice = 0;  // R�initialiser pour forcer un nouveau choix
                std::cout << "Merci de saisir 1 ou 2 (si deck disponible).\n";
            }
        } while (choice != 1 && (choice != 2 && current->getDeckSize() > 0));
        if (choice == 1) {
            plateau.afficherPlateau();
        } else {
            std::cout <<"\nVoici votre deck : " << std::endl;
            current->afficherDeck();
            mode = getInput("Quel pion souhaitez-vous poser ?\n", 1, current->getDeckSize());
            plateau.afficherPlateau();
            int x = getInput("O� en absisse ?\n", plateau.getMinQ() - 1 , plateau.getMaxQ() + 1);
            int y = getInput("O� en ordonn�es ?\n", plateau.getMinR() - 1 , plateau.getMaxR() + 1);
            //r�cup�rer l'insecte dans le vecteur, et appeler la m�thode pour le placer : plateau.ajouterInsecte(Insecte* insecte)
        }
    }
    // Destructeur pour lib�rer la m�moire
    ~GameMaster() {
        delete joueur1;
        delete joueur2; //Attention que le joueur soit d�fini si IA
    }
};



#endif // GAMEMASTER_H
