#ifndef EVENTS
#define EVENTS


typedef struct Widget_ResizeEvent {
    SDL_Point oldSize;
    SDL_Point newSize;
}Widget_ResizeEvent;

typedef struct Widget_MouseClickEvent{
    Uint8 button;
    Uint8 clicks;
    SDL_Point pos;
} Widget_MouseClickEvent;

typedef struct Widget_MouseMoveEvent{
    SDL_Point pos;
    SDL_Point rel;
} Widget_MouseMoveEvent;

#endif