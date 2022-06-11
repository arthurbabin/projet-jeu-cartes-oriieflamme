#include "BaseWidget.h"

WidgetList* new_WidgetList(){
    WidgetList *vl = malloc(sizeof(WidgetList));
    vl->first=NULL;
    vl->last=NULL;
    return vl;
}
void widgetList_free(WidgetList *vl){
    WidgetListItem *cur = vl->first;
    WidgetListItem *tmp = NULL;
    while(cur != NULL){
        tmp = cur;
        cur = cur->next;
        widget_free(tmp->val);
        free(tmp);
    }
    free(vl);
}

Widget* new_BaseWidget(int type){
    Widget *w = malloc(sizeof(Widget));
    w->bw = malloc(sizeof(BaseWidget));
    w->bw->type = type;
    w->bw->children = new_WidgetList();
    w->bw->onPaint=NULL;
    w->bw->onResize=NULL;
    w->bw->onMousePress=NULL;
    w->bw->onMouseRelease=NULL;
    w->bw->onMouseMove=NULL;
    w->bw->onMouseEnter=NULL;
    w->bw->onMouseLeave=NULL;
    w->bw->onFocusChange=NULL;
    w->bw->onKeyDown=NULL;
    w->bw->onMouseWheel=NULL;
    return w;
}

void baseWidget_free(Widget *w){
    widgetList_free(w->bw->children);
    free(w->bw);
    free(w);
}

void baseWidget_add(BaseWidget *bw, Widget *w){
    WidgetListItem *wli = malloc(sizeof(WidgetListItem));
    wli->val=w;
    wli->next=NULL;

    if(bw->children->first == NULL){  
        bw->children->first = wli;
        bw->children->last = wli;
    }else{
        bw->children->last->next=wli;
        bw->children->last = wli;
    }
}