#include <simplegl.h>

namespace AbyssCore{
    void Clear(Anchor anchor, aColor color){
        FillRect(anchor, SDL_Rect({0, 0, anchor.w, anchor.h}), color);
    }

    void DrawRect(Anchor anchor, SDL_Rect rect, aColor color){
        SDL_Rect globRect = {anchor.x + rect.x, anchor.y + rect.y, rect.w, rect.h};
        GLDraw2DRect(globRect, color);
    }

    void FillRect(Anchor anchor, SDL_Rect rect, aColor color){
        SDL_Rect globRect = {anchor.x + rect.x, anchor.y + rect.y, rect.w, rect.h};
        GLFill2DRect(globRect, color);
    }
}