CC = gcc -L ../SDL/lib -I ../SDL/include -Wall -ggdb3 -Wextra  -Wno-unused-parameter -Wno-unused-variable -std=c99 -Wno-unused-function
SDLFLAGS= -mfpmath=sse -msse3 -lm -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2 
OBJ = ./obj/


all: gui

$(OBJ)%.o: %.c
	$(CC) -c $< -o $@ $(SDLFLAGS)
	
gui: $(OBJ)mainM.o $(OBJ)DWindow.o $(OBJ)BaseWidget.o $(OBJ)Widget.o $(OBJ)Painter.o $(OBJ)ButtonWidget.o $(OBJ)TextEditWidget.o $(OBJ)MenuWidget.o $(OBJ)GameWidget.o
	$(CC) -o $@ $^ $(SDLFLAGS)

clean:
	rm -rf obj/*.o