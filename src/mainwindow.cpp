#include <mainwindow.h>
#include <core.h>

namespace AbyssCore{
    void Open(void* w, void * ptr){
        MainWindow* win = static_cast<MainWindow*>(ptr);
        if(Core::GetInstance()->GetGroup()->Find(new AString("empty")) == nullptr){
            win->window = new EmptyWindow();
            AssignSubWindow(win->window, new AString("empty"));
        }
    }
    void Hide(void* w, void * ptr){
        MainWindow* win = static_cast<MainWindow*>(ptr);

        if(Core::GetInstance()->GetGroup()->Find(new AString("empty")) != nullptr)
            win->window->SetVisible(!win->window->IsVisible());
    }

    MainWindow::MainWindow() : Window(){
        open = new Button();
        hide = new Button();

        open->SetPos(0, 0);
        open->SetSize(50, 50);

        open->SetAction(Click, Open);

        hide->SetPos(60, 0);
        hide->SetSize(50, 50);

        hide->SetAction(Click, Hide);

        AssignWidget(open, new AString("open"));
        AssignWidget(hide, new AString("hide"));
    }
}