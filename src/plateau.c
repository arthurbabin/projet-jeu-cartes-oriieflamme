#include "../headers/plateau.h"

struct Plateau {
    Faction* factions[2];
    Ligne* grille;
    Cell* lastCarteRetourne;
};

Plateau* plateau_new(){
    Plateau* p = malloc(sizeof(Plateau));
    srand(time(NULL));
    p->factions[0] = faction_new("Faction n°1");
    p->factions[1] = faction_new("Faction n°2");
    p->grille = NULL;
    p->lastCarteRetourne = NULL;
    return p;
}

void plateau_free(Plateau *p){
    faction_free(p->factions[0]);
    faction_free(p->factions[1]);
    ligne_free(p->grille);
}

Faction** plateau_factionListe(Plateau *p){
    return p->factions;
}

void plateau_cartePoser(Plateau *p, int faction, int carte, int x, int y ){
    Ligne *g = p->grille;
    CellInfos *ci = ligne_add(&g, x, y);
    p->grille = g;
    ci->numCarte = list_remove(faction_getMain(p->factions[faction]),carte);
    ci->visible = 0;
    ci->faction = faction;
}

Ligne* plateau_getPremiereLigne(Plateau *p){
    return p->grille;
}

unsigned long int factorielle(int n){
    unsigned long int res = 1;
    while(n > 1){
        res *= n;
        n--;
    }
    return res;
}

int plateau_mancheNew(Plateau *p ){
    int res = -1;
    if(p->lastCarteRetourne!= NULL && strcmp(carte_getNom(p->lastCarteRetourne->infosCarte.numCarte), "Laurent Prével") == 0){
        res = p->lastCarteRetourne->infosCarte.faction;
    }else if(faction_getDdrs(p->factions[0]) > faction_getDdrs(p->factions[1])){
        res = 0;
    }else if(faction_getDdrs(p->factions[1]) > faction_getDdrs(p->factions[0])){
        res = 1;
    }else{
        res = p->grille->firstCell->infosCarte.faction;    
    }
    faction_setManche(p->factions[res], faction_getManche(p->factions[res])+1);
    faction_setDdrs(p->factions[0], 0);
    faction_setDdrs(p->factions[1], 0);
    faction_melangerPioche(p->factions[0]);
    faction_melangerPioche(p->factions[1]);
    ligne_free(p->grille);
    p->grille=NULL;
    p->lastCarteRetourne=NULL;

    if(faction_getManche(p->factions[0]) > 1 || faction_getManche(p->factions[0]) > 1) res=-1;

    return res;
}

int* plateau_getMaxCoord(Plateau* p, int* res){
    Ligne* g = plateau_getPremiereLigne(p);
    res[0]=INT_MAX;
    res[1]=INT_MIN;
    while (g != NULL){
        Cell *gn = g->firstCell;
        if (gn != NULL){ 
            if (res[0] > gn->x){
                res[0] = gn->x;
            }
            while(gn->next != NULL){
                gn = gn->next;
            }
            if ( res[1] < gn->x){
                res[1] = gn->x;
            }
        }
        g = g->nextLigne;
    }
    return res;
}


