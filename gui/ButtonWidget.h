#include "Widget.h"

#ifndef WIDGET_BUTTON
#define WIDGET_BUTTON 1

#include "BaseWidget.h"
#include <string.h>
#include "Asset.h"

typedef struct BaseWidget BaseWidget;
typedef union Widget Widget;

typedef struct ButtonWidget{
    BaseWidget *bw;
    char *text;
    void (*onAction)(Widget *w);   
    int state; // 0: normal  1: hover  2:pressed
} ButtonWidget;

Widget* new_ButtonWidget(const char* text);
void buttonWidget_free(Widget *w);

#endif