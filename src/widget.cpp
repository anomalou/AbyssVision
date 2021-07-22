#include <widget.h>

namespace AbyssCore{
    Widget::Widget(){
        name = new AString();
        style = Style{{LIGHT_GRAY}, {GRAY}, {WHITE}, 0, {WHITE}, {BLACK}, {GRAY}, {WHITE}, {GRAY}, {GRAY}, {WHITE}};
        isVisible = true;

        state = Idle;

        click = nullptr;
        drag = nullptr;
        move = nullptr;
    }

    AString* Widget::GetName(){
        return name;
    }

    SDL_Rect Widget::GetRect(){
        return rect;
    }

    Style Widget::GetStyle(){
        return style;
    }

    State Widget::GetState(){
        return state;
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

    void Widget::SetStyle(Style style){
        this->style = style;
    }

    void Widget::SetState(State state){
        this->state = state;
    }

    void Widget::SetVisible(bool v){
        isVisible = v;
    }

    void Widget::SetDisable(bool d){
        isDisabled = d;
    }

    void Widget::SetAction(ActionType type, Action action){
        switch(type){
            case Click:
                click = action;
            break;
            case Drag:
                drag = action;
            break;
            case Move:
                move = action;
            break;
        }
    }

    void Widget::ProcessClick(SDL_MouseButtonEvent event, void * parent){
        if(click != nullptr)
            click(this, parent);
    }

    void Widget::ProcessDrag(SDL_MouseMotionEvent event, void * parent){
        if(drag != nullptr)
            drag(this, parent);
    }

    void Widget::ProcessMove(SDL_MouseMotionEvent event, void * parent){
        if(move != nullptr)
            move(this, parent);
    }

    void Widget::Paint(SDL_Renderer* render){
        if(state == Idle)
            SDL_SetRenderDrawColor(render, style.background.r, style.background.g, style.background.b, style.background.a);
        else if(state == Pressed)
            SDL_SetRenderDrawColor(render, style.selected.r, style.selected.g, style.selected.b, style.selected.a);
        else if(state == Hovered)
            SDL_SetRenderDrawColor(render, style.hover.r, style.hover.g, style.hover.b, style.hover.a);
        
        SDL_RenderClear(render);
    }
}