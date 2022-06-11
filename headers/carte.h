#ifndef CARTES2
#define CARTES2

#include <stdio.h>


typedef struct Carte Carte;

/**
 * @file carte.h
 * @brief Header du module Carte
 */

/**
 * Renvoie l'id de la carte
 * @param c la position de la carte dans le tableau
 * @return l'id de la carte
 */

char* carte_getId(int c);

/**
 * Permet de modifier l'id de la carte
 * @param c la position de la carte dans le tableau
 * @param id chaine de caractère
 */

void carte_setId(int c, char* id);

/**
 * Renvoie le nom de la carte
 * @param c la position de la carte dans le tableau
 * @return le nom de la carte
 */

char* carte_getNom(int c);

/**
 * Permet de modifier le nom de la carte
 * @param c la position de la carte dans le tableau
 * @param nom chaine de caractère
 */

void carte_setNom(int c, char* nom);

/**
 * Renvoie la description de la carte
 * @param c la position de la carte dans le tableau
 * @return la description de la carte
 */

char* carte_getDescription(int c);

/**
 * Permet de modifier la description de la carte
 * @param c la position de la carte dans le tableau
 * @param description chaîne de caractère
 */

void carte_setDescription(int c, char* description);

/**
 * Renvoie le nombre d'occurence de la carte
 * @param c la position de la carte dans le tableau
 * @return le nombre d'occurence de la carte
 */

int carte_getOccurence(int c);

/**
 * Permet de modifier le nombre d'occurence d'une carte
 * @param c la position de la carte dans le tableau
 * @param occurence un entier
 */

void carte_setOccurence(int c, int occurence);

#endif
