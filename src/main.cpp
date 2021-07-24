#include <iostream>
#include <SDL.h>
#include "core.h"

using namespace AbyssCore;

int main(int argc, char* args[]){
    
    InitCore();
    OpenFont("arial.ttf");

    MainWindow* mw = new MainWindow();

    AssignMainWindow(mw);

    EmptyWindow* e1 = new EmptyWindow();
    EmptyWindow* e2 = new EmptyWindow();
    EmptyWindow* e3 = new EmptyWindow();
    EmptyWindow* e4 = new EmptyWindow();

    AssignSubWindow(e1, new AString("e1"));
    AssignSubWindow(e2, new AString("e2"));
    AssignSubWindow(e3, new AString("e3"));
    AssignSubWindow(e4, new AString("e4"));


    StartCore();

    DisposeCore();

    return 0;
}


