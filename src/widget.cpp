#include <widget.h>

namespace AbyssCore{
    Widget::Widget(Window* parent){
        name = new AString();
        style = Style{{LIGHT_GRAY}, {GRAY}, {WHITE}, 0, {WHITE}, {BLACK}, {GRAY}, {WHITE}, {GRAY}, {GRAY}, {WHITE}};
        this->parent = parent;
        isVisible = true;
        isDisabled = false;
    }

    AString* Widget::GetName(){
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

    void Widget::SetName(AString* name){
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
}