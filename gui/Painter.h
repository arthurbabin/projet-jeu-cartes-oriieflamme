#ifndef PAINTER
#define PAINTER

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

typedef struct Painter {
    SDL_Renderer* renderer;
    int padX, padY;
    SDL_Color fillColor;
    SDL_Color strokeColor;
    Uint8 strokeSize;
} Painter;

Painter* new_Painter(SDL_Window *window);
void painter_free(Painter* p);

void painter_setFillColor(Painter *p, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void painter_setStrokeColor(Painter *p, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void painter_setStrokeSize(Painter *p, Uint8 w);

void painter_drawPoint(Painter *p, int x, int y);
void painter_drawLine(Painter *p, SDL_Point *pt1, SDL_Point *pt2);

void painter_drawFillRect(Painter *p, int x, int y, int width, int height);
void painter_drawStrokeRect(Painter *p, int x, int y, int width, int height);
void painter_drawRect(Painter *p, int x, int y, int width, int height);

void painter_freeFont(TTF_Font *font);
TTF_Font* painter_loadFont(Painter *p, const char* font, int size);
int painter_textSize(Painter *p, TTF_Font* font, const char *text, SDL_Point *pt);
int painter_charWidth(Painter *p, TTF_Font* font, char c, int* width);
void painter_drawText(Painter *p, TTF_Font* font, int x, int y, const char * txt);


SDL_Texture* painter_loadTexture(Painter *p, const char *path);
void painter_freeTexture(SDL_Texture* texture);
void painter_drawTextureRepeat(Painter *p, SDL_Texture* ttr, SDL_Point *src, SDL_Rect *dst);
void painter_drawTextureRepeatScale(Painter *p, SDL_Texture* ttr, SDL_Point *src, SDL_Rect *dst, float scale);
void painter_drawTexture(Painter *p, SDL_Texture* ttr, SDL_Rect *src, SDL_Rect *dst );

#endif