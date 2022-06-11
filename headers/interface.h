/**
 * @file interface.h
 * @author Arthur BABIN
*/

#ifndef INTERFACE
#define INTERFACE

#include <stdlib.h>
#include <stdio.h>
#include "carte.h"
#include "faction.h"
#include "plateau.h" 

/**
 * Affiche le plateau de jeu sur la sortie standard 
 * @param p pointeur de Plateau 
*/
void interface_afficherPlateau(Plateau *p); 

/**
 * Affiche la main de la faction sur la sortie standard 
 * @param f pointeur de Faction
*/
void interface_afficherMain(Faction *f); 

/**
 * Affiche un message de proposition de repioche au joueur sur la sortie standard 
 * @param f pointeur de Faction
 * @return 0 si Non 1 si Oui
*/ 
int interface_demandeRepioche(Faction *f);

/**
 * Affiche un message sur la sortie standard
 * Demande à la faction le numéro de la carte à jouer dans sa main 
 * @param f pointeur de Faction
 * @return int n le numéro de la carte choisie
*/
int interface_demandeCarteAPoser(Faction *f); 

/**
 * Affiche un message sur la sortie standard 
 * Demande au joueur où poser la carte
 * Si la position indiquée est invalide on lui redemande où poser la carte
 * @param f pointeur de Faction
 * @param p pointeur de Plateau
 * @param pos le couple des coordonnées choisies
*/ 
void interface_demandePosition(Faction *f, Plateau *p, int pos[2]);

/**
 *Affiche la description des effets de la carte sur la sortie standard
 *@param numeroCarte l'identifiant de la carte
*/ 
void interface_afficherEffets(int numeroCarte); 

/**
 * Affiche le vainqueur de la partie sur la sortie standard 
 * @param p pointeur de Plateau
*/ 
void interface_afficherVainqueur(Plateau *p);

/**
 * Vérifie que la position indiquée correspond à une case libre 
 * et adjacente à une case occupée
 * @param p pointeur de plateau
 * @param pos le couple des coordonnées à vérifier
 */
int interface_estPositionValide(Plateau *p, int pos[2]);

#endif



