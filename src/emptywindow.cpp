#include <emptywindow.h>

namespace AbyssCore{
    EmptyWindow::EmptyWindow() : Window(){
        pos = {0, 0};
    }

    void EmptyWindow::Paint(Anchor anchor){
        Clear(anchor, aColor({WHITE}));

        DrawRect(anchor, SDL_Rect({pos.x, pos.y, 10, 10}), aColor({BLACK}));
    }
}