#ifndef DWINDOW
#define DWINDOW

#include <stdio.h>
#include <SDL2/SDL.h>
#include "BaseWidget.h"
#include "Painter.h"
#include "Events.h"

#define NO_STDIO_REDIRECT

typedef struct DWindow {
    SDL_Window* window;
    Painter *painter;
    Widget* content;
    Widget* focus;
} DWindow;

DWindow* new_DWindow(const char* title, int width, int height);
void DWindow_free(DWindow*);
void DWindow_start(DWindow*);
Widget* DWindow_setContent(DWindow* window, Widget *w);

#endif