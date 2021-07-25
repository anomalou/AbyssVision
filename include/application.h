#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL.h>

#define RESOLUTION_X 1240
#define RESOLUTION_Y 680

#define WINDOW_FLAGS SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE

namespace AbyssCore{
    class Application{
        public:
            static int screen_width;
            static int screen_height;

            static SDL_Point mousePosition;
    };
}

#endif