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

    ew2->SetPos(100, 0);
    ew3->SetPos(200, 0);

    mw->AllowClose(false);
    mw->SetSize(RESOLUTION_X - 100, RESOLUTION_Y - 100);

    Application::Init();

    Application::GetGroup()->Create(mw, new AString("main window"));
    // UICore::GetGroup()->Create(ew1, new AString("empty window 1"));
    // UICore::GetGroup()->Create(ew2, new AString("empty window 2"));
    // UICore::GetGroup()->Create(ew3, new AString("empty window 3"));

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


