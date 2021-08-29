#include <window.h>

namespace MediumCore{
    Window::Window(){
        name = "\r";
        title = "\r";

        widgetPull = vector<Widget*>();

        rect = SDL_Rect({0, 0, 100, 100});
        style = Style{{WHITE}, {BLACK}, {OPAGUE_GRAY}, 5, {WHITE}, {BLACK}, {GRAY}, {LIGHT_GRAY}, {GRAY}, {WHITE}, {WHITE}};

        canMinimaze = true;
        canClose = true;
        canResize = true;
        canMove = true;

        isVisible = true;
        isMinimized = false;
        isFull = true;

        beginLMove = false;
        beginRMove = false;
        beginLClick = false;
        beginRClick = false;
        beginLClose = false;
        beginLMinimize = false;
        beginLResize = false;

        needDestroy = false;

        focusWidget = NULL;

        CalculateControlHitBox();

        
    }

    string Window::GetName(){
        return name;
    }

    string Window::GetTitle(){
        return title;
    }

    SDL_Rect Window::GetRect(){
        return rect;
    }

    bool Window::IsVisible(){
        return isVisible;
    }

    bool Window::IsMinimized(){
        return isMinimized;
    }

    bool Window::IsFull(){
        return isFull;
    }

    bool Window::CanMinimize(){
        return canMinimaze;
    }

    bool Window::CanClose(){
        return canClose;
    }

    bool Window::CanResize(){
        return canResize;
    }

    bool Window::CanMoving(){
        return canMove;
    }

    SDL_Rect Window::GetCloseHitBox(){
        return closeHitBox;
    }

    SDL_Rect Window::GetMinimizeHitBox(){
        return minimizeHitBox;
    }

    SDL_Rect Window::GetResizeHitBox(){
        return resizeHitBox;
    }

    bool Window::NeedDestroy(){
        return needDestroy;
    }

    void Window::SetName(string name){
        this->name = name;
    }

    void Window::SetTitle(string title){
        this->title = title;
    }

    void Window::SetPos(int x, int y){
        SetRect(SDL_Rect({x, y, rect.w, rect.h}));
    }

    void Window::SetSize(int w, int h){
        if(w < MIN_WIDTH)
            w = MIN_WIDTH;
        if(h < MIN_HEIGHT)
            h = MIN_HEIGHT;
        SetRect(SDL_Rect({rect.x, rect.y, w, h}));
    }

    void Window::SetRect(SDL_Rect rect){
        this->rect = rect;
        CalculateControlHitBox();
    }

    void Window::SetVisible(bool v){
        isVisible = v;
    }

    void Window::SetMinimize(bool m){
        isMinimized = m;
    }

    void Window::SetFull(bool f){
        isFull = f;
    }

    void Window::AllowMinimize(bool b){
        canMinimaze = b;
    }

    void Window::AllowClose(bool b){
        canClose = b;
    }

    void Window::AllowResize(bool b){
        canResize = b;
    }

    void Window::AllowMoving(bool m){
        canMove = m;
    }

    void Window::CalculateControlHitBox(){
        closeHitBox = {rect.w - CBUTTON_WIDTH, 0, CBUTTON_WIDTH, HEADER_HEIGHT};
        minimizeHitBox = {rect.w - 2 * CBUTTON_WIDTH + 1, 0, CBUTTON_WIDTH, HEADER_HEIGHT};
        resizeHitBox = {rect.w - CBUTTON_WIDTH, rect.h + HEADER_HEIGHT - CBUTTON_WIDTH, CBUTTON_WIDTH, CBUTTON_WIDTH};
    }

    void Window::OnKeyPressed(SDL_KeyboardEvent event){
        for(Widget* w : widgetPull){
            w->OnKeyPressed(event);
        }
    }

    void Window::OnKeyReleased(SDL_KeyboardEvent event){
        for(Widget* w : widgetPull){
            w->OnKeyReleased(event);
        }
    }

