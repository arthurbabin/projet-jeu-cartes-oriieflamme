/**
 * @file interface.c
 * @author Arthur BABIN
*/

#include "../headers/interface.h"

/**
 * Affiche une série de '-' sur la sortie standard 
 * suivie d'un retour à la ligne
 * @param n le nombre de '-' à afficher
*/
void interface_afficheGrandTrait(int n){
    for(int i=0;i<n;i++){
        printf("-");
    }
    printf("\n");
}

/**
 * Affiche le contenu d'une cellule précédé de '|'
 * 
 * @param content le contenu de la cellule 
 */
void interface_afficheCellule(char* content){
    printf("|%4s",content);
}

/**
 * Affiche une ligne vide d'ordonnée y dont la première
 * cellule est d'abscisse xmin et de longueur l 
 * 
 * @param l longueur de la ligne 
 */
void interface_afficheLigneVide(int l){
    for(int i=0; i<l; i++){
        interface_afficheCellule("");
    }
    printf("|\n");
}

/**
 * Affiche le plateau de jeu sur la sortie standard 
 * @param p pointeur de Plateau 
*/
void interface_afficherPlateau(Plateau *p){
    /* Variables dont on a besoin pour connaître la taille 
    et la position des cellules de la grille infinie à 
    afficher */
    int nbColonnes,tailleCase,longueurPlateau;
    int maxCoords[2];
    Ligne* g = plateau_getPremiereLigne(p);
    if (g!=NULL){
        plateau_getMaxCoord(p, maxCoords);
    } else {
        maxCoords[0] = 0;
        maxCoords[1] = 1;
    }
    tailleCase = 5;
    nbColonnes = maxCoords[1] - maxCoords[0] + 3;
    longueurPlateau = (tailleCase*nbColonnes) + 1;

    printf("Plateau de Jeu :\n");
    interface_afficheGrandTrait(longueurPlateau);
    interface_afficheLigneVide(nbColonnes);
    //Itération sur les lignes du plateau
    while(g != NULL){
        interface_afficheGrandTrait(longueurPlateau);
        Cell *gn = g->firstCell;
        //Itération le long de la ligne
        int x = maxCoords[0];
        interface_afficheCellule("");
        while(gn != NULL && x<=maxCoords[1]){
            //Si la position correspond à une cellule non vide
            if( gn!=NULL && (gn->x) == x){
                //Séquence d'échappement pour la couleur des cartes
                if(gn->infosCarte.faction){
                    printf("\033[0;31m");//Rouge
                } else {
                    printf("\033[0;36m");//Bleu Cyan
                }
                //Contenu en fonction de la visibilité de la carte
                if(gn->infosCarte.visible){
                    interface_afficheCellule(carte_getId(gn->infosCarte.numCarte));
                } else {
                    interface_afficheCellule("■■■■");
                }
                //Passage à la cellule remplie suivante
                printf("\033[0m");
                gn = gn->next;
            } else {
                interface_afficheCellule("");
            }
            x++;//passage à la cellule à droite
        }
        interface_afficheCellule("");
        printf("|\n");
        g = g->nextLigne;
    }
    interface_afficheGrandTrait(longueurPlateau);
    interface_afficheLigneVide(nbColonnes);
    interface_afficheGrandTrait(longueurPlateau);
}

/**
 * Affiche la main de la faction sur la sortie standard 
 * @param f pointeur de Faction
*/
void interface_afficherMain(Faction *f){
    //en tête
    printf("\n%s > Main:\n",faction_getNom(f));

    //cartes
    ListNode* cartesEnMain = faction_getMain(f)->head;
    int i=0;
    while(cartesEnMain != NULL){
        printf("(n°%i) - %s\n", i,carte_getNom(cartesEnMain->carte));
        i++;
        cartesEnMain = cartesEnMain->next;
    }
} 

/**
 * Affiche un message de proposition de repioche au joueur sur la sortie standard 
 * @param f pointeur de Faction
 * @return 0 si Non 1 si Oui
*/ 
int interface_demandeRepioche(Faction *f){
    char reponse;
    printf("(%s) Voulez-vous utiliser votre option permettant de repiocher une autre main ? (y/n) : ",faction_getNom(f));
    scanf(" %c", &reponse);
    if(reponse=='Y' || reponse == 'y'){
        return 1;
    } else {
        return 0;
    }
}

/**
 * Affiche un message sur la sortie standard
 * Demande à la faction le numéro de la carte à jouer dans sa main 
 * @param f pointeur de Faction
 * @return int n le numéro de la carte choisie
*/
int interface_demandeCarteAPoser(Faction *f){
    int c = -1;
    List* mainc = faction_getMain(f);
    while(c < 0 || c >= mainc->size){
        printf("%s> Quelle carte voulez-vous poser ?[0-%d]:\n", faction_getNom(f), mainc->size-1);
        scanf(" %d", &c);
    }
    return c;
}



/**
 * Vérifie que la position indiquée correspond à une case libre 
 * et adjacente à une case occupée
 * @param p pointeur de plateau
 * @param pos le couple des coordonnées à vérifier
 */
int interface_estPositionValide(Plateau *p, int pos[2]){
    // pas du tout opti mais ça fonctionne
    if(plateau_getPremiereLigne(p) == NULL) return 1;
    CellInfos *ci = ligne_get(plateau_getPremiereLigne(p), pos[0], pos[1]);
    if(ci != NULL) return 0;
    if(ligne_get(plateau_getPremiereLigne(p), pos[0], pos[1]+1) != NULL) return 1;
    if(ligne_get(plateau_getPremiereLigne(p), pos[0], pos[1]-1) != NULL) return 1;
    if(ligne_get(plateau_getPremiereLigne(p), pos[0]+1, pos[1]) != NULL) return 1;
    if(ligne_get(plateau_getPremiereLigne(p), pos[0]-1, pos[1]) != NULL) return 1;

    return 0;
}

/**
 * Affiche un message sur la sortie standard 
 * Demande au joueur où poser la carte
 * Si la position indiquée est invalide on lui redemande où poser la carte
 * @param f pointeur de Faction
 * @param p pointeur de Plateau
 * @param pos le couple des coordonnées choisies
*/ 
void interface_demandePosition(Faction *f, Plateau *p, int pos[2]){
    int pass = 0;
    while(!pass){
        printf("%s> A quelle position voulez-vous poser la carte ?\n", faction_getNom(f));
        printf("ligne= ");
        scanf(" %d", pos+1);
        printf("colonne= ");
        scanf(" %d", pos);

        pass = interface_estPositionValide(p, pos);
        if(!pass){
            printf("%s> l'emplacement (%d, %d) est invalide\n", faction_getNom(f), pos[0], pos[1]);
        }
    }
}

/**
 *Affiche la description des effets de la carte sur la sortie standard
 *@param numeroCarte l'identifiant de la carte
*/ 
void interface_afficherEffets(int numeroCarte){
    char* desc = carte_getDescription(numeroCarte);
    char* id = carte_getId(numeroCarte);
    char* nom = carte_getNom(numeroCarte);
    printf("Effet de la carte %s (%s)\n->%s\n",nom,id,desc);
} 

/**
 * Affiche le vainqueur de la partie sur la sortie standard 
 * @param p pointeur de Plateau
*/ 
void interface_afficherVainqueur(Plateau *p){
    char* messageVainqueur = "La faction %s a gagné la partie !\n";
    Faction **factions = plateau_factionListe(p);
    int i;
    for(i = 0; i < 2; i++){
        if(faction_getManche(factions[i]) == 2) break;
    }
    printf(messageVainqueur, faction_getNom(factions[i]));
}
