#include <button.h>

namespace AbyssCore{
    void Button::ProcessClick(SDL_MouseButtonEvent event, Window * parent){

    }

    void Button::ProcessDrag(SDL_MouseMotionEvent event, Window * parent){

    }

    void Button::ProcessMove(SDL_MouseMotionEvent event, Window * parent){

    }

    void Button::Paint(Anchor anchor){
        DrawRect(anchor, SDL_Rect({40, 40, 50, 50}), aColor({BLACK}));
    }
}