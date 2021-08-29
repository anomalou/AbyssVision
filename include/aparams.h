#ifndef APARAMS_H
#define APARAMS_H

#include <SDL.h>

#define RESOLUTION_X 1280
#define RESOLUTION_Y 720

#define WINDOW_FLAGS SDL_WINDOW_OPENGL

namespace MediumCore{
    extern int screen_width;
    extern int screen_height;

    extern SDL_Point mousePosition;
}

#endif