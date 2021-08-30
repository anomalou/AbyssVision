#include <mainwindow.h>
#include <application.h>

namespace MediumCore{
    MainWindow::MainWindow() : Window(){
        trackbar = new Trackbar(this);

        trackbar->SetPos(10, 50);
        trackbar->SetSize(200, 50);

        trackbar->minValue = 1;
        trackbar->maxValue = 10;

        trackbar->SetValue(1);

        lineedit = new LineEdit(this);

        lineedit->SetPos(10, 110);
        lineedit->SetSize(200, 50);

        AssignWidget(trackbar, "trackbar");
        AssignWidget(lineedit, "lineedit");
    }

    void MainWindow::Paint(Renderer &renderer){
        Window::Paint(renderer);

        char fps[10];

        snprintf(fps, 10, "FPS:%d", Application::fps);

        renderer.DrawTextLine(aPoint({10, 30}), fps, 0, 0.5);
        renderer.DrawTextLine(aPoint({10, 250}), "Hello world!", 5, (float)((float)trackbar->GetValue() / (float)10));
    }
}