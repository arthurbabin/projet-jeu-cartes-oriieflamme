#include "MenuWidget.h"

DWindow* window;
Widget* btn;
Widget* fac[2];

void menuWidget_onPaint(Widget* w, Painter* p){
    painter_setStrokeColor(p,200,200,200,255);

    SDL_Rect rect= {0,0, 0.2*w->bw->width, w->bw->height};
    SDL_Point pt = {0, 0};
    
    painter_drawTextureRepeat(p, asset_texture_fond, &pt, &rect);
    rect.x=0.8*w->bw->width;
    painter_drawTextureRepeat(p, asset_texture_fond, &pt, &rect);

    rect.x= 0.2*w->bw->width;
    rect.w= 0.6*w->bw->width;

    rect.h=0.25*w->bw->height;
    painter_drawTexture(p, asset_texture_menuTitle, NULL, &rect);
}

void menuWidget_onResize(Widget* w, Widget_ResizeEvent* re){
    widget_setLocation(btn, (re->newSize.x-btn->bw->width)/2, 0.8*re->newSize.y);
    int x = (re->newSize.x-fac[0]->bw->width*2-50)/2;
    widget_setLocation(fac[0], x,  0.4*re->newSize.y );
    widget_setLocation(fac[1], x+fac[0]->bw->width+50, 0.4*re->newSize.y );
}

void menuWidget_onAction(){
    printf("Jouer !\n");
    Widget *w = new_GameWidget(window);
    DWindow_setContent(window, w);
}

Widget* new_MenuWidget(DWindow* fenetre){
    Widget *w = new_BaseWidget(WIDGET_MENU);
    window = fenetre;
    
    btn = new_ButtonWidget("Jouer");
    widget_add(w, btn);
    widget_setSize(btn, 300, 50);

    for(int i = 0; i < 2; i++){
        fac[i] = new_TextEditWidget("Faction n", 30);
        widget_add(w, fac[i]);
        widget_setSize(fac[i], 200, 50);
    }

    w->bw->onPaint=menuWidget_onPaint;
    w->bw->onResize=menuWidget_onResize;
    btn->button.onAction=menuWidget_onAction;
    return w;
}

void menuWidget_free(Widget* w){
    baseWidget_free(w);
    window=NULL;
    btn=NULL;
}