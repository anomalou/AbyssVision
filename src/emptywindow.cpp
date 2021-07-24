#include <emptywindow.h>

namespace AbyssCore{
    EmptyWindow::EmptyWindow() : Window(){
        pos = {0, 0};
    }

    void EmptyWindow::Paint(SDL_Renderer* render){
        Window::Paint(render);

        SDL_Rect rect = {pos.x, pos.y, 10, 10};

        SDL_SetRenderDrawColor(render, BLACK);
        SDL_RenderDrawRect(render, &rect);
    }
}