# @file : Makefile du projet informatique
# @author : Teddy ALEXANDRE (Tâche B.1), Arthur BABIN (Tâche C.4)
# Pour faire tourner le projet, taper 'make all' dans un terminal

#Commande de compilation avec éventuel affichage des warnings
CC = gcc -Wall -Wextra  -Wno-unused-parameter -Wno-unused-variable -std=c99

#SDL Flags
SDLe = $(shell sdl2-config --cflags --libs) -lSDL2_ttf
SDL = -I$(shell pwd)/SDL/SDL2 -D_REENTRANT -pthread -lSDL2 -lSDL2_ttf

# Ensemble des fichiers objets
OBJ = ./obj/

# Ensemble des headers
HD = ./headers/

# Ensemble des fichiers sources
SRC = ./src/

# Ensemble des fichiers GUI (widgets de base)
GUI = ./gui/

# Exécute le projet
all: projet-interfaceGraphique

# Supprime les fichiers objets
clean:
	rm -rf prog *.o

#Supprime les fichiers liés au projet
cleanproj:
	rm -rf all

# Création des fichiers objets
$(OBJ)%.o: $(SRC)%.c
	$(CC) -c $< -o $@

# Edition de liens -> exécutable projet version interface graphique 
projet-interfaceGraphique: $(SRC)main.c
	$(CC) -o $@ $^ $(SDL)


# Edition de liens -> exécutable projet version console
projet-console: $(OBJ)mainConsole.o $(OBJ)carte.o $(OBJ)faction.o $(OBJ)interface.o $(OBJ)plateau.o $(OBJ)structure.o
	$(CC) -o $@ $^

#Commande pour exécuter les tests avec CUnit
test: $(SRC)test.c $(OBJ)carte.o $(OBJ)faction.o $(OBJ)interface.o $(OBJ)plateau.o $(OBJ)structure.o
	$(CC) -o $@ $^ -lcunit -I${HOME}/local/include -L${HOME}/local/lib

# Ensemble des dépendances
$(OBJ)carte.o: $(HD)carte.h $(SRC)carte.c

$(OBJ)faction.o: $(HD)faction.h $(SRC)faction.c

$(OBJ)interface.o: $(HD)interface.h $(SRC)interface.c

$(OBJ)plateau.o: $(HD)plateau.h $(SRC)plateau.c

$(OBJ)structure.o: $(HD)structure.h $(SRC)structure.c
