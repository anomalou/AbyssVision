#include <iostream>
#include <SDL.h>
#include <application.h>

using namespace AbyssCore;

int main(int argc, char* args[]){
    
    // InitCore();
    // OpenFont("arial.ttf");

    MainWindow* mw = new MainWindow();
    EmptyWindow* ew1 = new EmptyWindow();
    EmptyWindow* ew2 = new EmptyWindow();
    EmptyWindow* ew3 = new EmptyWindow();
    EmptyWindow* ew4 = new EmptyWindow();
    EmptyWindow* ew5 = new EmptyWindow();
    EmptyWindow* ew6 = new EmptyWindow();
    EmptyWindow* ew7 = new EmptyWindow();
    EmptyWindow* ew8 = new EmptyWindow();
    EmptyWindow* ew9 = new EmptyWindow();

    ew2->SetPos(100, 0);
    ew3->SetPos(200, 0);

    // mw->AllowClose(false);
    // mw->AllowMinimize(false);
    mw->SetSize(RESOLUTION_X - 100, RESOLUTION_Y - 100);

    Application::Init();

    Application::GetGroup()->Create(mw, new AString("main window"));
    Application::GetGroup()->Create(ew1, new AString("empty window 1"));
    Application::GetGroup()->Create(ew2, new AString("empty window 2"));
    Application::GetGroup()->Create(ew3, new AString("empty window 3"));
    Application::GetGroup()->Create(ew4, new AString("empty window 4"));
    Application::GetGroup()->Create(ew5, new AString("empty window 5"));
    Application::GetGroup()->Create(ew6, new AString("empty window 6"));
    Application::GetGroup()->Create(ew7, new AString("empty window 7"));
    Application::GetGroup()->Create(ew8, new AString("empty window 8"));
    Application::GetGroup()->Create(ew9, new AString("empty window 9"));

    Application::Start();

    Application::Dispose();

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


