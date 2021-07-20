#include <window.h>

namespace AbyssCore{
    Window::Window(){
        name = new AString();

        widgetPull = vector<Widget*>();

        rect = SDL_Rect({0, 0, 100, 100});
        color = SDL_Color({WHITE});

        canMinimaze = true;
        canClose = false;
        canResize = false;

        isVisible = false;
        isMinimazied = false;

        needDestroy = false;

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

    SDL_Color Window::GetColor(){
        return color;
    }

    bool Window::IsVisible(){
        return isVisible;
    }

    bool Window::IsMinimazed(){
        return isMinimazied;
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

    void Window::SetColor(SDL_Color color){
        this->color = color;
    }

    void Window::SetVisible(bool v){
        isVisible = v;
    }

    void Window::SetMinimaze(bool m){
        isMinimazied = m;
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

    void Window::CalculateControlHitBox(){
        closeHitBox = {rect.w - CBUTTON_WIDTH, 0, CBUTTON_WIDTH, HEADER_HEIGHT};
        minimazeHitBox = {rect.w - 2 * CBUTTON_WIDTH + 1, 0, CBUTTON_WIDTH, HEADER_HEIGHT};
        resizeHitBox = {rect.w - CBUTTON_WIDTH, rect.h + HEADER_HEIGHT - CBUTTON_WIDTH, CBUTTON_WIDTH, CBUTTON_WIDTH};
    }

    void Window::ProcessClick(SDL_MouseButtonEvent event){
        int x = event.x;
        int y = event.y;

        //mouse button down

        if(event.type == SDL_MOUSEBUTTONDOWN){
            if(InHeader(x, y)){
                ProcessHeaderClick(event);
            }else if(InBody(x, y)){
                ProcessBodyClick(event);
            }
        }
    }

    void Window::ProcessHeaderClick(SDL_MouseButtonEvent event){
        int x = event.x;
        int y = event.y;

        if(CloseHit(x, y) && CanClose()){
            needDestroy = true;
        }
        if(MinimazeHit(x, y) && CanMinimaze()){
            SetMinimaze(!isMinimazied);
        }
    }

    void Window::ProcessBodyClick(SDL_MouseButtonEvent event){
        int x = event.x;
        int y = event.y;

        for(Widget* w : widgetPull){
            SDL_Rect rect = w->GetRect();
            rect.x += this->rect.x;
            rect.y += this->rect.y + HEADER_HEIGHT - 1;

            if(x > rect.x && x < (rect.x + rect.w) && y > rect.y && y < (rect.y + rect.h)){
                w->DoAction(this);
            }
        }
    }

    void Window::ProcessMove(SDL_MouseMotionEvent event){

    }

    void Window::ProcessDrag(SDL_MouseMotionEvent event){
        int x = event.x;
        int y = event.y;
        int xrel = event.xrel;
        int yrel = event.yrel;

        SDL_Rect rect = GetRect();

        if(InHeader(x, y)){
            SetPos(rect.x + xrel, rect.y + yrel);
        }

        if(ResizeHit(x, y) && !IsMinimazed() && CanResize()){
            SetSize(rect.w + xrel, rect.h + yrel);
        }
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

        if(x > rect.x && x < (rect.x + rect.w) && y > rect.y && y < (rect.y + HEADER_HEIGHT))
            return true;
        return false;
    }

    bool Window::InBody(int x, int y){
        SDL_Rect rect = GetRect();

        if(x > rect.x && x < (rect.x + rect.w) && y > (rect.y + HEADER_HEIGHT) && y < (rect.y + rect.h + HEADER_HEIGHT))
            return true;
        return false;
    }

    bool Window::CloseHit(int x, int y){
        SDL_Rect currentFRect = GetRect();
        SDL_Rect closeHitBox = GetCloseHitBox();

        SDL_Rect crossRect = {currentFRect.x + closeHitBox.x, currentFRect.y + closeHitBox.y, closeHitBox.w, closeHitBox.h};
    
        if(x > crossRect.x && x < (crossRect.x + crossRect.w) && y > crossRect.y && y < (crossRect.y + crossRect.h))
            return true;

        return false;
    }

    bool Window::MinimazeHit(int x, int y){
        SDL_Rect currentFRect = GetRect();
        SDL_Rect minimazeHitBox = GetMinimazeHitBox();

        SDL_Rect minRect = {currentFRect.x + minimazeHitBox.x, currentFRect.y + minimazeHitBox.y, minimazeHitBox.w, minimazeHitBox.h};
        if(x > minRect.x && x < (minRect.x + minRect.w) && y > minRect.y && y < (minRect.y + minRect.h))
            return true;
        
        return false;
    }

    bool Window::ResizeHit(int x, int y){
        SDL_Rect currentFRect = GetRect();
        SDL_Rect resizeHitBox = GetResizeHitBox();

        SDL_Rect resRect = {currentFRect.x + resizeHitBox.x, currentFRect.y + resizeHitBox.y, resizeHitBox.w, resizeHitBox.h};
        if(x > resRect.x && x < (resRect.x + resRect.w) && y > resRect.y && y < (resRect.y + resRect.h))
            return true;
        
        return false;
    }
}