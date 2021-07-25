#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <GL/gl.h>
#include <application.h>

namespace AbyssCore{
    SDL_FRect GLConvertToNormal(SDL_Rect rect);
    void GLDrawRect(SDL_Rect rect);
    void GLFillRect(SDL_Rect rect);
    void GLSetColor(SDL_Color color);
}

#endif