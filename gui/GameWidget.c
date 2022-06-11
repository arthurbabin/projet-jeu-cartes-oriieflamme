#include "GameWidget.h"

SDL_FPoint posT; //position relative à la texture de fond en haut à gauche
SDL_Point sizeT; // taille de la texture de fond

SDL_Point moveDepart; 
SDL_bool isMoving; // si un mouvement de déplacement dans le plateau a démarré

SDL_FPoint posC; // position du coin en haut à gauche de la caméra
float scale;  // facteur de zoom

void gameWidget_onPaint(Widget* w, Painter* p){
    SDL_Point pt;
    if(posT.x <0){
        pt.x=(1+posT.x)*sizeT.x*scale;
    }else{
        pt.x=posT.x*sizeT.x*scale;
    }
    if(posT.y <0){
        pt.y=(1+posT.y)*sizeT.y*scale;
    }else{
        pt.y=posT.y*sizeT.y*scale;
    }
    SDL_Rect rect = { 0, 0, w->bw->width, w->bw->height };
    painter_drawTextureRepeatScale(p, asset_texture_fond, &pt, &rect, scale);

    painter_setStrokeSize(p, 4);
    painter_setStrokeColor(p, 255, 255, 255, 255);
    SDL_Point cardSize = {100,150};
    SDL_Point card = {1, 3};
    

    painter_drawStrokeRect(p, 0, 0, 100, 150);
}

void gameWidget_onMousePress(Widget* w, Widget_MouseClickEvent* mce){
    isMoving = SDL_TRUE;
    moveDepart.x=mce->pos.x;
    moveDepart.y=mce->pos.y;
}
void gameWidget_onMouseRelease(Widget* w, Widget_MouseClickEvent* mce){
    if(isMoving){
        isMoving=SDL_FALSE;
        posC.x -= (float)(mce->pos.x-moveDepart.x)/(sizeT.x*scale);
        posC.y -= (float)(mce->pos.y-moveDepart.y)/(sizeT.y*scale);
        posT=posC;   
        posT.x -= (int)posT.x;
        posT.y -= (int)posT.y;
    }
}
void gameWidget_onMouseMove(Widget* w, Widget_MouseMoveEvent* mme){
    if(isMoving){
        posC.x -= (float)(mme->pos.x-moveDepart.x)/(sizeT.x*scale);
        posC.y -= (float)(mme->pos.y-moveDepart.y)/(sizeT.y*scale);
        posT=posC;
        posT.x -= (int)posT.x;
        posT.y -= (int)posT.y;
        moveDepart.x=mme->pos.x;
        moveDepart.y=mme->pos.y;
    }
}

void gameWidget_onMouseWheel(Widget* w, SDL_Point *scroll){   
    scale += (float)scroll->y/10;
    if(scale<0.1){
        scale=0.1;
    }
}

Widget* new_GameWidget(DWindow *window){
    Widget *w = new_BaseWidget(WIDGET_BASE);
    posT.x=0.0;
    posT.y=0.0;
    posC.x=0.0;
    posC.y=0.0;
    isMoving = SDL_FALSE;
    scale = 1.0;
    SDL_QueryTexture(asset_texture_fond, NULL, NULL, &sizeT.x, &sizeT.y);

    w->bw->onPaint=gameWidget_onPaint;
    w->bw->onMousePress=gameWidget_onMousePress;
    w->bw->onMouseRelease=gameWidget_onMouseRelease;
    w->bw->onMouseMove=gameWidget_onMouseMove;
    w->bw->onMouseWheel=gameWidget_onMouseWheel;
    return w;
}

void gameWidget_free(Widget* w){
    baseWidget_free(w);
}