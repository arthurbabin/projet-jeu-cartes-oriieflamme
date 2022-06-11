#include "Widget.h"

void widget_setSize(Widget* w, int width, int height){
    Widget_ResizeEvent wre;

    wre.oldSize.x=w->bw->width;
    wre.oldSize.y=w->bw->height;
    wre.newSize.x=width;
    wre.newSize.y=height;

    w->bw->width=width;
    w->bw->height=height;

    if(w->bw->onResize != NULL)
        w->bw->onResize(w, &wre);
}

void widget_setLocation(Widget* w, int x, int y){
    w->bw->x=x;
    w->bw->y=y;
}

void widget_add(Widget *parent, Widget *fils){
    baseWidget_add(parent->bw, fils);
}

void widget_free(Widget *w){
    switch(w->bw->type){
        case WIDGET_BASE:
            baseWidget_free(w);
            break;
        case WIDGET_BUTTON:
            buttonWidget_free(w);
            break;
        case WIDGET_TEXTEDIT:
            textEditWidget_free(w);
            break;
        case WIDGET_MENU:
            menuWidget_free(w);
            break;
    }
}