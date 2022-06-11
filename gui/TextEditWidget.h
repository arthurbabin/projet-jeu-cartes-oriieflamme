#include "Widget.h"

#ifndef WIDGET_TEXTEDIT
#define WIDGET_TEXTEDIT 2

#include "BaseWidget.h"

typedef struct BaseWidget BaseWidget;
typedef union Widget Widget;

typedef struct TextEditWidget {
    BaseWidget *bw;
    char *text;
    int maxLength;
    void (*onTextInput)(Widget*, const char*);
    unsigned int cursor, curcorP;  //cursor: position du curseur par rapport au text   cursorP: position du curseur en pixel
    int focused;
} TextEditWidget;

Widget* new_TextEditWidget(const char* text, int maxLength);
void textEditWidget_free(Widget *w);

#endif