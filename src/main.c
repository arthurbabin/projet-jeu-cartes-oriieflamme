#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Transmet par inférence la texture du texte ainsi que son rectangle
 * associé
 * @param renderer le renderer
 * @param x l'abscisse du coin en haut à gauche de la texture
 * @param y l'ordonnée du coin en haut à gauche de la texture
 * @param text le texte à associer à la texture
 * @param font la police à utiliser pour le texte
 * @param textColor un 'SDL_Color' correspondant à la couleur du texte
 * @param texture un pointeur vers un 'SDL_Texture*'
 * @param rect un pointeur vers un 'SDL_Rect'
 */
void getTextAndRect(SDL_Renderer *renderer, int x, int y, char *text,
        TTF_Font *font, SDL_Color textColor, 
        SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}

int main(int argc, char *argv[]){

    //Initialisation
    int status = EXIT_FAILURE;
    SDL_Event event;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    char* fontPath = "assets/customFont.ttf";
    TTF_Init();
    TTF_Font* font = TTF_OpenFont(fontPath,24);

    if(0 != SDL_Init(SDL_INIT_VIDEO)){
        fprintf(stderr,"Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }

    window = SDL_CreateWindow(
            "Projet Oriieflamme",
            SDL_WINDOWPOS_UNDEFINED, //x
            SDL_WINDOWPOS_UNDEFINED, //y
            500, //width
            500, //height
            SDL_WINDOW_SHOWN);
    
    if (NULL == window) {
        fprintf(stderr,"Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if (NULL == renderer) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }

    //Variables
    SDL_Color black = {0,0,0,255};
    SDL_Color red = {254,67,60,255};
    SDL_Color blue = {0,149,239,255};


    //Draw Rectangle
    SDL_Rect rect = {100, 300, 100, 100};
    SDL_Surface* rectangleExample = SDL_CreateRGBSurface(0,
            32,
            32,
            32, //number of bits per pixels
            0,0,0,0); //masks
    SDL_FillRect(rectangleExample,
            NULL,
            SDL_MapRGB(rectangleExample->format, red.r, red.g, red.b));
    SDL_Texture* rectangleExampleTexture = 
        SDL_CreateTextureFromSurface(renderer, rectangleExample);

    //Text
    SDL_Texture *exampleTextTexture;
    SDL_Rect exampleTextRect;
    getTextAndRect(renderer,
            100,
            50,
            "Oriieflamme",
            font,
            blue,
            &exampleTextTexture,
            &exampleTextRect);

    int quit=0;
    while(!quit){
        while(SDL_PollEvent(&event)==1){
            if(event.type==SDL_QUIT){
                quit=1;
            }
        }
        //Set Window Color
        SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,
                exampleTextTexture,
                NULL, 
                &exampleTextRect);
        SDL_RenderCopy(renderer,
                rectangleExampleTexture,
                NULL,
                &rect);
        SDL_RenderPresent(renderer);
    }

    status = EXIT_SUCCESS;

Quit:
    SDL_DestroyTexture(exampleTextTexture);
    TTF_Quit();
    if (NULL != renderer) {
       SDL_DestroyRenderer(renderer); 
    }
    if (NULL != window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return status;
}
