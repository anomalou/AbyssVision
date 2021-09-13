#include <iostream>
#include <SDL.h>
#include <application.h>

using namespace MediumCore;

int main(int argc, char* args[]){
    
    // InitCore();
    // OpenFont("arial.ttf");

    // MainWindow* mw = new MainWindow();
    // mw->SetSize(RESOLUTION_X - 100, RESOLUTION_Y - 100);
    // mw->SetTitle("Main menu");
    // mw->AllowResize(false);

    // EmptyWindow* e1 = new EmptyWindow();
    // EmptyWindow* e2 = new EmptyWindow();
    // EmptyWindow* e3 = new EmptyWindow();
    // EmptyWindow* e4 = new EmptyWindow();
    // EmptyWindow* e5 = new EmptyWindow();
    // EmptyWindow* e6 = new EmptyWindow();
    // EmptyWindow* e7 = new EmptyWindow();
    // EmptyWindow* e8 = new EmptyWindow();
    // EmptyWindow* e9 = new EmptyWindow();
    // EmptyWindow* e10 = new EmptyWindow();

    Application::Init();

    for(int i = 0; i < 100; i++){
        // for(int t = 0; t < 10; t++){
            MainWindow* mw = new MainWindow();
            // mw->SetPos(100 * i, 100 * t);
            mw->SetSize(100, 100);
            char str[256];
            snprintf(str, 256, "ew%d", i);
            mw->SetTitle(str);
            // mw->AllowResize(false);
            Application::GetGroup()->Create(mw, str);
        // }
        // EmptyWindow* ew = new EmptyWindow();
        // char str[256];
        // snprintf(str, 256, "ew%d", i);
        // Application::GetGroup()->Create(ew, str);

    }

    // Application::GetGroup()->Create(e1, "e1");
    // Application::GetGroup()->Create(e2, "e2");
    // Application::GetGroup()->Create(e3, "e3");
    // Application::GetGroup()->Create(e4, "e4");
    // Application::GetGroup()->Create(e5, "e5");
    // Application::GetGroup()->Create(e6, "e6");
    // Application::GetGroup()->Create(e7, "e7");
    // Application::GetGroup()->Create(e8, "e8");
    // Application::GetGroup()->Create(e9, "e9");
    // Application::GetGroup()->Create(e10, "e10");

    // Application::GetGroup()->Create(mw, "main window");

    Application::Start();

    // AssignMainWindow(mw);

    

    // AssignSubWindow(e1, new AString("e1"));
    // AssignSubWindow(e2, new AString("e2"));
    // AssignSubWindow(e3, new AString("e3"));
    // AssignSubWindow(e4, new AString("e4"));


    // StartCore();

    // DisposeCore();

    return 0;
}


