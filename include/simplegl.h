#ifndef SIMPLEGL_H
#define SIMPLEGL_H

#include <SDL.h>
#include <agl.h>


namespace AbyssCore{
    typedef struct{
        int x;
        int y;
        int w;
        int h;
    }Anchor;

    void Clear(Anchor anchor, aColor color);
    void DrawRect(Anchor anchor, SDL_Rect rect, aColor color);
    void FillRect(Anchor anchor, SDL_Rect rect, aColor color);
}

#endif