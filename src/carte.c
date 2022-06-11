#include "../headers/carte.h"

struct Carte {
    char id[5];
    char nom[40];
    char description[1000];
    int occurence;
};

Carte cartes[32] = {
    {
        "FISE",//0
        "FISE",
        "La faction qui a posé cette carte gagne 1 point DDRS.",
        4
    },
    {
        "FISA",
        "FISA",
        "La faction qui a posé cette carte gagne 2 points DDRS si le nombre de cartes retournées sur le plateau (y compris celle-ci) est pair, et 0 sinon.",
        4
    },
    {
        "FC  ",
        "FC",
        "La faction qui a posé cette carte gagne 4 points DDRS si au moins une autre carte FC est retournée sur le plateau et 0 sinon",
        4
    },
    {
        "ECO ",
        "EcologIIE",
        "La faction qui a posé cette carte gagne 1 point DDRS par carte FISE/FISA/FC retournée.",
        2
    },
    {
        "IIEN",
        "IIIEns",
        "Prenez toutes les cartes FISE/FISA/FC retournées, retirez les du plateau, mélangez les et reposez les face cachées une par une sur la gauche de la carte la plus en haut à gauche du plateau, dans cet ordre. Les prochaines cartes à être retournées sont ces cartes là.",
        2
    },
    {
        "SSA ",
        "Soirée sans alcool",
        "Si au moins une carte alcool est retournée, supprimez toutes les cartes FISE/FISA/FC retournées du plateau. Supprimez ensuite la première et la dernière ligne du plateau. Sinon la faction qui a posé cette carte gagne 5 points DDRS.",
        1
    },
    {
        "ALCO",
        "Alcool",
        "Supprimez du plateau toutes les cartes qui touchent cette carte-ci (mais laissez la carte Alcool sur le plateau).",
        1
    },
    {
        "CAFE",
        "Café",
        "Supprimez toutes les cartes Thé et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.",
        3
    },
    {
        "THE ",
        "Thé",
        "Supprimez toutes les cartes Café et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.",
        3
    },
    {
        "CUP",
        "Ecocup",
        "Cette carte est sans effet.",
        1
    },
    {
        "REPR",//10
        "Reprographie",
        "La faction adverse de celle qui a posé cette carte perd 1 points DDRS pour chaque paire de cartes retournées et identiques sur le plateau. (S'il y a 3 cartes identiques, cela fait 3 paires).",
        1
    },
    {
        "ISOB",
        "Isolation du bâtiment",
        "Chaque faction gagne 1 point DDRS par carte non retournée et non supprimée du plateau qu'elle a posée sur le plateau.",
        1
    },
    {
        "PSNU",
        "Parcours sobriété numérique",
        "Retournez toutes les cartes non retournées les plus à gauche et à droite de chaque ligne, sans appliquer leur effet.",
        1
    },
    {
        "HSUP",
        "Heures supplémentaires",
        "La faction adverse de celle qui a posé cette carte perd 3 points DDRS par carte Heures supplémentaires retournée sur le plateau (y compris celle-ci).",
        1
    },
    {
        "KABO",//14
        "Kahina Bouchama",
        "Supprimez une carte non retournée du plateau choisie au hasard.",
        1
    },
    {
        "KEGO",//15
        "Kevin Goilard",
        "Supprimez une ligne au hasard, la faction qui a posé cette carte gagne 2 points DDRS par carte supprimée ainsi.",
        1
    },
    {
        "MAME",
        "Massinissa Merabet",
        "La faction qui a posé cette carte réactive l'effet de la dernière carte retournée avant Massinissa Merabet, en faisant comme elle l'avait posée elle-même, même si ce n'est pas le cas.",
        1
    },
    {
        "VI Y",
        "Vitéra Y",
        "La faction qui a le moins de points DDRS gagne 3 points DDRS.",
        1
    },
    {
        "JOSE",
        "Jonas Senizergues",
        "Supprimez toutes les cartes Heures supplémentaires retournées du plateau.",
        1
    },
    {
        "FEBA",
        "Fetia Bannour",
        "Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes de la ligne et de la colonne où est posée cette carte (y compris celle-ci). Sinon la faction qui a posé cette carte gagne 1 point DDRS par carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest et Dimitri Watel retournée sur le plateau.",
        1
    },
    {
        "CADU",//20
        "Catherine Dubois",
        "Supprimez la première et la dernière cartes de la ligne et de la colonne où est posée cette carte.",
        1
    },
    {
        "ALLI",
        "Anne-Laure Ligozat",
        "Pour chaque carte EcologIIE, Ecocup, Isolation du bâtiment et parcours Sobriété numérique retournée, la faction qui a posé cette carte gagne 3 points DDRS et la dernière carte non retournée du plateau est supprimée. (L'effet continue même si Anne-Laure Ligozat ou une des 4 cartes précédemment mentionnées est supprimée).",
        1
    },
    {
        "GUBU",
        "Guillaume Burel",
        "Si la faction adverse de celle qui a posé cette carte a plus de points DDRS, la seconde lui vole 3 points DDRS.",
        1
    },
    {
        "CHMO",
        "Christophe Mouilleron",
        "Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes retournées du plateau sauf les cartes Christophe Mouilleron et Heures supplémentaires.",
        1
    },
    {
        "THLI",
        "Thomas Lim",
        "Si Julien Forest n'est par retourné sur le plateau, la faction qui a posé cette carte gagne 3 points DDRS par carte FISE retournée sur le plateau. Sinon la faction adverse perd 1 point DDRS par carte FISE retournée sur le plateau.",
        1
    },
    {
        "JUFO",
        "Julien Forest",
        "La faction qui a posé cette carte gagne 6 points DDRS par carte FISE retournée sur le plateau si au moins une carte Café est retournée sur le plateau.",
        1
    },
    {
        "DIWA",
        "Dimitri Watel",
        "La faction qui a posé cette carte gagne 3 points DDRS par carte FISA ou FC retournée sur le plateau si au moins une carte Thé est retournée sur le plateau.",
        1
    },
    {
        "DADC",
        "Djibril-Aurélien Dembele-Cabot",
        "S'il y a plus de 3 cartes retournées sur la ligne de cette carte, la faction qui a posé cette carte gagne 5 points DDRS.",
        1
    },
    {
        "ERLE",
        "Eric Lejeune",
        "Prenez au hasard 5 cartes retournées du plateau (ou toutes les cartes retournées du plateau s'il y a moins de 5). Si une de ces cartes est une carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest ou Dimitri Watel, mélangez les et placez les à gauche de la case la plus à gauche de la première ligne. Les prochaines cartes à être retournées sont ces cartes là. Sinon, supprimez ces cartes du plateau.",
        1
    },
    {
        "LUPA",
        "Lucienne Pacavé",
        "S'il y a une carte FISA retournée dans la même ligne ou la même colonne que cette carte, la faction qui a posé cette carte gagne 5 points DDRS.",
        1
    },
    {
        "KASA",//30
        "Katrin Salhab",
        "Si les cartes Djibril-Aurélien Djembele-Cabeau, Eric Lejeune et Lucienne Pacavé sont retournées, la faction qui a posé cette carte gagne 10 points DDRS. Sinon, retournez toutes les cartes dans la même ligne de cette carte sans appliquer leurs effets.",
        1
    },
    {
        "LAPR",
        "Laurent Prével",
        "Si Laurent Prével est la dernière carte retournée du plateau, la faction qui a posé cette carte gagne la manche, quel que soit le nombre de points DDRS des deux factions.",
        1
    }
};


char* carte_getId(int c){
    return cartes[c].id;
}
char* carte_getNom(int c){
    return cartes[c].nom;
}
char* carte_getDescription(int c){
    return cartes[c].description;
}
int carte_getOccurence(int c){
    return cartes[c].occurence;
}
