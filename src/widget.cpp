#include <widget.h>

namespace AbyssCore{
    Widget::Widget(){
        name = new AString();
        style = Style{{LIGHT_GRAY}, {GRAY}, {WHITE}, 0, {WHITE}, {BLACK}, {GRAY}, {WHITE}, {GRAY}, {GRAY}, {WHITE}};
        isVisible = true;

        state = Idle;

        actions = map<ActionType, Action>();
    }

    AString* Widget::GetName(){
        return name;
    }

    SDL_Rect Widget::GetRect(){
        return rect;
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
        if(actions.count(type) == 0){
            actions.insert(make_pair(type, action));
        }
    }

    void Widget::ProcessClick(SDL_MouseButtonEvent event, Window * parent){
        if(actions.count(Click) != 0){
            ActionEvent aevent = {
                parent,
                event.x,
                event.y,
                0,
                0,
                event.button
            };
            actions[Click](this, aevent);
        }
    }

    void Widget::ProcessDrag(SDL_MouseMotionEvent event, Window * parent){
        if(actions.count(Drag) != 0){
            ActionEvent aevent = {
                parent,
                event.x,
                event.y,
                event.xrel,
                event.yrel,
                event.state
            };
            actions[Drag](this, aevent);
        }
    }

    void Widget::ProcessMove(SDL_MouseMotionEvent event, Window * parent){
        if(actions.count(Move) != 0){
            ActionEvent aevent = {
                parent,
                event.x,
                event.y,
                event.xrel,
                event.yrel,
                event.state
            };
            actions[Move](this, aevent);
        }
    }

    void Widget::Paint(SDL_Renderer* render){
        if(state == Idle)
            SDL_SetRenderDrawColor(render, style.background.r, style.background.g, style.background.b, style.background.a);
        else if(state == Pressed)
            SDL_SetRenderDrawColor(render, style.selected.r, style.selected.g, style.selected.b, style.selected.a);
        else if(state == Hovered)
            SDL_SetRenderDrawColor(render, style.hover.r, style.hover.g, style.hover.b, style.hover.a);
        
        SDL_RenderClear(render);

        SDL_SetRenderDrawColor(render, style.border.r, style.border.g, style.border.b, style.border.a);
        SDL_Rect rect = this->rect;
        rect.x = 0;
        rect.y = 0;

        SDL_RenderDrawRect(render, &rect);
    }
}