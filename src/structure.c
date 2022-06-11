/**
 * @file structure.c
 * @author Teddy ALEXANDRE
 * @brief Fonctions liées aux structures de données utilisées dans le projet
 */

#include <stdlib.h>
#include "../headers/structure.h"

List* list_create() {
    List* l = malloc(sizeof(struct List)); // Allocation mémoire d'une nouvelle liste
    l->head = NULL;     // La tête est nulle
    l->size = 0;        // Tout comme la taille
    return l;
}

void list_free(List* liste) {
    while (liste->head != NULL) {
        // Tant qu'il y a des éléments à supprimer, on les supprime
        ListNode* noeud = liste->head; 
        liste->head = noeud->next;     
        free(noeud);                   
    }
	free(liste);  // Libération de la mémoire associée à la liste      
}

void list_empiler(List* main, int element) {
    ListNode* noeud = malloc(sizeof(struct ListNode));
    noeud->carte = element;
    noeud->next = main->head;  // L'empilement est réalisé en tête
    main->head = noeud;        // La tête de liste devient le noeud
	main->size++;              // La taille augmente de 1
}

int list_depiler(List* liste) {
    if (liste->head == NULL) return -1; // On renvoie -1 si la liste est vide
    
    // On récupère l'élément en tête de liste avant de le renvoyer
	int numCarte = liste->head->carte;
	ListNode* noeud = liste->head;
	liste->head = liste->head->next; // La nouvelle tête
	free(noeud);
	liste->size--;   // La taille diminue de 1
	return numCarte;
}

int list_swap(List* l, int from, int to) {
    if (from == to) return 1;  // Rien à faire
    if (from <= 0 || to <= 0 || from > l->size || to > l->size ) return -1; // Indices invalides
    if (from > to){   // On supposera from <= to
        int tmp = from;
        from = to;
        to = tmp;
    }

    int i = 1;
    ListNode *pere_from, *pere_to, *noeud_from, *noeud_to, *tmp;
    pere_from = NULL;
    pere_to = NULL;
    tmp = l->head;
    while (i <= to) {  // Parcours de la liste jusqu'à to
        if (i == from-1) // Si on est avant from, on enregistre son père
            pere_from = tmp;
        if (i == from)   // Enregistrement de from
            noeud_from = tmp;
        if (i == to-1)   // Si on est avant to, on enregistre son père
            pere_to = tmp;
        if (i == to)     // Enregistrement de to
            noeud_to = tmp;
        tmp = tmp->next;
        i++;
    }

    // Le successeur du père de from devient to si le père n'est pas null
    if (pere_from != NULL)
        pere_from->next = noeud_to;
    // Le successeur du père de to devient from si le père n'est pas null
    if (pere_to != NULL)
        pere_to->next = noeud_from;
    
    // On échange les noeuds suivants avec une variable tmp
    tmp = noeud_from->next;
    noeud_from->next = noeud_to->next;
    noeud_to->next = tmp;

    if (pere_from == NULL) // Si le père de from est null, la tête devient to
        l->head = noeud_to;
    if (pere_to == NULL)   // Réciproquement
        l->head = noeud_from; 

    return 1;
}

void list_display(List* liste) {
    ListNode* pListe = liste->head;
    while (pListe != NULL) {
        printf("%d -> ", pListe->carte);  // Affichage de la carte
        pListe = pListe->next;
    }
    printf("NULL\n");
}

int list_remove(List* l, int pos) {
    if (l->head == NULL || pos < 0 || pos >= l->size) return -1;  // Position invalide
	
    ListNode *last = NULL;
    ListNode *ln = l->head;
    int carte = 0;

    for (int i = 0; i < pos; i++) {
        last = ln;
        ln = ln->next;
    }
    if (last == NULL) l->head = l->head->next; // Si c'est le premier élément
    else last->next = ln->next;                // Autres cas

    carte = ln->carte;
    free(ln);
    l->size--;
    return carte;
}


void ligne_free(Ligne* g) {
    while (g != NULL){                       // Balayage de la ligne
        while (g->firstCell != NULL) {       // Balayage des cellules sur la ligne
            Cell *tmp = g->firstCell;
            g->firstCell = g->firstCell->next;
            free(tmp);
        }
        // Passage à la ligne suivante
        Ligne *tmp = g;
        g = g->nextLigne;
        free(tmp);
    }
}

