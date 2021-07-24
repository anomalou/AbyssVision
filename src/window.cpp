#include <window.h>

namespace AbyssCore{
    Window::Window(){
        name = new AString();

        widgetPull = vector<Widget*>();

        rect = SDL_Rect({0, 0, 100, 100});
        style = Style{{WHITE}, {BLACK}, {OPAGUE_GRAY}, 5, {WHITE}, {BLACK}, {GRAY}, {WHITE}, {GRAY}, {WHITE}, {WHITE}};

        canMinimaze = true;
        canClose = true;
        canResize = false;
        canMove = true;

        isVisible = true;
        isMinimazied = false;
        isFull = true;

        needDestroy = false;

        beginGClick = false;
        beginGDrag = false;
        beginGResize = false;

        beginClick = false;
        beginGDrag = false;

        CalculateControlHitBox();

        
    }

    int Window::GetID(){
        return id;
    }

    AString* Window::GetName(){
        return name;
    }

    SDL_Rect Window::GetRect(){
        return rect;
    }

    bool Window::IsVisible(){
        return isVisible;
    }

    bool Window::IsMinimazed(){
        return isMinimazied;
    }

    bool Window::IsFull(){
        return isFull;
    }

    bool Window::CanMinimaze(){
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

    SDL_Rect Window::GetMinimazeHitBox(){
        return minimazeHitBox;
    }

    SDL_Rect Window::GetResizeHitBox(){
        return resizeHitBox;
    }

    bool Window::NeedDestroy(){
        return needDestroy;
    }

    void Window::SetID(int id){
        this->id = id;
    }

    void Window::SetName(AString* name){
        this->name = name;
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

    void Window::SetMinimaze(bool m){
        isMinimazied = m;
    }

    void Window::SetFull(bool f){
        isFull = f;
    }

    void Window::AllowMinimaze(bool b){
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
        minimazeHitBox = {rect.w - 2 * CBUTTON_WIDTH + 1, 0, CBUTTON_WIDTH, HEADER_HEIGHT};
        resizeHitBox = {rect.w - CBUTTON_WIDTH, rect.h + HEADER_HEIGHT - CBUTTON_WIDTH, CBUTTON_WIDTH, CBUTTON_WIDTH};
    }

    void Window::ProcessGlobalClick(SDL_MouseButtonEvent event){
        int x = event.x;
        int y = event.y;

        //mouse button down

        if(InHeader(x, y)){
            ProcessGlobalHeaderClick(event);
        }else if(InBody(x, y)){
            ProcessGlobalBodyClick(event);
        }

        if(event.type == SDL_MOUSEBUTTONUP && event.button == SDL_BUTTON_LEFT){
            beginGClick = false;
            beginGDrag = false;
            beginGResize = false;
        }
    }

    void Window::ProcessGlobalHeaderClick(SDL_MouseButtonEvent event){
        int x = event.x;
        int y = event.y;

        if(event.type == SDL_MOUSEBUTTONDOWN && event.button == SDL_BUTTON_LEFT && IsFull() && CanMoving())
            beginGDrag = true;

        if(CloseHit(x, y) && CanClose() && IsFull()){
            if(event.type == SDL_MOUSEBUTTONDOWN)
                beginGClick = true;
            if(beginGClick && event.type == SDL_MOUSEBUTTONUP)
                CloseAction();
        }
        if(MinimazeHit(x, y) && CanMinimaze() && IsFull()){
            if(event.type == SDL_MOUSEBUTTONDOWN)
                beginGClick = true;
            if(beginGClick && event.type == SDL_MOUSEBUTTONUP)
                MinimazeAction();
        }
    }

    void Window::ProcessGlobalBodyClick(SDL_MouseButtonEvent event){
        int x = event.x;
        int y = event.y;

        if(ResizeHit(x, y) && !IsMinimazed() && CanResize() && IsFull() && event.type == SDL_MOUSEBUTTONDOWN && event.button == SDL_BUTTON_LEFT)
            beginGResize = true;
    }

    void Window::ProcessGlobalMove(SDL_MouseMotionEvent event){
        
    }

    void Window::ProcessGlobalDrag(SDL_MouseMotionEvent event){
        int x = event.x;
        int y = event.y;
        int xrel = event.xrel;
        int yrel = event.yrel;

        SDL_Rect rect = GetRect();

        if(beginGDrag){
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

        if(beginGResize)
            ResizeAction(rect.w + (x - rect.w - rect.x) + HEADER_HEIGHT / 2, rect.h + (y - rect.h - rect.y - HEADER_HEIGHT / 2));
    }

    void Window::ProcessClick(SDL_MouseButtonEvent event){
        int x = event.x;
        int y = event.y;

        int header_offset = HEADER_HEIGHT;

        if(!IsFull())
            header_offset = 0;

        if(y >= header_offset)
            ProcessBodyClick(event);
        else if(y < header_offset)
            ProcessHeaderClick(event);

        if(event.type == SDL_MOUSEBUTTONUP && event.button == SDL_BUTTON_LEFT){
            beginClick = false;
            beginDrag = false;
        }
    }

    void Window::ProcessHeaderClick(SDL_MouseButtonEvent event){
        
    }

    void Window::ProcessBodyClick(SDL_MouseButtonEvent event){
        int x = event.x;
        int y = event.y;

        for(Widget* w : widgetPull){
            if(w->IsVisible() && !w->IsDisabled()){
                if(event.button == SDL_BUTTON_LEFT){

                    if(w->GetState() == Pressed){
                        w->SetState(Idle);
                    }

                    if(InWidget(w, x, y)){
                        if(event.type == SDL_MOUSEBUTTONDOWN){
                            beginClick = true;
                            w->SetState(Pressed);
                        }
                        if(beginClick && event.type == SDL_MOUSEBUTTONUP){
                            w->SetState(Hovered);
                            w->ProcessClick(event, this);
                        }
                    }
                }
            }
        }
    }

    void Window::ProcessMove(SDL_MouseMotionEvent event){
        int x = event.x;
        int y = event.y;

        for(Widget* w : widgetPull){
            if(w->IsVisible() && !w->IsDisabled()){
                if(w->GetState() == Hovered)
                    w->SetState(Idle);

                if(w->GetState() == Idle){
                    if(InWidget(w, x, y)){
                        w->SetState(Hovered);
                        w->ProcessMove(event, this);
                    }
                }
            }
        }
    }

    void Window::ProcessDrag(SDL_MouseMotionEvent event){
        int x = event.x;
        int y = event.y;

        for(Widget* w : widgetPull){
            if(w->IsVisible() && !w->IsDisabled()){
                if(InWidget(w, x, y)){
                    w->ProcessDrag(event, this);
                }
            }
        }
    }

    void Window::CloseAction(){
        needDestroy = true;
    }

    void Window::MinimazeAction(){
        isMinimazied = !isMinimazied;
    }

    void Window::ResizeAction(int w, int h){
        SetSize(w, h);
    }

    void Window::Paint(SDL_Renderer* render){
        SDL_SetRenderDrawColor(render, style.background.r, style.background.g, style.background.b, style.background.a);
        SDL_RenderClear(render);

        SDL_SetRenderDrawColor(render, style.border.r, style.border.g, style.border.b, style.border.a);
        
        SDL_Rect rect = this->rect;
        rect.x = 0;
        rect.y = 0;
        
        SDL_RenderDrawRect(render, &rect);
    }

    vector<Widget*> Window::GetPull(){
        return vector<Widget*>(widgetPull);
    }

    bool Window::AssignWidget(Widget* w, AString* byName){
        if(w == nullptr)
            return false;

        for(Widget * w : widgetPull){
            if(strcmp(w->GetName()->ToChars(), byName->ToChars()) == 0)
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

    Widget* Window::Find(AString* byName){
        for(Widget* w : widgetPull){
            if(strcmp(byName->ToChars(), w->GetName()->ToChars()) == 0){
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

    bool Window::MinimazeHit(int x, int y){
        SDL_Rect currentFRect = GetRect();
        SDL_Rect minimazeHitBox = GetMinimazeHitBox();

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