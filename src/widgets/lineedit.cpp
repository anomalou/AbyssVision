#include <widgets/lineedit.h>

namespace MediumCore{
    LineEdit::LineEdit(Window* parent) : Widget(parent){
        text = "";

        typingMode = false;
        state = Idle;

        style.focus = aColor({BLACK});
        style.nofocus = aColor({GRAY});
    }
   
    void LineEdit::OnKeyPressed(SDL_KeyboardEvent event){
        if(typingMode){
            if(event.keysym.sym == SDLK_BACKSPACE){
                if(text.length() > 0)
                    text.erase(text.begin() + text.length() - 1, text.end());
            }else{
                const char* c = SDL_GetKeyName(event.keysym.sym);
                size_t length = strlen(c);
                if(length <= 1)
                    text.append(c);
            }
        }
    }

    void LineEdit::OnKeyReleased(SDL_KeyboardEvent event){

    }

    void LineEdit::OnMouseDown(SDL_MouseButtonEvent event){
        if(event.button == SDL_BUTTON_LEFT || event.button == SDL_BUTTON_RIGHT){
            int x = event.x;
            int y = event.y;

            if(WidgetHit(x, y)){
                state = Pressed;
                typingMode = true;
            }else{
                state = Idle;
                typingMode = false;
            }
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

        renderer.DrawTextLine(aPoint({OFFSET * 2, height}), text, 0, 0.7, width);
    }
}