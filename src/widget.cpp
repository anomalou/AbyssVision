#include <widget.h>

namespace AbyssCore{
    Widget::Widget(){
        name = new AString();
        color = SDL_Color({GRAY});
        isVisible = true;

        action = nullptr;
    }

    AString* Widget::GetName(){
        return name;
    }

    SDL_Rect Widget::GetRect(){
        return rect;
    }

    SDL_Color Widget::GetColor(){
        return color;
    }

    bool Widget::IsVisible(){
        return isVisible;
    }

    void Widget::DoAction(void * ptr){
        if(action != nullptr)
            action(ptr);
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

    void Widget::SetColor(SDL_Color color){
        this->color = color;
    }

    void Widget::SetVisible(bool v){
        isVisible = v;
    }

    void Widget::SetAction(Action action){
        this->action = action;
    }

}