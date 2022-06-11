#include "Painter.h"

Painter* new_Painter(SDL_Window *window){
    Painter *p = malloc(sizeof(Painter));
    p->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(p->renderer == NULL){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return NULL;
    }
    SDL_SetRenderTarget(p->renderer, NULL);
    if(SDL_SetRenderDrawBlendMode(p->renderer, SDL_BLENDMODE_BLEND) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
    }
    if (TTF_Init() < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
        return NULL;
    }

    p->padX=0;
    p->padY=0;
    p->strokeSize=1;

    return p;
}

void painter_free(Painter* p){
    SDL_DestroyRenderer(p->renderer);
    TTF_Quit();
    free(p);
}

void painter_setFillColor(Painter *p, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    p->fillColor.r=r;
    p->fillColor.g=g;
    p->fillColor.b=b;
    p->fillColor.a=a;
}

void painter_setStrokeColor(Painter *p, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    p->strokeColor.r=r;
    p->strokeColor.g=g;
    p->strokeColor.b=b;
    p->strokeColor.a=a;
}

void painter_setStrokeSize(Painter *p, Uint8 w){
    p->strokeSize=w;
}

void painter_drawPoint(Painter *p, int x, int y){
    SDL_SetRenderDrawColor(p->renderer, p->fillColor.r, p->fillColor.g, p->fillColor.b, p->fillColor.a);
    SDL_RenderDrawPoint(p->renderer, x+p->padX, y+p->padY);
}

void painter_drawLine(Painter *p, SDL_Point *pt1, SDL_Point *pt2){
    SDL_SetRenderDrawColor(p->renderer, p->strokeColor.r, p->strokeColor.g, p->strokeColor.b, p->strokeColor.a);
    for(int i = 0; i < p->strokeSize; i++){
        SDL_RenderDrawLine(p->renderer, pt1->x+i+p->padX, pt1->y+p->padY, pt2->x+i+p->padX, pt2->y+p->padY);
    }
}

void painter_drawFillRect(Painter *p, int x, int y, int width, int height){
    SDL_Rect rect;
    rect.x=x+p->padX;
    rect.y=y+p->padY;
    rect.w=width;
    rect.h=height;
    SDL_SetRenderDrawColor(p->renderer, p->fillColor.r, p->fillColor.g, p->fillColor.b, p->fillColor.a);
    SDL_RenderFillRect(p->renderer,&rect);
}

void painter_drawStrokeRect(Painter *p, int x, int y, int width, int height){
    SDL_Rect rect;
    rect.x=x+p->padX;
    rect.y=y+p->padY;
    rect.w=width;
    rect.h=height;

    SDL_SetRenderDrawColor(p->renderer, p->strokeColor.r, p->strokeColor.g, p->strokeColor.b, p->strokeColor.a);
    for(int i = 0; i < p->strokeSize; i++){
        SDL_RenderDrawRect(p->renderer, &rect);
        rect.x++;
        rect.y++;
        rect.w-=2;
        rect.h-=2;
    }
}

void painter_drawRect(Painter *p, int x, int y, int width, int height){
    if(p->fillColor.a != 0){
        painter_drawFillRect(p, x+p->strokeSize, y+p->strokeSize, width-2*p->strokeSize, height-2*p->strokeSize);
    }
    if(p->strokeColor.a != 0){
        painter_drawStrokeRect(p, x, y, width, height);
    }
}

void painter_freeFont(TTF_Font *font){
    if(font != NULL){
        TTF_CloseFont(font);
    }
}
TTF_Font* painter_loadFont(Painter *p, const char* font, int size){
    return TTF_OpenFont(font, size);
}
int painter_textSize( Painter *p, TTF_Font* font, const char *text, SDL_Point *pt){
    return TTF_SizeUTF8(font, text, &pt->x, &pt->y);
}
int painter_charWidth(Painter *p,TTF_Font* font, char c, int* width){
    return TTF_GlyphMetrics(font, c, NULL,NULL,NULL,NULL, width);
}

void painter_drawText(Painter *p, TTF_Font* font, int x, int y, const char * txt){
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, txt, p->strokeColor);
    if(surface==NULL) return;
    SDL_Texture *ttr = SDL_CreateTextureFromSurface(p->renderer, surface);
    SDL_Rect rect = {x+p->padX, y+p->padY, surface->w, surface->h};
    SDL_RenderCopy(p->renderer, ttr, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(ttr);
}

