#include <widgets/trackbar.h>

namespace AbyssCore{
    Trackbar::Trackbar(Window* parent) : Widget(parent){
        minValue = 0;
        maxValue = 10;
        value = 0;
        handlePosition = 0;
        smooth = 100;

        style.selected = {BLUE};

        handleState = Idle;

        beginLMove = false;
        valueChanged = NULL;
    }

    int Trackbar::CalculateHandlePosition(){
        double step = CalculateHandleStep();

        int x_value = step * (value - minValue);

        double odds = abs(handlePosition - x_value);

        if(handlePosition > x_value)
            handlePosition -= odds * Time::deltaTime / smooth;
        if(handlePosition < x_value)
            handlePosition += odds * Time::deltaTime / smooth;

        return (int)round(handlePosition);
    }

    aRect Trackbar::CalculateHandleRect(){
        aRect hrect;

        int x_value = CalculateHandlePosition();

        hrect.left = x_value + HANDLE_OFFSET - TRACKBAR_WIDTH / 2;
        hrect.right = x_value + HANDLE_OFFSET + TRACKBAR_WIDTH / 2;
        hrect.top = rect.h / 2 - TRACKBAR_HEIGHT / 2;
        hrect.bottom = rect.h / 2 + TRACKBAR_HEIGHT / 2;

        return hrect;
    }

    double Trackbar::CalculateHandleStep(){
        int length = rect.w - HANDLE_OFFSET * 2;
        int stepCount = (maxValue - minValue);
        double step = (double)length / (double)stepCount;

        return step;
    }

    bool Trackbar::HandleHit(int x, int y){
        aRect rect = CalculateHandleRect();

        if(x > rect.left && x < rect.right && y > rect.top && y < rect.bottom){
            return true;
        }

        return false;
    }

    void Trackbar::SetValue(int value){
        if(value > maxValue)
            this->value = maxValue;
        else if(value < minValue)
            this->value = minValue;
        else
            this->value = value;

        if(valueChanged != NULL){
            ActionEvent aevent = {
                parent,
                0,
                0,
                0,
                0,
                0
            };

            valueChanged(this, aevent);
        }
    }

    int Trackbar::GetValue(){
        return value;
    }

    void Trackbar::Paint(Renderer &renderer){
        aRect rect = CalculateHandleRect();

        int x = HANDLE_OFFSET;
        int y = this->rect.h / 2;
        int w = this->rect.w - 2 * HANDLE_OFFSET;
        int h = 1;

        renderer.DrawRect(SDL_Rect({x, y, w, h}), aColor({WHITE}), true, aColor({BLACK}));

        SDL_Rect sdl_rect = {rect.left, rect.top, rect.right - rect.left, rect.bottom- rect.top};

        switch(handleState){
            case Idle:
                renderer.DrawRect(sdl_rect, style.background, true, style.border);
            break;
            case Pressed:
                renderer.DrawRect(sdl_rect, style.selected, true, style.border);
            break;
        }
    }

    void Trackbar::OnMouseDown(SDL_MouseButtonEvent event){
        int x = event.x - rect.x;
        int y = event.y - rect.y;

        if(event.button == SDL_BUTTON_LEFT){
            if(HandleHit(x, y)){
                beginLMove = true;
                handleState = Pressed;
            }
        }
    }

    void Trackbar::OnMouseUp(SDL_MouseButtonEvent event){
        if(event.button == SDL_BUTTON_LEFT){
            beginLMove = false;
            handleState = Idle;
        }   
    }

    void Trackbar::OnMouseMove(SDL_MouseMotionEvent event){
        int x_mouse = event.x - rect.x - HANDLE_OFFSET;

        if(beginLMove){
            if(event.state != SDL_BUTTON_LMASK){
                beginLMove = false;
                handleState = Idle;
                return;
            }

            double step = CalculateHandleStep();

            double fnewValue = (double)x_mouse / step;
            int value = (int)round(fnewValue) + minValue;

            SetValue(value);
        }
    }

    void Trackbar::OnMouseWheel(SDL_MouseWheelEvent event, aPoint pos){
        int x = pos.x;
        int y = pos.y;

        if(WidgetHit(x, y)){
            if(event.y > 0)
                SetValue(value + 1);
            if(event.y < 0)
                SetValue(value - 1);
        }
    }
}