    void Window::OnMouseDown(SDL_MouseButtonEvent event){
        int x = event.x;
        int y = event.y;

        if(WindowHit(x, y)){
            event.x -= rect.x;

            if(isFull)
                event.y -= (rect.y + HEADER_HEIGHT);
            else
                event.y -= rect.y;

            for(Widget* w : widgetPull){
                if(!w->IsDisabled())
                    w->OnMouseDown(event);
            }

            if(event.button == SDL_BUTTON_LEFT){
                if(CloseHit(x, y) && canClose)
                    beginLClose = true;
                if(MinimizeHit(x, y) && canMinimaze)
                    beginLMinimize = true;
                if(ResizeHit(x, y) && canResize)
                    beginLResize = true;

                beginLClick = true;
            }
            if(event.button == SDL_BUTTON_RIGHT)
                beginRClick = true;
        }

        if(HeaderHit(x, y) && canMove){
            if(event.button == SDL_BUTTON_LEFT)
                beginLMove = true;
            if(event.button == SDL_BUTTON_RIGHT)
                beginRMove = true;
        }
    }

    void Window::OnMouseUp(SDL_MouseButtonEvent event){
        int x = event.x;
        int y = event.y;

        if(WindowHit(x, y)){
            event.x -= rect.x;
            
            if(isFull)
                event.y -= (rect.y + HEADER_HEIGHT);
            else
                event.y -= rect.y;

            for(Widget* w : widgetPull){
                if(!w->IsDisabled())
                    w->OnMouseUp(event);
            }

            if(event.button == SDL_BUTTON_LEFT){
                if(beginLClose){
                    if(CloseHit(x, y))
                        needDestroy = true;
                }

                if(beginLMinimize){
                    if(MinimizeHit(x, y))
                        isMinimized = !isMinimized;
                }
                beginLClick = false;
            }
            if(event.button == SDL_BUTTON_RIGHT)
                beginRClick = false;
        }

        if(event.button == SDL_BUTTON_LEFT){
            beginLClose = false;
            beginLMinimize = false;
            beginLResize = false;
            beginLMove = false;
        }
        if(event.button == SDL_BUTTON_RIGHT)
            beginRMove = false;
    }

    void Window::OnMouseMove(SDL_MouseMotionEvent event){
        int x = event.x;
        int y = event.y;
        int xrel = event.xrel;
        int yrel = event.yrel;

        if(beginLMove || beginRMove){
            SDL_Point pos;

            pos.x = rect.x + xrel;

            if(x < rect.x)
                pos.x = x - HEADER_HEIGHT / 2;
            if(x > (rect.x + rect.w))
                pos.x = x - rect.w + HEADER_HEIGHT / 2 + CBUTTON_WIDTH * 2;
            if(y < rect.y || y > rect.y + HEADER_HEIGHT)
                pos.y = y - HEADER_HEIGHT / 2;
            else
                pos.y = rect.y + yrel;

            if(pos.y < 0)
                pos.y = 0;
                
            SetPos(pos.x, pos.y);
        }

        if(beginLResize){
            SetSize(rect.w + (x - rect.w - rect.x) + HEADER_HEIGHT / 2, rect.h + (y - rect.h - rect.y - HEADER_HEIGHT / 2));
        }

        if(WindowHit(x, y)){
            event.x -= rect.x;
            
            if(isFull)
                event.y -= (rect.y + HEADER_HEIGHT);
            else
                event.y -= rect.y;

            for(Widget* w : widgetPull){
                if(!w->IsDisabled())
                    w->OnMouseMove(event);
            }
        }
    }

    void Window::OnMouseWheel(SDL_MouseWheelEvent event, aPoint pos){
        int x = pos.x;
        int y = pos.y;

        if(WindowHit(x, y)){
            pos.x -= rect.x;
            
            if(isFull)
                pos.y -= (rect.y + HEADER_HEIGHT);
            else
                pos.y -= rect.y;

            for(Widget* w : widgetPull){
                if(!w->IsDisabled())
                    w->OnMouseWheel(event, pos);
            }
        }
    }

    bool Window::WindowHit(int x, int y){
        int left = rect.x;
        int right = rect.x + rect.w;
        int top = rect.y;
        int bottom = rect.y + rect.h + HEADER_HEIGHT;

        if(isMinimized){
            if(isFull)
                bottom = rect.y + HEADER_HEIGHT;
            else
                bottom = rect.y;
        }else{
            if(!isFull)
                bottom = rect.y + rect.h;
        }

        if(x > left && x < right && y > top && y < bottom)
            return true;

        return false;
    }

