/**
 * @file main.c
 * @brief gestion de la partie avec toutes les fonctions définies dans le projet
 */

/* Importation de tous les fichiers et de
 * toutes les bibliothèques nécessaires */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../headers/carte.h"
#include "../headers/plateau.h"
#include "../headers/faction.h"
#include "../headers/interface.h"

int main() {

	// Constantes et variables utiles pendant la partie
	Plateau* p = plateau_new();                 // Création du plateau et initialisation des factions avec faction_init
	srand(time(NULL));                          // Change la "graine", ici le temps d'exécution du programme
	int j1 = rand() % 2;                        // Vaut 0 ou 1, permet de passer de la faction 1 à la faction 2
	int finJeu = 0;                             // Variable indiquant si le jeu continue (=0) ou s'il est terminé (=1)
	Faction** fac = plateau_factionListe(p);    // Tableau de pointeur de faction : renvoie la liste des factions du jeu
	int nbManches = 0;							// Compte le nombre de manches
	
	// Tant que le jeu n'est pas terminé
	while (!finJeu) {
		// Première phase

		// Préparation du jeu pour chaque faction
		for (int i = 0; i < 2; i++) {
			faction_piocher(fac[i]);													// Chaque faction effectue sa pioche
			interface_afficherMain(fac[i]);												// Affichage de la main obtenue (les 8 cartes piochées)
			if (!faction_dejaRemelange(fac[i]) && interface_demandeRepioche(fac[i])) {    
				// Si la faction veut remélanger sa main et qu'elle n'a pas déjà utilisé l'option avant
				// dans la partie
				faction_remelanger(fac[i]);												// Elle l'utilise (elle repioche 8 nouvelles cartes)
				interface_afficherMain(fac[i]);											// On affiche la nouvelle main
			}
		}

		// Disposition des cartes sur le plateau : il y en a 16 à poser
		for (int tour = 0; tour < tailleMain*2; tour++) {
			Faction* joueurEnCours = fac[(tour + j1) % 2];								// Détermine le joueur qui joue en le tour courant
			interface_afficherMain(joueurEnCours);
			interface_afficherPlateau(p);
			int carteAPoser = interface_demandeCarteAPoser(joueurEnCours);              // L'interface demande au joueur quelle carte de sa main poser
			int pos[2];
			interface_demandePosition(joueurEnCours, p, pos);							// L'interface demande au joueur à quel endroit il souhaite poser sa carte sur le plateau
			plateau_cartePoser(p, (tour+j1) % 2, carteAPoser, pos[0], pos[1]);			// Pose la carte aux coordonnées x=pos[0] et y=pos[1]
		}
													
			
		// Deuxième phase

		// Retournement de toutes les cartes + effets de celles-ci
		int infosCarte;
		while ((infosCarte = plateau_carteRetourner(p)) != -1) {						// Tant que toutes les cartes ne sont pas retournées
			interface_afficherEffets(infosCarte);										// On les retourne, on active leur effet et on affiche leur effet
			interface_afficherPlateau(p);												// Affiche l'état du plateau après disposition des cartes
		}
		int etatJeu;
		if ((etatJeu = plateau_mancheNew(p)) == -1) finJeu = 1;							// Si la manche est finie, on quitte la boucle
		else printf("La faction n°%d a gagné la manche !", etatJeu+1);					// Sinon on affiche le vainqueur de la manche

		nbManches++;
		if (nbManches == 1) j1 = 1 - j1;												// Si on passe au 2nd tour, on prend l'autre faction en 1er
		else if (nbManches == 2) j1 = rand() % 2;										// Sinon on le détermine au hasard
	}
	interface_afficherVainqueur(p);														// Affiche le vainqueur de la partie
	plateau_free(p);																	// Libération de la mémoire du plateau et des factions avec faction_free
	return 0;
}