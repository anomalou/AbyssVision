#include <mainwindow.h>
#include <core.h>

namespace AbyssCore{
    void CloseThis(void * ptr){
        Window* w = static_cast<Window*>(ptr);

        w->SetMinimaze(true);

        // Core* c = Core::GetInstance();

        // c->GetGroup()->Destroy(w);
    }

    MainWindow::MainWindow() : Window(){
        button = new Button();

        button->SetPos(100, 20);
        button->SetSize(100, 50);

        button->SetAction(CloseThis);

        AssignWidget(button, new AString("close button"));
    }
}