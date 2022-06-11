#ifndef WIDGET_BASE
#define WIDGET_BASE 0

#include <stdio.h>
#include <stdlib.h>
#include "Widget.h"
#include "Painter.h"
#include "Events.h"

typedef union Widget Widget;

typedef struct WidgetListItem {
    Widget *val;
    struct WidgetListItem *next;
} WidgetListItem;

typedef struct WidgetList {
    WidgetListItem *first;
    WidgetListItem *last;
} WidgetList;

typedef struct BaseWidget {
    int type;
    int x,y;
    int width, height;
    WidgetList *children;

    void (*onPaint)(Widget*, Painter*);
    void (*onResize)(Widget*, Widget_ResizeEvent*);
    void (*onMousePress)(Widget*, Widget_MouseClickEvent*);
    void (*onMouseRelease)(Widget*, Widget_MouseClickEvent*);
    void (*onMouseMove)(Widget*, Widget_MouseMoveEvent*);
    void (*onMouseEnter)(Widget*);
    void (*onMouseLeave)(Widget*);
    void (*onFocusChange)(Widget *w, SDL_bool);
    void (*onKeyDown)(Widget*, SDL_KeyboardEvent *);
    void (*onMouseWheel)(Widget*, SDL_Point*);
} BaseWidget;

Widget* new_BaseWidget(int type);
void baseWidget_free(Widget *w);
void baseWidget_add(BaseWidget *bw, Widget *w);


#endif