void effet_FISE(Plateau *p, Cell *ce, int y);
void effet_FISA(Plateau *p, Cell *ce, int y);
void effet_FC(Plateau *p, Cell *ce, int y);
void effet_EcologIIE(Plateau *p, Cell *ce, int y);
void effet_lIIEns(Plateau *p, Cell *ce, int y);
void effet_SoireeSansAlcool(Plateau *p, Cell *ce, int y);
void effet_alcool(Plateau *p, Cell *ce, int y);
void effet_CafeThe(Plateau *p, Cell *ce, int y);
void effet_reprographie(Plateau *p, Cell *ce, int y);
void effet_IsolationDuBatiment(Plateau *p, Cell *ce, int y);
void effet_ParcoursSobrieteNumerique(Plateau *p, Cell *ce, int y);
void effet_HeuresSupplementaires(Plateau *p, Cell *ce, int y);
void effet_KahinaBouchama(Plateau *p, Cell *ce, int y);
void effet_KevinGoilard(Plateau *p, Cell *ce, int y);
void effet_MassinissaMerabet(Plateau *p, Cell *ce, int y);
void effet_ViteraY(Plateau *p, Cell *ce, int y);
void effet_JonasSenizergues(Plateau *p, Cell *ce, int y);
void effet_FetiaBannour(Plateau *p, Cell *ce, int y);
void effet_CatherineDubois(Plateau *p, Cell *ce, int y);
void effet_AnneLaureLigozat(Plateau *p, Cell *ce, int y);
void effet_GuillaumeBurel(Plateau *p, Cell *ce, int y);
void effet_ChristopheMouilleron(Plateau *p, Cell *ce, int y);
void effet_ThomasLim(Plateau *p, Cell *ce, int y);
void effet_JulienForest(Plateau *p, Cell *ce, int y);
void effet_DimitriWatel(Plateau *p, Cell *ce, int y);
void effet_DjibrilAurelienDembeleCabot(Plateau *p, Cell *ce, int y);
void effet_EricLejeune(Plateau *p, Cell *ce, int y);
void effet_LuciennePacave(Plateau *p, Cell *ce, int y);
void effet_KatrinSalhab(Plateau *p, Cell *ce, int y);
// dans l'objectif de les rendrent plus facilement accessible, j'enregistre les fonctions de gestions d'effets de carte dans un tableau de pointeur de fonction.
void (*effet_appliquer[32])(Plateau *p, Cell *ce, int y) = {
    effet_FISE,
    effet_FISA,
    effet_FC,
    effet_EcologIIE,
    effet_lIIEns,
    effet_SoireeSansAlcool,
    effet_alcool,
    effet_CafeThe,
    effet_CafeThe,
    NULL,
    effet_reprographie,
    effet_IsolationDuBatiment,
    effet_ParcoursSobrieteNumerique,
    effet_HeuresSupplementaires,
    effet_KahinaBouchama,
    effet_KevinGoilard,
    effet_MassinissaMerabet,
    effet_ViteraY,
    effet_JonasSenizergues,
    effet_FetiaBannour,
    effet_CatherineDubois,
    effet_AnneLaureLigozat,
    effet_GuillaumeBurel,
    effet_ChristopheMouilleron,
    effet_ThomasLim,
    effet_JulienForest,
    effet_DimitriWatel,
    effet_DjibrilAurelienDembeleCabot,
    effet_EricLejeune,
    effet_LuciennePacave,
    effet_KatrinSalhab,
    NULL
};

/**
 * les comparaisons de chaines de caractères peuvent être remplacer par de simple comparaisons d'entier. Cependant, le code est plus facilement lisible ainsi.
 */
