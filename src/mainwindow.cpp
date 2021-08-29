#include <mainwindow.h>
#include <application.h>

namespace MediumCore{
    void Open(Widget* sender, ActionEvent event){
        MainWindow* mainWindow = dynamic_cast<MainWindow*>(event.parent);

        if(Application::GetGroup()->Find("empty") == nullptr){
            mainWindow->window = new EmptyWindow();
            Application::GetGroup()->Create(mainWindow->window, "empty");
        }
    }
    void Hide(Widget* sender, ActionEvent event){
        MainWindow* mainWindow = dynamic_cast<MainWindow*>(event.parent);

        if(Application::GetGroup()->Find("empty") != nullptr)
            mainWindow->window->SetVisible(!mainWindow->window->IsVisible());
    }

    void MoveAction(Widget* sender, ActionEvent event){
        EmptyWindow* empty = dynamic_cast<EmptyWindow*>(Application::GetGroup()->Find("empty"));

        if(empty != nullptr){
            SDL_Point pos = empty->pos;
            empty->pos = {pos.x + event.xrel, pos.y + event.yrel};
        }
    }

    void FullAction(Widget* sender, ActionEvent event){
        Window* parent = event.parent;

        parent->SetFull(!parent->IsFull());
    }

    MainWindow::MainWindow() : Window(){
        // open = new Button();
        // hide = new Button();
        // slide = new Button();
        full = new Button(this);
        trackbar = new Trackbar(this);

        // open->SetPos(10, 10);
        // open->SetSize(50, 50);

        // open->SetAction(Click, Open);

        // hide->SetPos(70, 10);
        // hide->SetSize(50, 50);

        // hide->SetAction(Click, Hide);

        // slide->SetPos(130, 10);
        // slide->SetSize(100, 100);

        // slide->SetAction(Drag, MoveAction);

        full->SetPos(240, 10);
        full->SetSize(50, 50);

        full->style.background = {RED};

        full->clickAction = FullAction;

        trackbar->SetPos(10, 50);
        trackbar->SetSize(200, 50);

        trackbar->minValue = 1;
        trackbar->maxValue = 10;

        trackbar->SetValue(1);

        // AssignWidget(open, new AString("open"));
        // AssignWidget(hide, new AString("hide"));
        // AssignWidget(slide, new AString("move"));
        // AssignWidget(full, new AString("full"));
        AssignWidget(trackbar, "trackbar");

        currentSize = 200;
    }

    void MainWindow::Paint(Renderer &renderer){
        Window::Paint(renderer);

        char fps[10];

        snprintf(fps, 10, "FPS:%d", Application::fps);

        renderer.DrawTextA(aPoint({10, 30}), fps, 0.5);
        renderer.DrawTextA(aPoint({10, 250}), "Hello world!", (float)((float)trackbar->GetValue() / (float)10));
    }
}