#include "ButtonWidget.h"


void buttonWidget_onPaint(Widget* w, Painter* p){
    painter_setStrokeSize(p, 2);
    painter_setStrokeColor(p,200,200,200,255);

    switch(w->button.state){
        case 0: //normal
            painter_setFillColor(p,35,35,35,255);
            break;
        case 1: // hover
            painter_setFillColor(p,20,20,20,255);
            break;
        case 2: // pressed
            painter_setFillColor(p,0,0,0,255);
            break;
    }  

    painter_drawRect(p,0, 0, w->bw->width, w->bw->height);
    SDL_Point pt;
    if(painter_textSize(p, asset_font_arial18 , w->button.text, &pt) == 0){
        painter_drawText(p, asset_font_arial18, (w->bw->width-pt.x)/2, (w->bw->height-pt.y)/2, w->button.text);
    }else{
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[textSize] > %s", w->button.text);
    }
    // je ne sais pas pourquoi, mais si je ne fais pas ça, les textures n'affichent que du blanc... j'espère que c'est un bug du WSL
    SDL_Point pt1 = { 0,0};
    SDL_Point pt2 = { 10,0};
    painter_drawLine(p, &pt1, &pt2);
}

void buttonWidget_onMouseEnter(Widget* w){
    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
    w->button.state=1;
}

void buttonWidget_onMouseLeave(Widget* w){
    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
    w->button.state=0;
}

void buttonWidget_onMousePress(Widget* w, Widget_MouseClickEvent* mce){
    w->button.state=2;
}

void buttonWidget_onMouseRelease(Widget* w, Widget_MouseClickEvent* mce){
    if(w->button.state==2 && w->button.onAction != NULL){
        w->button.onAction(w);
    }
    w->button.state=1;
}

Widget* new_ButtonWidget(const char* text){
    Widget *w = new_BaseWidget(WIDGET_BUTTON);
    w->button.text = malloc(sizeof(char) * (strlen(text)+1));
    strcpy(w->button.text, text);
    w->button.state=0;
    w->button.onAction=NULL;
    
    w->bw->onPaint=buttonWidget_onPaint;
    w->bw->onMouseEnter=buttonWidget_onMouseEnter;
    w->bw->onMouseLeave=buttonWidget_onMouseLeave;
    w->bw->onMousePress=buttonWidget_onMousePress;
    w->bw->onMouseRelease=buttonWidget_onMouseRelease;

    return w;
}

void buttonWidget_free(Widget *w){
    free(w->button.text);
    baseWidget_free(w);
}
