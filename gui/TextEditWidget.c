#include "TextEditWidget.h"

int cursorAnimation;
Painter *painter;

void textEditWidget_onPaint(Widget* w, Painter* p){
    painter = p;
    painter_setStrokeSize(p, 2);
    painter_setStrokeColor(p,200,200,200,255);
    painter_setFillColor(p,35,35,35,255);
    painter_drawRect(p,0, 0, w->bw->width, w->bw->height);
    SDL_Point size;
    if(painter_textSize(p, asset_font_arial18, w->textEdit.text, &size) == 0){    
        painter_drawText(p, asset_font_arial18, 7, (w->bw->height-size.y)/2, w->textEdit.text);
    }else{
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[textSize] > %s", w->textEdit.text);
    }
    if(w->textEdit.focused){
        if(cursorAnimation<30){
            SDL_Point pt1 = { 7+w->textEdit.curcorP, (w->bw->height-size.y)/2 };
            SDL_Point pt2 = { 7+w->textEdit.curcorP, (w->bw->height+size.y)/2 };
            painter_drawLine(p, &pt1, &pt2);
        }
        cursorAnimation = (cursorAnimation+1)%60;
    }
    // je ne sais pas pourquoi, mais si je ne fais pas ça, les textures n'affichent que du blanc... j'espère que c'est un bug du WSL
    SDL_Point pt1 = { 0,0};
    SDL_Point pt2 = { 10,0};
    painter_drawLine(p, &pt1, &pt2); 
}

void textEditWidget_onMouseEnter(Widget* w){
    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM));
}

void textEditWidget_onMouseLeave(Widget* w){
    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
}

void strInsert(char *dst, int dstLength, int index, const char *insert, int insertLength){
    for(int i=dstLength+1; i > index;i--){
        dst[i+insertLength]=dst[i];
    }
    for(int i = 0; i < insertLength;i++){
        dst[index+i]=insert[i];
    }
}
void textEditWidget_onTextInput(Widget* w, const char* txt){
    int l=strlen(w->textEdit.text);
    int addl=strlen(txt);
    if(l+addl < w->textEdit.maxLength){
        //strcat(w->textEdit.text,txt);
        strInsert(w->textEdit.text, l, w->textEdit.cursor, txt, addl);   
        SDL_Point size;
        if(painter_textSize(painter, asset_font_arial18, txt, &size) == 0){ 
            w->textEdit.curcorP+=size.x;
            cursorAnimation=0;
            w->textEdit.cursor++;
        }
    }
}
void textEditWidget_onkeyDown(Widget *w, SDL_KeyboardEvent *event){
    if(event->keysym.sym == SDLK_BACKSPACE && w->textEdit.cursor>0){
        int width;
        char tmp = w->textEdit.text[w->textEdit.cursor-1];
        if(painter_charWidth(painter, asset_font_arial18, tmp, &width) == 0){ 
            for(int i = w->textEdit.cursor-1; w->textEdit.text[i] != '\0';i++){
                w->textEdit.text[i] = w->textEdit.text[i+1];
            }
            w->textEdit.curcorP-=width;
            cursorAnimation=0;
            w->textEdit.cursor--;
        }
    }else if(event->keysym.sym == SDLK_LEFT && w->textEdit.cursor>0){
        int width;
        char tmp = w->textEdit.text[w->textEdit.cursor-1];
        if(painter_charWidth(painter, asset_font_arial18, tmp, &width) == 0){ 
            w->textEdit.curcorP-=width;
            cursorAnimation=0;
            w->textEdit.cursor--;
        }
    }else if(event->keysym.sym == SDLK_RIGHT && w->textEdit.cursor<strlen(w->textEdit.text)){
        int width;
        char tmp = w->textEdit.text[w->textEdit.cursor];
        if(painter_charWidth(painter, asset_font_arial18, tmp, &width) == 0){ 
            w->textEdit.curcorP+=width;
            cursorAnimation=0;
            w->textEdit.cursor++;
        }
    }
}

void textEditWidget_onFocusChange(Widget *w, SDL_bool focused){
    if(focused){
        printf("le textEdit a le focus\n");
        SDL_StartTextInput();
        cursorAnimation=0;
        w->textEdit.focused=1;
    }else{
        printf("le textEdit n'a plus le focus\n");
        SDL_StopTextInput();
        w->textEdit.focused=0;
    }
}

Widget* new_TextEditWidget(const char* text, int maxLength){
    Widget *w = new_BaseWidget(WIDGET_TEXTEDIT);
    w->textEdit.text = malloc(sizeof(char) * maxLength);
    memset(w->textEdit.text,0,maxLength);
    strcpy(w->textEdit.text, text);
    w->textEdit.maxLength=maxLength;   
    w->textEdit.cursor=strlen(text);
    w->textEdit.curcorP=w->textEdit.cursor*8;
    w->textEdit.focused=0;
    
    w->bw->onPaint=textEditWidget_onPaint;
    w->bw->onMouseEnter= textEditWidget_onMouseEnter;
    w->bw->onMouseLeave= textEditWidget_onMouseLeave;
    w->bw->onFocusChange=textEditWidget_onFocusChange;
    w->bw->onKeyDown=textEditWidget_onkeyDown;
    w->textEdit.onTextInput=textEditWidget_onTextInput;
    
    return w;
}
void textEditWidget_free(Widget *w){
    free(w->textEdit.text);
    baseWidget_free(w);
}