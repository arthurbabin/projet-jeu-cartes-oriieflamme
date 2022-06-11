#ifndef WIDGET
#define WIDGET

#include "BaseWidget.h"
#include "ButtonWidget.h"
#include "TextEditWidget.h"
#include "MenuWidget.h"
#include "GameWidget.h"

typedef struct BaseWidget BaseWidget;

typedef union Widget {
    BaseWidget *bw;
    ButtonWidget button;
    TextEditWidget textEdit;

} Widget;

void widget_setSize(Widget* w, int width, int height);
void widget_setLocation(Widget* w, int x, int y);
void widget_add(Widget *parent, Widget *fils);
void widget_free(Widget *w);


#endif