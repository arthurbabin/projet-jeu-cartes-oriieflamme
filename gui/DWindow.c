#include "DWindow.h"

DWindow* new_DWindow(const char* title, int x, int y){
    DWindow *this = malloc(sizeof(DWindow));
    if(!this) return NULL;

    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, x, y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(this->window == NULL){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return NULL;
    }
    this->painter = new_Painter(this->window);
    this->content = NULL;
    this->focus=NULL;
    return this;
}

void propagOnPaint(Widget *w, Painter *painter){
    if(w->bw->onPaint != NULL)
        w->bw->onPaint(w, painter);
    WidgetListItem *cur = w->bw->children->first;
    while(cur != NULL){
        painter->padX+=cur->val->bw->x;
        painter->padY+=cur->val->bw->y;
        propagOnPaint(cur->val, painter);
        cur = cur->next;
    }
    painter->padX -= w->bw->x;
    painter->padY -= w->bw->y;
}

Widget* propagOnMouseClick(Widget *w, Widget_MouseClickEvent* mce, int type /* 0: press, 1: release */){
    WidgetListItem *cur = w->bw->children->first;
    Widget *ret = NULL;
    while(cur != NULL){
        mce->pos.x-=cur->val->bw->x;
        mce->pos.y-=cur->val->bw->y;
        ret = propagOnMouseClick(cur->val, mce,type);
        mce->pos.x+=cur->val->bw->x;
        mce->pos.y+=cur->val->bw->y;
        if(ret != NULL) return ret;
        cur = cur->next;
    }

    if(mce->pos.x > 0 && mce->pos.y >0 && mce->pos.x <= w->bw->width && mce->pos.y <= w->bw->height){
        if(type==0 && w->bw->onMousePress != NULL){
            w->bw->onMousePress(w, mce);
        }else if(type==1 && w->bw->onMouseRelease != NULL){
            w->bw->onMouseRelease(w, mce);
        }
        return w;
    }
    return NULL;
}

Widget* propagOnMouseMove(Widget *w, Widget_MouseMoveEvent* mme){
    WidgetListItem *cur = w->bw->children->first;
    Widget *ret = NULL;
    while(cur != NULL){
        mme->pos.x-=cur->val->bw->x;
        mme->pos.y-=cur->val->bw->y;
        ret = propagOnMouseMove(cur->val, mme);
        mme->pos.x+=cur->val->bw->x;
        mme->pos.y+=cur->val->bw->y;
        if(ret != NULL) return ret;
        cur = cur->next;
    }
    
    if(mme->pos.x > 0 && mme->pos.y >0 && mme->pos.x <= w->bw->width && mme->pos.y <= w->bw->height){
        if(w->bw->onMouseEnter != NULL && !(mme->pos.x-mme->rel.x > 0 && mme->pos.y-mme->rel.y > 0 && mme->pos.x-mme->rel.x <= w->bw->width && mme->pos.y-mme->rel.y <= w->bw->height )){
            w->bw->onMouseEnter(w);
        }
        if(w->bw->onMouseMove != NULL){
            w->bw->onMouseMove(w, mme);   
            return w;
        }  
    }else if(w->bw->onMouseLeave != NULL && (mme->pos.x-mme->rel.x > 0 && mme->pos.y-mme->rel.y > 0 && mme->pos.x-mme->rel.x <= w->bw->width && mme->pos.y-mme->rel.y <= w->bw->height )){
        w->bw->onMouseLeave(w);
    }
     
    return NULL;
}

    

void DWindow_start(DWindow* this){
    SDL_Event events;
    int isOpen=1;
    Uint32 timePerFrame = 1000/60;
	Uint32 frameStart = 0;
	Uint32 elapsed = 0;
    while(isOpen){
        frameStart = SDL_GetTicks();
        while(SDL_PollEvent(&events)){
            switch(events.type){
                case SDL_QUIT:
                    isOpen=0;
                    break;
                case SDL_WINDOWEVENT:
                    if(events.window.event == SDL_WINDOWEVENT_RESIZED){
                        widget_setSize(this->content, events.window.data1, events.window.data2);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:  
                    {
                        Widget_MouseClickEvent mce;
                        mce.pos.x = events.button.x;
                        mce.pos.y = events.button.y;
                        mce.clicks = events.button.clicks;
                        mce.button=events.button.button;
                        Widget *w = propagOnMouseClick(this->content, &mce, 0);  
                        if(this->focus != NULL && this->focus->bw->onFocusChange!=NULL){
                            this->focus->bw->onFocusChange(this->focus, SDL_FALSE);
                        }
                        this->focus=w;
                        if(w != NULL && w->bw->onFocusChange!=NULL){
                            w->bw->onFocusChange(w, SDL_TRUE);
                        }
                    }        
                    break;
                case SDL_MOUSEBUTTONUP:
                    {
                        Widget_MouseClickEvent mce;
                        mce.pos.x = events.button.x;
                        mce.pos.y = events.button.y;
                        mce.clicks = events.button.clicks;
                        mce.button=events.button.button;
                        Widget *w = propagOnMouseClick(this->content, &mce, 1);
                    }
                    break;
                case SDL_MOUSEMOTION:
                    {
                        Widget_MouseMoveEvent mme;
                        mme.pos.x = events.motion.x;
                        mme.pos.y = events.motion.y;
                        mme.rel.x = events.motion.xrel;
                        mme.rel.y = events.motion.yrel;
                        Widget *w = propagOnMouseMove(this->content, &mme);
                    }
                    break;
                case SDL_TEXTINPUT:
                    {
                        if(this->focus != NULL && this->focus->bw->type==WIDGET_TEXTEDIT){
                            this->focus->textEdit.onTextInput(this->focus, events.text.text);
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    {
                        if(this->focus!=NULL && this->focus->bw->onKeyDown!=NULL){
                            this->focus->bw->onKeyDown(this->focus, &events.key);
                        }
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    {
                        if(this->focus!=NULL && this->focus->bw->onMouseWheel!=NULL){
                            SDL_Point pt = { events.wheel.x, events.wheel.y };
                            this->focus->bw->onMouseWheel(this->focus, &pt);
                        }
                    }
                    break;
            }
        }
        SDL_SetRenderDrawColor(this->painter->renderer, 0, 0, 0, 255);
        SDL_RenderClear(this->painter->renderer);
        propagOnPaint(this->content, this->painter);
        SDL_RenderPresent(this->painter->renderer);

        elapsed = SDL_GetTicks() - frameStart;
		if(elapsed < timePerFrame){
			SDL_Delay(timePerFrame - elapsed);
		}
        
    }
}

void DWindow_free(DWindow* this){
    painter_free(this->painter);
    if(this->content != NULL)
        widget_free(this->content);
    SDL_DestroyWindow(this->window);
    free(this);
}

Widget* DWindow_setContent(DWindow* parent, Widget *fils){
    Widget* res=parent->content;
    parent->content = fils;
    int width, height;
    SDL_GetWindowSize(parent->window, &width, &height);
    widget_setSize(fils, width, height);
    widget_setLocation(fils, 0,0);
    return res;
}