CellInfos* ligne_add(Ligne** g, int x, int y) {
	if (*g == NULL || y < (*g)->y){
        // Grille vide ou y inférieur à l'ordonnée de *g
        Ligne *g2 = malloc(sizeof(Ligne));    
        g2->nextLigne = *g;
        g2->y = y;
        g2->ligneSize = 1;
        *g = g2;
        g2->firstCell = NULL;
    }

    Ligne *parent = *g;
    Ligne *cur = *g;
    while (cur != NULL && cur->y < y) {
        // On va jusqu'à la ligne d'ordonnée y
        parent = cur;
        cur = cur->nextLigne;
    }
    if (cur == NULL || cur->y != y) {
        // Si on est arrivé au bout de la grille
        Ligne *g2 = malloc(sizeof(Ligne)); 
        parent->nextLigne = g2;
        g2->nextLigne = cur;
        g2->y = y;

        g2->ligneSize = 1;   
        
        g2->firstCell = NULL;
        cur = g2;
    }
    else {
        // On augmente la taille de la ligne
        cur->ligneSize++;
    }

    
    if (cur->firstCell == NULL || x < cur->firstCell->x) {
        // Si la première case de la ligne est nulle ou que x est inférieur à l'abscisse de la première cellule
        Cell *gn = malloc(sizeof(Cell));
        gn->next = cur->firstCell;
        gn->x = x;
        cur->firstCell = gn;
        return &(gn->infosCarte);
    }

    // Cas restant
    Cell *parentn = cur->firstCell;
    Cell *curn = cur->firstCell;
    while (curn != NULL && curn->x < x) {
        // On balaye jusqu'à x
        parentn = curn;
        curn = curn->next;
    }
    if (curn == NULL || curn->x != x) {
        // On crée la cellule voulue
        Cell *gn = malloc(sizeof(Cell));
        gn->next = curn;
        parentn->next = gn;
        gn->x = x;
        return &(gn->infosCarte);
    }
    cur->ligneSize--;
    return NULL;
}

CellInfos* ligne_get(Ligne *g, int x, int y){
	Ligne *cur = g;
    while (cur != NULL && cur->y != y) {
        // On balaie jusqu'à y
        cur = cur->nextLigne;
    }
    if (cur == NULL) return NULL;       // Ligne vide

    Cell *curn = cur->firstCell;
    while (curn != NULL && curn->x != x) {
        // On balaie jusqu'à x
        curn = curn->next;
    }
    if (curn == NULL) return NULL;      // Cellule vide
    return &(curn->infosCarte);         // Cellule non vide
}

CellInfos* ligne_empiler(Ligne** g) {
    if (*g == NULL) {
        // Si la grille est vide, on crée la cellule directement
        *g = malloc(sizeof(Ligne));
        (*g)->ligneSize=0;
        (*g)->nextLigne=NULL;
        (*g)->y=0;
        (*g)->firstCell=NULL;
    }

    // Sinon, on crée une cellule qui pointe vers l'ancienne cellule la + en haut à gauche
    Cell *c = malloc(sizeof(Cell));
    c->next = (*g)->firstCell;
    if ((*g)->firstCell != NULL) c->x = (*g)->firstCell->x-1;
    else c->x = 0;
    (*g)->firstCell = c;
    return &(c->infosCarte);
}

Cell* cell_remove(Ligne *g, Cell *c) {
	Ligne *cur = g;
	while (cur != NULL) {
        // On balaie ligne par ligne
		Cell *curn = cur->firstCell;
		Cell *parentn = NULL;
		while (curn != NULL && curn != c) {
            // On cherche c sur la ligne
			parentn = curn;
			curn = curn->next;
		}
		if (curn != NULL) {
            // Si on tombe sur curn, on libère la mémoire associée à cette cellule et on la renvoie
            Cell *cn =  curn->next;
			if (parentn == NULL) cur->firstCell = cn;
			else parentn->next = cn;
			free(curn);
			return cn;
		}
		cur = cur->nextLigne;
	}
    return NULL;
}