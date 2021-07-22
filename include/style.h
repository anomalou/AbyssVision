#ifndef STYLE_H
#define STYLE_H

#include <SDL.h>
#include <colors.h>

typedef struct{
    SDL_Color background;
    SDL_Color border;
    SDL_Color shadow;
    int shadow_size;
    SDL_Color control;
    SDL_Color enabled;
    SDL_Color disabled;
    SDL_Color focus;
    SDL_Color nofocus;
    SDL_Color selected;
    SDL_Color hover;
}Style;

typedef enum{
    Idle,
    Pressed,
    Hovered
}State;

#endif