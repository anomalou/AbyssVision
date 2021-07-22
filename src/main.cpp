#include <iostream>
#include <SDL.h>
#include "core.h"

using namespace AbyssCore;

int main(int argc, char* args[]){
    
    InitCore();
    OpenFont("arial.ttf");

    AssignMainWindow(new MainWindow());

    StartCore();

    DisposeCore();

    return 0;
}


