#ifndef ASSET
#define ASSET

#include "Painter.h"

TTF_Font* asset_font_arial18;
SDL_Texture* asset_texture_fond;
SDL_Texture* asset_texture_menuTitle;

static void asset_init(Painter* p){
    asset_font_arial18=painter_loadFont(p, "arial.ttf", 18);
    asset_texture_fond=painter_loadTexture(p, "./Hexagon.png");
    asset_texture_menuTitle=painter_loadTexture(p, "./title.png");
}

static void asset_free(){
    painter_freeFont(asset_font_arial18);
    painter_freeTexture(asset_texture_fond);
    painter_freeTexture(asset_texture_menuTitle);
}

#endif