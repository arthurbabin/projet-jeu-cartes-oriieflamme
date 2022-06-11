#ifndef PLATEAU
#define PLATEAU

#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "carte.h"
#include "faction.h"
#include "structure.h"

/**
 * @file plateau.h
 * @brief Header du module plateau
 */

typedef struct Plateau Plateau;


/**
 * Alloue dynamiquement un nouveau plateau
 */

Plateau* plateau_new();

/**
 * Libère la mémoire du plateau et des factions (en appelant faction_free)
 * @param p pointeur de plateau
 */

void plateau_free(Plateau *p);

/**
 * Termine la manche précédente:
 * Qui à remporté cette manche et ajoute le poitn à la faction
 * Puis créer une nouvelle manche:
 * Libère la grille, redonne de nouvelles cartes aux factions et vérifie qu'aucune faction n'a plus d'une manche gagnée
 * @param p pointeur de plateau
 * @return 0 ou 1 en fonction de qui à remporté la manche si une nouvelle est créée , -1 si fin du jeu
 */

int plateau_mancheNew(Plateau *p);

/**
 * Permet de créer une liste des faction
 * @param p pointeur de plateau
 * @return un tableau de pointeurs vers la liste des factions
 */

Faction** plateau_factionListe(Plateau *p);

/**
 * Permet à une faction de poser une carte à certaines coordonnées
 * @param p pointeur de plateau
 * @param faction numéro de la faction
 * @param carte numéro de la carte
 * @param x coordonnée x
 * @param y coordonnée y
 */

void plateau_cartePoser(Plateau *p, int faction, int carte, int x, int y );

/**
 * Retourne une carte et applique ses effets
 * @param p pointeur de plateau
 * @return le numéro de la carte retournée, -1 si elle sont toutes déjà retournées
 */

int plateau_carteRetourner(Plateau *p);

/**
 * Permet de modifier les factions du plateau
 * @param p un plateau
 * @param factions tableau de factions
 */

void plateau_setFaction(Plateau *p, Faction* factions);

/**
 * Renvoie l'adresse de la première ligne de la grille
 * @param p un plateau
 * @return le pointeur vers la grille
 */

Ligne* plateau_getPremiereLigne(Plateau *p);

/**
 * Permet de modifier l'adresse de la grille du plateau
 * @param p un plateau
 * @param ligne pointeur vers une ligne
 */

void plateau_setPremiereLigne(Plateau *p, Ligne* ligne);

/**
 * Permet de récupérer les coordonées maximales du plateau
 * @param p un plateau
 * @param res un tableau d'entier de taille au moins 2
 */

int* plateau_getMaxCoord(Plateau* p, int* res);
#endif
