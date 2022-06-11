/**
  * @file structure.h
  * @brief Signatures des fonctions qui implémentent les structures utilisées dans le programme
  * @author Teddy ALEXANDRE
  */

#ifndef STRUCTURE
#define STRUCTURE

#include <stdio.h>
#include <stdlib.h>

/* Idée clé : implémenter le plateau par des listes de listes chaînées
 * Isomorphisme avec un tableau 2D
 * mais permet de stocker plusieurs informations dans une même case
 */

// Noeud qui représente une case
typedef struct ListNode {
    int carte;              // Numéro de la carte
    struct ListNode* next;  // Pointeur sur la case suivante
} ListNode;

// Liste chaînée
typedef struct List {
    struct ListNode* head;  // Pointeur sur la tête de la liste
    int size;               // Taille de la liste
} List;

// Structure qui contient les informations d'une carte dans une cellule
typedef struct CellInfos {
    int faction;            // La faction qui a posé la carte
    int numCarte;           // Le numéro de la carte posée
    int visible;            // Si elle a été retournée (1) ou non (0)
} CellInfos;

// Cellule
typedef struct Cell {
    struct Cell *next;      // Pointeur sur la cellule suivante
    int x;                  // Indice de la colonne
    CellInfos infosCarte;   // Infos sur les cartes
} Cell;

typedef struct Ligne {
    int y;                  // Indice de la ligne
	int ligneSize;          // Taille de la ligne
    struct Cell *firstCell; // Pointeur sur la première cellule de la ligne
    struct Ligne *nextLigne;// Pointeur sur la ligne d'en dessous
} Ligne;

/**
  * Crée une nouvelle Liste
  * @param vide
  * @return un pointeur sur la nouvelle liste
  */
List* list_create();

/**
  * Libère la mémoire de la liste fournie
  * @param un pointeur sur la liste
  * @return rien, on libère simplement la mémoire associée à la liste
  */
void list_free(List* liste);

/**
  * Empile l'élément en tête de liste
  * @param un pointeur sur la liste et l'élément à empiler
  * @return rien, la liste pointée contient le nouvel élément en tête
  */
void list_empiler(List* main, int element);

/**
  * Dépile l'élément en tête de liste
  * @param un pointeur sur la liste à dépiler
  * @return l'élément en tête de liste, la liste pointée ne contient plus
  *         l'élément renvoyé
  */
int list_depiler(List* main);

/**
  * Supprime l'élément de la liste d'indice pos
  * @param un pointeur sur la liste et l'indice à supprimer
  * @return l'élément supprimé
  */
int list_remove(List* liste, int pos);

/**
  * Affiche la liste
  * @param un pointeur sur la liste
  * @return rien
  */
void list_display(List* liste);

/**
  * Echange les éléments aux indices respectifs from et to
  * @param un pointeur sur la liste et deux indices valides
  * @return 1 si l'échange s'est bien déroulé, 0 sinon
  */
int list_swap(List* l, int from, int to);

/** Libère la mémoire associée à une ligne
  * @param un pointeur sur la ligne en question
  * @return rien
  */
void ligne_free(Ligne* g);

/** Ajoute une nouvelle cellule aux coordonnées (x,y)
  * @param un pointeur de pointeurs de ligne (~ tableau 2D) et deux coordonnées valides
  * @return un pointeur sur un CellInfos placé aux coordonnées (x,y)
  */
CellInfos* ligne_add(Ligne** g, int x, int y);

/**
  * Récupère la cellule aux coordonnées (x,y)
  * @param Un pointeur sur le plateau entier, et deux coordonnées valides
  * @return Un pointeur sur le CellInfos aux coordonnées (x,y)
  */
CellInfos* ligne_get(Ligne *g, int x, int y);

/**
  * Ajoute une cellule le plus en haut à gauche dans le plateau
  * @param un pointeur de pointeurs (~ tableau 2D)
  * @return un pointeur sur la nouvelle cellule créée
  */
CellInfos* ligne_empiler(Ligne** g);

/**
  * Supprime une cellule dans le tableau
  * @param Un pointeur sur le tableau, et la cellule à supprimer
  * @return la cellule à supprimer
  */
Cell* cell_remove(Ligne *g, Cell *c);

#endif
