# Projet informatique OrIIEflamme

<aside>
💡 Mettre Tâches X.X dans les commits
</aside>

### Convention de nommage

```[nom de l'interface]_[nom de la fonction en camelCase]```

Exemple : ```void faction_viderDansPioche(...)```

# Intro

2 joueurs = 2 factions

Plusieurs manches (bo3)

Les factions posent des cartes à tour de rôle

# Manche

## Phase 1

- chacun a
    - boîte à idées
    - pile de cartes mélangées

### Initialisation

- chaque faction pioche 8 carte de sa pile
    
    <aside>
    💡 une fois dans la partie chaque faction peu remettre sa main dans la boîte remélanger et repiocher 8 cartes au début de la manche
    
    </aside>
    
- Première faction désignée au hasard à la première manche puis la main passe à l’autre faction pour la deuxième manche (aléatoire si 3e manche)
- Plateau = Grille 2D de taille infinie (mais max 16x16)

### Corps Phase 1

- à tour de rôle chaque faction dépose une carte face cachée sur une case libre du plateau
    - la carte doit avoir un côté en commun avec une carte déjà posée

## Phase 2

- de gauche à droite et de haut en bas on retourne les cartes
    
    <aside>
    💡 l’effet de la carte est appliqué lorsqu’elle est retournée.
    
    </aside>
    

## Victoire

- la faction qui a le plus de points DDRS à l’issue de la manche
- égalité ⇒ la faction dont la carte est la plus en haut à gauche gagne

# Lot A

## Tâche A.1

- mise en place du dépôt Git et du GanttProject
- codage du fichier main.c
- vérifier que le main.c compile bien avec toutes les interfaces réunies (obtention d'un main.o)

## Tâche A.2

## Tâche A.3

## Tâche A.4

- afficher le plateau
- afficher la main d’une faction
- demander à une faction si elle veut utiliser son option permettant de repiocher sa main
- demander quelle carte poser
- demander où poser
- afficher les effets d’une carte
- afficher le vainqueur de la partie
