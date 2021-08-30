#include <widget.h>

namespace MediumCore{
    Widget::Widget(Window* parent){
        name = "\r";
        style = Style{{LIGHT_GRAY}, {GRAY}, {WHITE}, 0, {WHITE}, {BLACK}, {GRAY}, {WHITE}, {GRAY}, {GRAY}, {WHITE}};
        this->parent = parent;
        isVisible = true;
        isDisabled = false;
    }

    string Widget::GetName(){
        return name;
    }

    SDL_Rect Widget::GetRect(){
        return rect;
    }

    bool Widget::IsVisible(){
        return isVisible;
    }

    bool Widget::IsDisabled(){
        return isDisabled;
    }

    void Widget::SetName(string name){
        this->name = name;
    }

    void Widget::SetPos(int x, int y){
        SetRect(SDL_Rect({x, y, rect.w, rect.h}));
    }

    void Widget::SetSize(int w, int h){
        SetRect(SDL_Rect({rect.x, rect.y, w, h}));
    }

    void Widget::SetRect(SDL_Rect rect){
        this->rect = rect;
    }

    void Widget::SetVisible(bool v){
        isVisible = v;
    }

    void Widget::SetDisable(bool d){
        isDisabled = d;
    }

    bool Widget::WidgetHit(int x, int y){
        int left = rect.x;
        int right = rect.x + rect.w;
        int top = rect.y;
        int bottom = rect.y + rect.h;

        if(x > left && x < right && y > top && y < bottom){
            return true;
        }

        return false;
    }

    void Widget::OnKeyPressed(SDL_KeyboardEvent event){

    }

    void Widget::OnKeyReleased(SDL_KeyboardEvent event){

    }

    void Widget::OnMouseDown(SDL_MouseButtonEvent event){

    }

    void Widget::OnMouseUp(SDL_MouseButtonEvent event){

    }

    void Widget::OnMouseMove(SDL_MouseMotionEvent event){

    }

    void Widget::OnMouseWheel(SDL_MouseWheelEvent event, aPoint pos){

    }
}