void effet_FISE(Plateau *p, Cell *ce, int y){
     faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])+1);
}
void effet_FISA(Plateau *p, Cell *ce, int y){
    int nbCarteRetourne = 0;
    //on compte dans nbCarteRetoune le nombre de carte retourne sur le plateau
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible){
                nbCarteRetourne++;
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
    // si le nombre de carte retourne sur le plateau est pair, la faction gagne 2 points ddrs
    if(nbCarteRetourne%2 == 0){
        faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])+2);
    }
}
void effet_FC(Plateau *p, Cell *ce, int y){
    int nbCarteRetourne = 0;
    // on regarde si une autre carte FC est retourne sur le plateau
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible){
                if(strcmp(carte_getNom(c->infosCarte.numCarte), "FC") == 0){
                    nbCarteRetourne++;
                }
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
    // si une autre carte FC est retourne, la faction gagne 4 points ddrs
    if(nbCarteRetourne > 1){
        faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])+4);
    }
}
void effet_EcologIIE(Plateau *p, Cell *ce, int y){
    //La faction qui a posé cette carte gagne 1 point DDRS par carte FISE/FISA/FC retournée.
    int nbCarteRetourne = 0;
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible){
                if(strcmp(carte_getNom(c->infosCarte.numCarte), "FISE") == 0 || strcmp(carte_getNom(c->infosCarte.numCarte), "FISA") == 0 || strcmp(carte_getNom(c->infosCarte.numCarte), "FC") == 0){
                    nbCarteRetourne++;
                }
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
    if(nbCarteRetourne > 0){
        faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])+nbCarteRetourne);
    }
}
void effet_lIIEns(Plateau *p, Cell *ce, int y){
    List *lc = list_create();
    List *lf = list_create();
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible){
                if(strcmp(carte_getNom(c->infosCarte.numCarte), "FISE") == 0 || strcmp(carte_getNom(c->infosCarte.numCarte), "FISA") == 0 || strcmp(carte_getNom(c->infosCarte.numCarte), "FC") == 0){
                    list_empiler(lc, c->infosCarte.numCarte);
                    list_empiler(lf, c->infosCarte.faction);
                    c = cell_remove(g, c);
                    continue;
                }
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
    for(int i = lc->size-1; i >= 1; i--){
        int j = rand() % (i+1);
        list_swap(lc, i, j);
        list_swap(lf, i, j);
    }

    while(lc->size > 0){
        CellInfos *ci=ligne_empiler(&(p->grille));
        ci->faction=list_depiler(lf);
        ci->numCarte=list_depiler(lc);
        ci->visible=0;
    }
}
void effet_SoireeSansAlcool(Plateau *p, Cell *ce, int y){
    Ligne *g = p->grille;
    int alcool = 0;
    while(g != NULL && !alcool){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible && strcmp(carte_getNom(c->infosCarte.numCarte), "Alcool") == 0 ){
                alcool++;
                break;
            }
            c = c->next;
        }
        g = g->nextLigne;
    }

    if(alcool){
        g = p->grille;
        while(g != NULL){
            Cell *c = g->firstCell;
            while(c != NULL){
                if(c->infosCarte.visible){
                    if(strcmp(carte_getNom(c->infosCarte.numCarte), "FISE") == 0 || strcmp(carte_getNom(c->infosCarte.numCarte), "FISA") == 0 || strcmp(carte_getNom(c->infosCarte.numCarte), "FC") == 0){
                        c = cell_remove(g, c);
                        continue;
                    }
                }
                c = c->next;
            }
            g = g->nextLigne;
        }
        g = p->grille;
        p->grille = g->nextLigne;
        g->nextLigne = NULL;
        ligne_free(g);

        if(p->grille == NULL) return;

        Ligne *pg = NULL;
        g = p->grille;
        while(g->nextLigne != NULL){
            pg = g;
            g = g->nextLigne;
        } 
        pg->nextLigne = NULL;
        ligne_free(g);
    }else{
        faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])+5);
    }
}
void effet_alcool(Plateau *p, Cell *ce, int y){
    //Supprimez du plateau toutes les cartes qui touchent cette carte-ci (mais laissez la carte Alcool sur le plateau).
    Ligne *g = p->grille;
    while(g != NULL){
        if(g->y == y-1 || g->y == y+1){
            Cell *c = g->firstCell;
            while(c != NULL){
                if(c->x == ce->x){
                    cell_remove(g, c);
                    break;
                }
                c = c->next;
            }
        }else if(g->y == y){
            Cell *c = g->firstCell;
            while(c != NULL){
                if(c->x == ce->x-1){
                    cell_remove(g, c);
                    break;
                }
                c = c->next;
            }
            if(ce->next != NULL && ce->next->x == ce->x+1){
                cell_remove(g, ce->next);
            }
        }
        g = g->nextLigne;
    }
}
void effet_CafeThe(Plateau *p, Cell *ce, int y){
    int state = 0;
    if(strcmp(carte_getNom(ce->infosCarte.numCarte), "Café") == 0){
        state = 1;
    }else if (strcmp(carte_getNom(ce->infosCarte.numCarte), "Thé") == 0){
        state = 0;
    }
    char suppr[2][5] = { "Café" , "Thé" };
    int ecocup = 0;
    Ligne *g = p->grille;
    while( g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible){
                if(strcmp(carte_getNom(c->infosCarte.numCarte), suppr[state]) == 0 || strcmp(carte_getNom(c->infosCarte.numCarte), "Alcool") == 0){
                    c = cell_remove(g, c);
                    continue;
                }else if(strcmp(carte_getNom(c->infosCarte.numCarte), "Ecocup") == 0){
                    ecocup++;
                }
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
    if(ecocup){
        faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])+1);
    }else{
        faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])-1);
    }
}
void effet_reprographie(Plateau *p, Cell *ce, int y){
    int carte[32];
    int ddrs = 0;
    memset(carte, 0, 32 * sizeof(int));

    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible){
                carte[c->infosCarte.numCarte]++;
            }
            c = c->next;
        }
        g = g->nextLigne;
    }

    for(int i = 0; i < 32; i++){
        if(carte[i] > 1){
            ddrs -= 1 * ( factorielle(carte[i]) / (2 * factorielle(carte[i] - 2)) );
        }
    }
    int faction = (ce->infosCarte.faction+1)%2;
    faction_setDdrs(p->factions[faction], faction_getDdrs(p->factions[faction])+ddrs);
}
void effet_IsolationDuBatiment(Plateau *p, Cell *ce, int y){
    int ddrs[2] = {0, 0};
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(!c->infosCarte.visible){
                ddrs[c->infosCarte.faction]++;
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
    faction_setDdrs(p->factions[0], faction_getDdrs(p->factions[0]) + ddrs[0]);
    faction_setDdrs(p->factions[1], faction_getDdrs(p->factions[1]) + ddrs[1]);
}
void effet_ParcoursSobrieteNumerique(Plateau *p, Cell *ce, int y){
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *pc = NULL;
        Cell *c = g->firstCell;
        if(c != NULL){
            c->infosCarte.visible = 1; 
        }   
        while(c != NULL){
            pc = c;
            c = c->next;
        }
        if(pc != NULL){
            pc->infosCarte.visible = 1;
        }
        g = g->nextLigne;
    }
}
void effet_HeuresSupplementaires(Plateau *p, Cell *ce, int y){
    int nbCarte = 0;
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible && strcmp(carte_getNom(c->infosCarte.numCarte), "Heures supplémentaires") == 0){
                nbCarte++;
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
    int faction = (ce->infosCarte.faction+1)%2;
    faction_setDdrs(p->factions[faction], faction_getDdrs(p->factions[faction]) - 3 * nbCarte);
}
void effet_KahinaBouchama(Plateau *p, Cell *ce, int y){
    //Supprimez une carte non retournée du plateau choisie au hasard.
    Cell **cells = malloc(sizeof(Cell*) *tailleMain*2);
    int i = 0;
    Ligne *g = p->grille;
    while(g !=NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(!c->infosCarte.visible){
                cells[i]=c;
                i++;
            }
            c = c->next;
        }  
        g = g->nextLigne;
    }
    if(i > 0){
        int r = rand()%i;
        cell_remove(p->grille, cells[r]);  
    }
    free(cells);
}
void effet_KevinGoilard(Plateau *p, Cell *ce, int y){
    int nbLigne = 0;
    Ligne*g = p->grille, *pg = NULL;
    while(g != NULL){
        nbLigne++;
        g = g->nextLigne;
    }
    int r = rand()%nbLigne;

    g = p->grille;
    while(r > 0){
        pg = g;
        g = g->nextLigne;
        r--;
    }
    if(pg == NULL){
        p->grille = g->nextLigne;
    }else{
        pg->nextLigne=g->nextLigne;   
    }
    g->nextLigne = NULL;

    faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction]) + 2 * g->ligneSize);
    ligne_free(g);
}
void effet_MassinissaMerabet(Plateau *p, Cell *ce, int y){
    if(p->lastCarteRetourne == NULL) return;
    int faction = p->lastCarteRetourne->infosCarte.faction;
    p->lastCarteRetourne->infosCarte.faction = ce->infosCarte.faction;
    
    Ligne *g = p->grille;
    int yb = 0;
    while( g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c == p->lastCarteRetourne){
                yb = g->y;
                break;
            }
            c = c->next;
        }
        if(c == p->lastCarteRetourne) break;
        g = g->nextLigne;
    }
    effet_appliquer[p->lastCarteRetourne->infosCarte.numCarte](p,p->lastCarteRetourne, yb);
    p->lastCarteRetourne->infosCarte.faction = faction;
}
void effet_ViteraY(Plateau *p, Cell *ce, int y){
    if(faction_getDdrs(p->factions[0]) < faction_getDdrs(p->factions[1])){
        faction_setDdrs(p->factions[0], faction_getDdrs(p->factions[0])+3);
    }else if(faction_getDdrs(p->factions[1]) < faction_getDdrs(p->factions[0])){
        faction_setDdrs(p->factions[1], faction_getDdrs(p->factions[1])+3);
    }
}
void effet_JonasSenizergues(Plateau *p, Cell *ce, int y){
    //	Supprimez toutes les cartes Heures supplémentaires retournées du plateau.
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible && strcmp(carte_getNom(c->infosCarte.numCarte), "Heures supplémentaires") == 0){
                c = cell_remove(g, c);
                continue;
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
}
void effet_FetiaBannour(Plateau *p, Cell *ce, int y){
    Ligne *g = p->grille, *pg = NULL;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible && strcmp(carte_getNom(c->infosCarte.numCarte), "Heures supplémentaires") == 0){
                int x = c->x;
                if(pg != NULL){
                    pg->nextLigne=g->nextLigne;                       
                }else{
                    p->grille = g->nextLigne;
                }
                g->nextLigne=NULL;  
                ligne_free(g);
                
                g = p->grille;
                while(g != NULL){
                    c = g->firstCell;
                    while(c != NULL){
                        if(c->x == x){
                            cell_remove(g, c);
                            break;
                        }
                        c = c->next;
                    }
                    g = g->nextLigne;
                }
                return;
            }
            c = c->next;
        }
        pg = g;
        g = g->nextLigne;
    }

    int ddrs = 0;
    g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible && (
                (strcmp(carte_getNom(c->infosCarte.numCarte), "Catherine Dubois") == 0) ||
                (strcmp(carte_getNom(c->infosCarte.numCarte), "Anne-Laure Ligozat") == 0) ||
                (strcmp(carte_getNom(c->infosCarte.numCarte), "Guillaume Burel") == 0) ||
                (strcmp(carte_getNom(c->infosCarte.numCarte), "Christophe Mouilleron") == 0) ||
                (strcmp(carte_getNom(c->infosCarte.numCarte), "Thomas Lim") == 0) ||
                (strcmp(carte_getNom(c->infosCarte.numCarte), "Julien Forest") == 0) ||
                (strcmp(carte_getNom(c->infosCarte.numCarte), "Dimitri Watel") == 0))){
                ddrs++;
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
    faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])+ddrs);
}
void effet_CatherineDubois(Plateau *p, Cell *ce, int y){
    int x = ce->x;
    Ligne *g = p->grille, *pg = NULL;
    Cell *c = g->firstCell;
    // supression de la première carte de la colonne
    while(c != NULL){
        if(c->x == x){
            cell_remove(g, c);
            break;
        }
        c = c->next;
    }
    // supression de la première et la dernière carte de la ligne
    while(g != NULL){
        Cell *c = g->firstCell;
        if(g->y == y){
            c = cell_remove(g, c);
            Cell *pc = NULL;
            while(c != NULL){
                pc = c;
                c = c->next;
            }
            if(pc != NULL){
                cell_remove(g, pc);
            }
        }
        pg = g;
        g = g->nextLigne;
    }
    // supression de la dernière carte de la colonne
    c = pg->firstCell;
    while(c != NULL){
        if(c->x == x){
            cell_remove(g, c);
            break;
        }
        c = c->next;
    }
}
void effet_AnneLaureLigozat(Plateau *p, Cell *ce, int y){
    int nbCarte = 0;
    int faction = ce->infosCarte.faction;
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible && (
                (strcmp(carte_getNom(c->infosCarte.numCarte), "EcologIIE") == 0) ||
                (strcmp(carte_getNom(c->infosCarte.numCarte), "Ecocup") == 0) ||
                (strcmp(carte_getNom(c->infosCarte.numCarte), "Isolation du bâtiment") == 0) ||
                (strcmp(carte_getNom(c->infosCarte.numCarte), "parcours Sobriété numérique") == 0))){
                nbCarte++;
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
    // supprimer les nbCarte dernières cartes non retournées du plateau
    for(int i = 0; i < nbCarte; i++){
        Cell* carteNonRetourne = NULL;
        g = p->grille;
        while(g != NULL){
            Cell *c = g->firstCell;
            while(c != NULL){
                if(c->infosCarte.visible){
                    carteNonRetourne = c;
                }
                c = c->next;
            }
            g = g->nextLigne;
        }
        cell_remove(p->grille, carteNonRetourne);
    }

    faction_setDdrs(p->factions[faction], faction_getDdrs(p->factions[faction]) + nbCarte*3);
}
void effet_GuillaumeBurel(Plateau *p, Cell *ce, int y){
    int faction = (ce->infosCarte.faction+1)%2;
    if(faction_getDdrs(p->factions[faction]) > faction_getDdrs(p->factions[ce->infosCarte.faction])){
        faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])+3);
        faction_setDdrs(p->factions[faction], faction_getDdrs(p->factions[faction])-3);
    }
}
void effet_ChristopheMouilleron(Plateau *p, Cell *ce, int y){
    int retourne = 0;
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible && strcmp(carte_getNom(c->infosCarte.numCarte), "Heures supplémentaires") == 0){
                retourne = 1;
                break;
            }
            c = c->next;
        }
        if(retourne) break;
        g = g->nextLigne;
    }
    if(!retourne) return;
    g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible && (strcmp(carte_getNom(c->infosCarte.numCarte), "Heures supplémentaires") != 0 && strcmp(carte_getNom(c->infosCarte.numCarte), "Christophe Mouilleron") != 0 )){
                c = cell_remove(g, c);
                continue;
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
}
void effet_ThomasLim(Plateau *p, Cell *ce, int y){
    int estRetourne = 0;
    int nbFISE = 0;
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible){
                if(strcmp(carte_getNom(c->infosCarte.numCarte), "Julien Forest") == 0){
                    estRetourne++;
                }else if(strcmp(carte_getNom(c->infosCarte.numCarte), "FISE") == 0){
                    nbFISE++;
                }
            }
            c = c->next;
        }
        g = g->nextLigne;
    }

    if(!estRetourne){
        faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])+3*nbFISE);
    }else{
        int faction = (ce->infosCarte.faction+1)%2;
        faction_setDdrs(p->factions[faction], faction_getDdrs(p->factions[faction])-nbFISE);
    }
}
void effet_JulienForest(Plateau *p, Cell *ce, int y){
    int estRetourne = 0;
    int nbFISE = 0;
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible){
                if(strcmp(carte_getNom(c->infosCarte.numCarte), "Café") == 0){
                    estRetourne++;
                }else if(strcmp(carte_getNom(c->infosCarte.numCarte), "FISE") == 0){
                    nbFISE++;
                }
            }
            c = c->next;
        }
        g = g->nextLigne;
    }

    if(estRetourne){
        faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])+6*nbFISE);
    }
}
void effet_DimitriWatel(Plateau *p, Cell *ce, int y){
    int estRetourne = 0;
    int nbFISAFC = 0;
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible){
                if(strcmp(carte_getNom(c->infosCarte.numCarte), "Thé") == 0){
                    estRetourne++;
                }else if(strcmp(carte_getNom(c->infosCarte.numCarte), "FISA") == 0 || strcmp(carte_getNom(c->infosCarte.numCarte), "FC") == 0){
                    nbFISAFC++;
                }
            }
            c = c->next;
        }
        g = g->nextLigne;
    }

    if(estRetourne){
        faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])+3*nbFISAFC);
    }
}
void effet_DjibrilAurelienDembeleCabot(Plateau *p, Cell *ce, int y){
    Ligne *g = p->grille;
    while(g != NULL){
        if(g->y == y){
            Cell *c = g->firstCell;
            int retourne = 0;
            while(c != NULL){
                if(c->infosCarte.visible){
                    retourne++;
                    if(retourne > 3){
                        faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])+5);
                        return;
                    }
                }
                c = c->next;
            }
        }
        g = g->nextLigne;
    }
}
void effet_EricLejeune(Plateau *p, Cell *ce, int y){
    Cell **cells = malloc(sizeof(Cell*)*tailleMain*2);
    int n = 0;
    // on prend toutes les cartes retounées du plateau
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible && strcmp(carte_getNom(c->infosCarte.numCarte), "Eric Lejeune") != 0){// autrement ça peut créer une boucle infinie
                cells[n] = c;
                n++;
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
    // on les mélange
    for(int i = n-1; i >= 1; i--){
        int j = rand() % (i+1);
        Cell *tmp= cells[i];
        cells[i] = cells[j];
        cells[j] = tmp;
    }
    //on prend les 5 premières
    n = n>5?5:n;
    int estPresent=0;
    for(int i = 0; i < n;i++){
        if((strcmp(carte_getNom(cells[i]->infosCarte.numCarte), "Catherine Dubois") == 0) ||
            (strcmp(carte_getNom(cells[i]->infosCarte.numCarte), "Anne-Laure Ligozat") == 0) ||
            (strcmp(carte_getNom(cells[i]->infosCarte.numCarte), "Guillaume Burel") == 0) ||
            (strcmp(carte_getNom(cells[i]->infosCarte.numCarte), "Christophe Mouilleron") == 0) ||
            (strcmp(carte_getNom(cells[i]->infosCarte.numCarte), "Thomas Lim") == 0) ||
            (strcmp(carte_getNom(cells[i]->infosCarte.numCarte), "Julien Forest") == 0) ||
            (strcmp(carte_getNom(cells[i]->infosCarte.numCarte), "Dimitri Watel") == 0)){
                estPresent++;
                break;
            }
    }
    // on supprime les 5 cartes et enregistre les infos a conserver
    int save[5][2];
    for(int i = 0; i < n;i++){
        save[i][0] = cells[i]->infosCarte.numCarte;
        save[i][1] = cells[i]->infosCarte.faction;
        cell_remove(p->grille, cells[i]);
    }
    free(cells);
    // on ajoute ces 5 cartes à gauche de la carte la plus en haut à gauche
    if(estPresent){
        for(int i = 0; i < n; i++){
            CellInfos *ci = ligne_empiler(&(p->grille));
            ci->numCarte = save[i][0];
            ci->faction = save[i][1];
            ci->visible = 0;
        }
    }
}
void effet_LuciennePacave(Plateau *p, Cell *ce, int y){
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible && (c->x == ce->x || g->y == y) && strcmp(carte_getNom(ce->infosCarte.numCarte), "FISA") == 0){
                faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])+5);
                return;
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
}
void effet_KatrinSalhab(Plateau *p, Cell *ce, int y){
    int estRetourne[3] = {0, 0, 0};
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(c->infosCarte.visible){
                if(strcmp(carte_getNom(ce->infosCarte.numCarte), "Djibril-Aurélien Djembele-Cabeau") == 0){
                    estRetourne[0]++;
                }else if(strcmp(carte_getNom(ce->infosCarte.numCarte), "Eric Lejeune") == 0){
                    estRetourne[1]++;
                }else if (strcmp(carte_getNom(ce->infosCarte.numCarte), "Lucienne Pacavé") == 0){
                    estRetourne[2]++;
                }
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
    if(estRetourne[0] && estRetourne[1] && estRetourne[2]){
        faction_setDdrs(p->factions[ce->infosCarte.faction], faction_getDdrs(p->factions[ce->infosCarte.faction])+10);
    }else{
        g = p->grille;
        while(g != NULL){
            if(g->y == y){
                Cell *c = g->firstCell;
                while(c != NULL){
                    c->infosCarte.visible=1;
                    c = c->next;
                }
            }
            g = g->nextLigne;
        }
    }
}

int plateau_carteRetourner(Plateau *p){
    Ligne *g = p->grille;
    while(g != NULL){
        Cell *c = g->firstCell;
        while(c != NULL){
            if(!c->infosCarte.visible){
                c->infosCarte.visible=1;
                printf("plateau_carteRetourner(): de la carte %s \n", carte_getNom(c->infosCarte.numCarte));
                if(effet_appliquer[c->infosCarte.numCarte] != NULL){
                    effet_appliquer[c->infosCarte.numCarte](p, c, g->y);
                }
                p->lastCarteRetourne = c;
                while(p->grille->firstCell == NULL){
                    Ligne *g = p->grille;
                    p->grille = g->nextLigne;
                    g->nextLigne = NULL;
                    ligne_free(g);
                }
                return c->infosCarte.numCarte;
            }
            c = c->next;
        }
        g = g->nextLigne;
    }
    return -1;
}
