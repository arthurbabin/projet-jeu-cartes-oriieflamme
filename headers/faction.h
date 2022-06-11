#ifndef FACTION
#define FACTION

#include <string.h>
#include <stdlib.h>
#include "carte.h"
#include "structure.h"

/**
 * @file faction.h
 * @brief Header du module Faction
 */
 
static int tailleMain = 8;
typedef struct Faction Faction;

/**
 * alloue dynamiquement la mémoire nécessaire
 * initialise les différents champs du type Faction.
 * Ajoute l'ensemble des cartes dans la pioche la mélange.
 * @param fac  Pointeur de faction
 * @param name  Nom de la faction
 * @return pointeur vers le type Faction nouvellement créé
 */
Faction* faction_new(char* name);

/**
 * libère la mémoire, notamment celle des List
 * @param fac pointeur de faction
 */
void faction_free(Faction *fac);

/**
 * La faction a t-elle déjà utilisé l'option permettant de repiocher et remélanger sa main ?
 * @param fac pointeur de faction
 * @return 1 si la faction a déjà utilisé l'option remélanger. retourne 0 sinon
 */
int faction_dejaRemelange(Faction *fac);

/**
 * Permet de vider sa main dans la pioche, mélanger la pioche ainsi que de repiocher ces cartes.
 * modifie fac->remelanger à 1.
 * Cette fonction ne vérifie pas si l'option a déjà été utilisé
 * @param fac pointeur de faction
 */
void faction_remelanger(Faction *fac);

/**
 * Vide la main de la faction fac dans sa pioche.
 * @param fac pointeur de faction 
 */
void faction_viderDansPioche(Faction *fac);

/**
 * Mélange la pioche de la faction fac
 * @param fac pointeur de faction
 */
void faction_melangerPioche(Faction *fac);

/**
 * pioche 8 cartes et les ajoute à la main de la faction fac
 * @param fac pointeur de faction
 */
void faction_piocher(Faction *fac);


/**
 * Renvoie le nom de la faction
 * @param fac une faction
 * @return le nom de la faction
 */


char* faction_getNom(Faction* fac);

/**
 * Permet de modifier le nom de la faction
 * @param fac une faction
 * @param nom une chaine de caractère
 */

void faction_setNom(Faction* fac, char* nom);

/**
 * Renvoie le score DDRS de la faction
 * @param fac une faction
 * @return le nombre de point DDRS de la faction
 */

int faction_getDdrs(Faction* fac);

/**
 * Permet de modifier le score DDRS de la faction
 * @param fac une faction
 * @param ddrs un entier
 */

void faction_setDdrs(Faction* fac, int ddrs);

/**
 * Renvoie la main de la faction
 * @param fac une faction
 * @return la main de la faction
 */

List* faction_getMain(Faction* fac);

/**
 * Permet de modifier la main de la faction
 * @param fac une faction
 * @param main pointeur vers une list
 */

void faction_setMain(Faction* fac, List* main);

/**
 * Renvoie la pioche de la faction
 * @param fac une faction
 * @return la pioche de la faction
 */

List* faction_getPioche(Faction* fac);

/**
 * Permet de modifier la pioche de la faction
 * @param fac une faction
 * @param pioche pointeur vers une list
 */

void faction_setPioche(Faction* fac, List* pioche);

/**
 * Renvoie l'entier qui indique si la faction à déjà remélangé sa main au cours de la partie
 * @param fac une faction
 * @return l'entier qui indique si la faction à déjà remélangé sa main au cours de la partie
 */

int faction_getRemelanger(Faction* fac);

/**
 * Permet de modifier l'entier qui indique si la faction à le droit de remélanger ou pas
 * @param fac une faction
 * @param remalanger un entier
 */

void faction_setRemelanger(Faction* fac, int remelanger);

/**
 * Renvoie le nombre de manche gagnée par la faction
 * @param fac une faction
 * @return le nombre de manche gagnée la faction
 */


int faction_getManche(Faction* fac);

/**
 * Permet de modifier le nombre de manche gagné par la faction
 * @param fac une faction
 * @param manche un entier
 */

void faction_setManche(Faction* fac, int manche);

/**
 * Renvoie la taille de la main de la faction
 * @param fac une faction
 * @return la taille de la main de la faction
 */


int faction_getTailleMain(Faction* fac);

#endif