SDL_Texture* painter_loadTexture(Painter *p, const char *path){
    SDL_Surface *surface = IMG_Load(path);
    if(surface == NULL){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", IMG_GetError());
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(p->renderer, surface);
    if( texture == NULL){
        printf("Error> CreateTextureFromSurface: %s\n", SDL_GetError());
    } 
    SDL_FreeSurface(surface);
    return texture;
}
void painter_freeTexture(SDL_Texture* texture){
    SDL_DestroyTexture(texture);
}

/**
 * Dessine une texture dans la zone définie par le rectangle dst. Si le rectangle dst est plus grand que la texture, alors la texture sera répété.
 * 
 * @param p le Painter
 * @param texture @see SDL_Texture la texture à dessiner
 * @param src @see SDL_Point interne à la texture à partir duquel on la dessinera
 * @param dst @see SDL_Rect la position et la taille du rectangle dans lequel on dessinera la texture
 */
void painter_drawTextureRepeat(Painter *p, SDL_Texture* ttr, SDL_Point *src, SDL_Rect *dst){
    int width, height;
    SDL_QueryTexture(ttr, NULL, NULL, &width, &height);
    SDL_Rect rsrc = { 0, src->y, 0, (height-src->y < dst->h)?height-src->y:dst->h };
    SDL_Rect rdst = { 0, dst->y+p->padY, 0, rsrc.h };

    while(rdst.y < p->padY+dst->y+dst->h){
        rsrc.x=src->x;
        rdst.x=dst->x+p->padX;
        rsrc.w= (width-src->x < dst->w) ? width-src->x : dst->w;
        rdst.w=rsrc.w;

        while(rdst.x < dst->w+dst->x+p->padX){
            if( SDL_RenderCopy(p->renderer, ttr, &rsrc, &rdst) < 0){
                printf("Error> renderCopy: %s\n", SDL_GetError());
            }  
            rsrc.x=0;
            rdst.x+=rdst.w;
            rsrc.w= ((dst->w+p->padX+dst->x)-(rdst.x)>width)? width: (dst->w+p->padX+dst->x)-(rdst.x);      
            rdst.w=rsrc.w;
        }
        rsrc.y=0;
        rdst.y+=rdst.h;
        rsrc.h=((dst->h+p->padY+dst->y)-(rdst.y) > height)? height:(dst->h+p->padY+dst->y)-(rdst.y);
        rdst.h=rsrc.h;
    }
}

void painter_drawTextureRepeatScale(Painter *p, SDL_Texture* ttr, SDL_Point *src, SDL_Rect *dst, float scale){
    int width, height;
    SDL_QueryTexture(ttr, NULL, NULL, &width, &height);
    width *= scale;
    height *= scale;

    SDL_Rect rsrc = { 0, src->y, 0, (height-src->y < dst->h)?height-src->y:dst->h };
    SDL_Rect rdst = { 0, dst->y+p->padY, 0, rsrc.h };
    SDL_Rect tmp;
    while(rdst.y < p->padY+dst->y+dst->h){
        rsrc.x=src->x;
        rdst.x=dst->x+p->padX;
        rsrc.w= (width-src->x < dst->w) ? width-src->x : dst->w;
        rdst.w=rsrc.w;

        while(rdst.x < dst->w+dst->x+p->padX){
            tmp=rsrc;
            tmp.w /= scale;
            tmp.h /= scale;
            tmp.x /= scale;
            tmp.y /= scale;
            if( SDL_RenderCopy(p->renderer, ttr, &tmp, &rdst) < 0){
                printf("Error> renderCopy: %s\n", SDL_GetError());
            }  
            rsrc.x=0;
            rdst.x+=rdst.w;
            rsrc.w= ((dst->w+p->padX+dst->x)-(rdst.x)>width)? width: (dst->w+p->padX+dst->x)-(rdst.x);      
            rdst.w=rsrc.w;
        }
        rsrc.y=0;
        rdst.y+=rdst.h;
        rsrc.h=((dst->h+p->padY+dst->y)-(rdst.y) > height)? height:(dst->h+p->padY+dst->y)-(rdst.y);
        rdst.h=rsrc.h;
    }
}

void painter_drawTexture(Painter *p, SDL_Texture* ttr, SDL_Rect *src, SDL_Rect *dst ){
    SDL_RenderCopy(p->renderer, ttr, src, dst);
}
