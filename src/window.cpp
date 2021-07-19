#include <window.h>

namespace AbyssCore{
    Window::Window(){
        name = new AString();
        rect = SDL_Rect({0, 0, 100, 100});
        color = SDL_Color({WHITE});

        canMinimaze = true;
        canClose = false;
        canResize = false;

        isVisible = false;
        isMinimazied = false;

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
}