#include <emptywindow.h>

namespace MediumCore{
    EmptyWindow::EmptyWindow() : Window(){
        pos = {0, 0};
    }

    void EmptyWindow::Paint(Renderer &renderer){
        Window::Paint(renderer);

        renderer.DrawTextLine(aPoint({0, 30}), "I'm empty =)", 0.35);
    }
}