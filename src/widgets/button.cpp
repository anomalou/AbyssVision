#include <widgets/button.h>

namespace AbyssCore{
    Button::Button(Window* parent) : Widget(parent){
        beginClick = false;
        state = Idle;
    }

    void Button::Paint(Renderer &renderer){
        SDL_Rect rect = {0, 0, this->rect.w, this->rect.h};
        switch(state){
            case Idle:
                renderer.DrawRect(rect, style.background, true, style.border);
            break;
            case Pressed:
                renderer.DrawRect(rect, style.selected, true, style.border);
            break;
            case Hovered:
                renderer.DrawRect(rect, style.hover, true, style.border);
            break;
        }
    }

    void Button::OnMouseDown(SDL_MouseButtonEvent event){
        int x = event.x;
        int y = event.y;

        if(WidgetHit(x, y)){
            if(event.button == SDL_BUTTON_LEFT){
                beginClick = true;
                state = Pressed;
            }
        }
    }

    void Button::OnMouseUp(SDL_MouseButtonEvent event){
        int x = event.x;
        int y = event.y;

        if(event.button == SDL_BUTTON_LEFT){
            if(beginClick){
                if(WidgetHit(x, y)){
                    if(clickAction != NULL){
                        ActionEvent aevent = {
                            parent,
                            x,
                            y,
                            0,
                            0,
                            event.button
                        };

                        clickAction(this, aevent);
                    }
                }

                beginClick = false;
                state = Idle;
            }
        }
    }

    void Button::OnMouseMove(SDL_MouseMotionEvent event){
        int x = event.x;
        int y = event.y;

        if(!beginClick){
            if(WidgetHit(x, y)){
                state = Hovered;
            }else{
                state = Idle;
            }
        }
    }

    void Button::OnMouseWheel(SDL_MouseWheelEvent event, aPoint pos){

    }
}