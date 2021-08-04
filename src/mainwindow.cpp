#include <mainwindow.h>
#include <core.h>

namespace AbyssCore{
    void Open(Widget* sender, ActionEvent event){
        MainWindow* mainWindow = dynamic_cast<MainWindow*>(event.parent);

        if(Core::GetGroup()->Find(new AString("empty")) == nullptr){
            mainWindow->window = new EmptyWindow();
            Core::GetGroup()->Create(mainWindow->window, new AString("empty"));
        }
    }
    void Hide(Widget* sender, ActionEvent event){
        MainWindow* mainWindow = dynamic_cast<MainWindow*>(event.parent);

        if(Core::GetGroup()->Find(new AString("empty")) != nullptr)
            mainWindow->window->SetVisible(!mainWindow->window->IsVisible());
    }

    void MoveAction(Widget* sender, ActionEvent event){
        EmptyWindow* empty = dynamic_cast<EmptyWindow*>(Core::GetGroup()->Find(new AString("empty")));

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
        open = new Button();
        hide = new Button();
        slide = new Button();
        full = new Button();

        open->SetPos(10, 10);
        open->SetSize(50, 50);

        open->SetAction(Click, Open);

        hide->SetPos(70, 10);
        hide->SetSize(50, 50);

        hide->SetAction(Click, Hide);

        slide->SetPos(130, 10);
        slide->SetSize(100, 100);

        slide->SetAction(Drag, MoveAction);

        full->SetPos(240, 10);
        full->SetSize(50, 50);

        full->style.background = {RED};

        full->SetAction(Click, FullAction);

        AssignWidget(open, new AString("open"));
        AssignWidget(hide, new AString("hide"));
        AssignWidget(slide, new AString("move"));
        AssignWidget(full, new AString("full"));
    }
}