    bool Window::HeaderHit(int x, int y){
        int left = rect.x;
        int right = rect.x + rect.w - CBUTTON_WIDTH * 2;
        int top = rect.y;
        int bottom = rect.y + HEADER_HEIGHT;

        if(!isFull)
            bottom = rect.y;

        if(x > left && x < right && y > top && y < bottom)
            return true;

        return false;
    }

    void Window::Paint(Renderer &renderer){
        //TODO: default paint
        
    }

    vector<Widget*> Window::GetPull(){
        return vector<Widget*>(widgetPull);
    }

    bool Window::AssignWidget(Widget* w, string byName){
        if(w == nullptr)
            return false;

        for(Widget * w : widgetPull){
            if(strcmp(w->GetName().c_str(), byName.c_str()) == 0)
                return false;
        }

        w->SetName(byName);
        widgetPull.push_back(w);

        return true;
    }

    bool Window::DestroyWidget(Widget* w){
        for(size_t i = 0; i < widgetPull.size(); i++){
            if(widgetPull[i] == w){
                widgetPull.erase(widgetPull.begin() + i);
                return true;
            }
        }

        return false;
    }

    Widget* Window::Find(string byName){
        for(Widget* w : widgetPull){
            if(strcmp(byName.c_str(), w->GetName().c_str()) == 0){
                return w;
            }
        }

        return nullptr;
    }

    bool Window::InHeader(int x, int y){
        SDL_Rect rect = GetRect();

        if(x >= rect.x && x <= (rect.x + rect.w) && y >= rect.y && y <= (rect.y + HEADER_HEIGHT))
            return true;
        return false;
    }

    bool Window::InBody(int x, int y){
        SDL_Rect rect = GetRect();

        if(x >= rect.x && x <= (rect.x + rect.w) && y >= (rect.y + HEADER_HEIGHT) && y <= (rect.y + rect.h + HEADER_HEIGHT))
            return true;
        return false;
    }

    bool Window::InWidget(Widget* w, int x, int y){
        SDL_Rect rect = w->GetRect();

        if(IsFull())
            rect.y += HEADER_HEIGHT - 1;

        if(x >= rect.x && x <= (rect.x + rect.w) && y >= rect.y && y <= (rect.y + rect.h)){
            return true;
        }

        return false;
    }

    bool Window::CloseHit(int x, int y){
        SDL_Rect currentFRect = GetRect();
        SDL_Rect closeHitBox = GetCloseHitBox();

        SDL_Rect crossRect = {currentFRect.x + closeHitBox.x, currentFRect.y + closeHitBox.y, closeHitBox.w, closeHitBox.h};
    
        if(x >= crossRect.x && x <= (crossRect.x + crossRect.w) && y >= crossRect.y && y <= (crossRect.y + crossRect.h))
            return true;

        return false;
    }

    bool Window::MinimizeHit(int x, int y){
        SDL_Rect currentFRect = GetRect();
        SDL_Rect minimazeHitBox = GetMinimizeHitBox();

        SDL_Rect minRect = {currentFRect.x + minimazeHitBox.x, currentFRect.y + minimazeHitBox.y, minimazeHitBox.w, minimazeHitBox.h};
        if(x >= minRect.x && x <= (minRect.x + minRect.w) && y >= minRect.y && y <= (minRect.y + minRect.h))
            return true;
        
        return false;
    }

    bool Window::ResizeHit(int x, int y){
        SDL_Rect currentFRect = GetRect();
        SDL_Rect resizeHitBox = GetResizeHitBox();

        SDL_Rect resRect = {currentFRect.x + resizeHitBox.x, currentFRect.y + resizeHitBox.y, resizeHitBox.w, resizeHitBox.h};
        if(x >= resRect.x && x <= (resRect.x + resRect.w) && y >= resRect.y && y <= (resRect.y + resRect.h))
            return true;
        
        return false;
    }
}