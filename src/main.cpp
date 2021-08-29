#include <iostream>
#include <SDL.h>
#include <application.h>

using namespace MediumCore;

int main(int argc, char* args[]){
    
    // InitCore();
    // OpenFont("arial.ttf");

    MainWindow* mw = new MainWindow();
    mw->SetSize(RESOLUTION_X - 100, RESOLUTION_Y - 100);
    mw->SetTitle("Main menu");

    Application::Init();

    for(int i = 0; i < 10; i++){
        EmptyWindow* ew = new EmptyWindow();
        char str[256];
        snprintf(str, 256, "ew%d", i);
        Application::GetGroup()->Create(ew, str);
    }

    Application::GetGroup()->Create(mw, "main window");

    Application::Start();

    // AssignMainWindow(mw);

    // EmptyWindow* e1 = new EmptyWindow();
    // EmptyWindow* e2 = new EmptyWindow();
    // EmptyWindow* e3 = new EmptyWindow();
    // EmptyWindow* e4 = new EmptyWindow();

    // AssignSubWindow(e1, new AString("e1"));
    // AssignSubWindow(e2, new AString("e2"));
    // AssignSubWindow(e3, new AString("e3"));
    // AssignSubWindow(e4, new AString("e4"));


    // StartCore();

    // DisposeCore();

    return 0;
}


