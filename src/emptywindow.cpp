#include <emptywindow.h>

namespace MediumCore{
    EmptyWindow::EmptyWindow() : Window(){
        pos = {0, 0};
    }

    void EmptyWindow::Paint(Renderer &renderer){
        Window::Paint(renderer);
        // Clear(anchor, aColor({WHITE}));

        // DrawRect(anchor, SDL_Rect({pos.x, pos.y, 10, 10}), aColor({BLACK}));
    }
}