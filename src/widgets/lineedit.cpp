#include <widgets/lineedit.h>

namespace MediumCore{
    LineEdit::LineEdit(Window* parent) : Widget(parent){
        text = "";
        scale = 0.7;
        startPointText = 0;
        startPointCursore = 0;
        textPosition = 0;
        cursorePosition = 0;

        smooth = 100;
        cursoreOffset = 5;

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
                // printf("Key: %s\n", SDL_GetKeyName(event.keysym.sym));
                char c = Resources::ConvertKeyCode(event.keysym.sym);
                if(event.keysym.mod == 0)
                    text.append(1, c);
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
        switch(state){
            case Idle:
                renderer.DrawRect(SDL_Rect({0, 0, rect.w, rect.h}), aColor({WHITE}), true, style.nofocus);
            break;
            case Pressed:
                renderer.DrawRect(SDL_Rect({0, 0, rect.w, rect.h}), aColor({WHITE}), true, style.focus);
            break;
        }

        int maxHeight = Resources::GetCurrentFont().height * scale;

        int strWidth = Resources::CountStringWidth(text, Resources::GetCurrentFont(), scale);

        startPointText = rect.w - strWidth - text.length() + 1;
        startPointCursore = rect.w - strWidth - cursoreOffset;

        // printf("strW: %d, rect.w: %d\n", strWidth, rect.w);

        if(startPointText > 0)
            startPointText = 0;

        if(startPointCursore > 0)
            startPointCursore = 0;

        double todds = abs(textPosition - startPointText);

        // printf("sp: %d, odds: %f\n", startPoint, odds);

        if(textPosition > startPointText)
            textPosition -= todds * Time::deltaTime / smooth;
        if(textPosition < startPointText)
            textPosition += todds * Time::deltaTime / smooth;

        renderer.DrawTextLine(aPoint({(int)round(textPosition), rect.h / 2 + maxHeight / 2}), text, 0, scale);

        if(typingMode){
            double codds = abs(cursorePosition - (strWidth + startPointCursore));

            if(cursorePosition < strWidth + startPointCursore)
                cursorePosition += codds * Time::deltaTime / smooth;
            if(cursorePosition > strWidth + startPointCursore)
                cursorePosition -= codds * Time::deltaTime / smooth;

            renderer.DrawRect(SDL_Rect({(int)round(cursorePosition), 0, 1, rect.h}), aColor({BLACK}), false);
        }

    }
}