#include <widgets/trackbar.h>

namespace AbyssCore{
    Trackbar::Trackbar(Window* parent) : Widget(parent){
        minValue = 0;
        maxValue = 10;
        value = 0;

        style.selected = {BLUE};

        handleState = Idle;

        beginLMove = false;
        valueChanged = NULL;
    }

    int Trackbar::CalculateHandlePosition(){
        double step = CalculateHandleStep();

        int x_value = step * (value - minValue);

        return x_value;
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

    void Trackbar::Paint(Anchor anchor){
        Clear(anchor, style.background);

        int x1 = HANDLE_OFFSET;
        int y1 = rect.h / 2;
        int x2 = rect.w - HANDLE_OFFSET;
        int y2 = y1;

        aRect rect = CalculateHandleRect();

        DrawLine(anchor, aPair({x1, y1, x2, y2}), aColor({BLACK}));
        switch(handleState){
            case Idle:
                FillRect(anchor, SDL_Rect({rect.left, rect.top, TRACKBAR_WIDTH, TRACKBAR_HEIGHT}), style.background);
            break;
            case Pressed:
                FillRect(anchor, SDL_Rect({rect.left, rect.top, TRACKBAR_WIDTH, TRACKBAR_HEIGHT}), style.selected);
            break;
        }
        
        DrawRect(anchor, SDL_Rect({rect.left, rect.top, TRACKBAR_WIDTH, TRACKBAR_HEIGHT}), style.border);
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