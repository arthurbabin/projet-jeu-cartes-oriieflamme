#include <stdio.h>
#include "Asset.h"
#include "DWindow.h"
#include "MenuWidget.h"


int main(int argc, char *argv[]){
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return -1;
    }

    DWindow *window = new_DWindow("OrIIEflamme",800,600);
    Widget *w = new_MenuWidget(window);

    if(window != NULL){
        asset_init(window->painter);
        DWindow_setContent(window, w); // à partir de la, w  prend toute la place dans la fenetre

        DWindow_start(window);

        asset_free();
        DWindow_free(window);
    }

    SDL_Quit();
    return 0;
}