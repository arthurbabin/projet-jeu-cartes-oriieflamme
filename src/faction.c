#include "../headers/faction.h"

struct Faction {
    char nom[30];
    int ddrs;
    List *main;
    List *pioche;
    int remelanger;
    int manche;
};

Faction* faction_new(char* name){
    Faction* fac = malloc(sizeof(Faction));
    fac->ddrs = 0;
    strcpy(fac->nom, name);
    fac->main = list_create();
    fac->pioche = list_create();
    for(int i = 0; i < 32; i++){
        for(int j = 0; j < carte_getOccurence(i); j++){
            list_empiler(fac->pioche, i);
        }
    }
    faction_melangerPioche(fac);
    fac->remelanger = 0;
    fac->manche = 0;

    return fac;
}

void faction_free(Faction *fac){
    list_free(fac->main);
    list_free(fac->pioche);
}

int faction_dejaRemelange(Faction *fac){
    return fac->remelanger;
}

void faction_remelanger(Faction *fac){
    faction_viderDansPioche(fac);
    faction_melangerPioche(fac);
    faction_piocher(fac);
    fac->remelanger = 1;
}

void faction_viderDansPioche(Faction *fac){
    while(fac->main->size > 0){
        list_empiler(fac->pioche,list_depiler(fac->main));
    }
}

void faction_piocher(Faction *fac){
    for(int i = 0; i < tailleMain; i++){
        list_empiler(fac->main, list_depiler(fac->pioche));
    }
}

void faction_melangerPioche(Faction *fac){
    for(int i = fac->pioche->size-1; i >= 1; i--){
        int j = rand() % (i+1);
        list_swap(fac->pioche, i, j);
    }
}

char* faction_getNom(Faction* fac){
    return fac->nom;
}
void faction_setNom(Faction* fac, char* nom){
    strcpy(fac->nom, nom);
}
int faction_getDdrs(Faction* fac){
    return fac->ddrs;
}
void faction_setDdrs(Faction* fac, int ddrs){
    fac->ddrs = ddrs;
}
List* faction_getMain(Faction* fac){
    return fac->main;
}
int faction_getManche(Faction* fac){
    return fac->manche;
}
void faction_setManche(Faction* fac, int manche){
    fac->manche=manche;
}