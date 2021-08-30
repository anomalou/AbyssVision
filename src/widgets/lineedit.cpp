#include <widgets/lineedit.h>

namespace MediumCore{
    LineEdit::LineEdit(Window* parent) : Widget(parent){
        text = "";

        state = Idle;

        style.focus = aColor({BLACK});
        style.nofocus = aColor({GRAY});
    }
   
    void LineEdit::OnKeyPressed(SDL_KeyboardEvent event){
        
    }

    void LineEdit::OnKeyReleased(SDL_KeyboardEvent event){

    }

    void LineEdit::OnMouseDown(SDL_MouseButtonEvent event){
        if(event.button == SDL_BUTTON_LEFT || event.button == SDL_BUTTON_RIGHT){
            int x = event.x;
            int y = event.y;

            if(WidgetHit(x, y))
                state = Pressed;
            else
                state = Idle;
        }
    }

    void LineEdit::OnMouseUp(SDL_MouseButtonEvent event){

    }

    void LineEdit::Paint(Renderer &renderer){
        int width = rect.w - 2 * OFFSET;
        int height = rect.h - 2 * OFFSET;

        switch(state){
            case Idle:
                renderer.DrawRect(SDL_Rect({OFFSET, OFFSET, width, height}), aColor({WHITE}), true, style.nofocus);
            break;
            case Pressed:
                renderer.DrawRect(SDL_Rect({OFFSET, OFFSET, width, height}), aColor({WHITE}), true, style.focus);
            break;
        }
    }
}