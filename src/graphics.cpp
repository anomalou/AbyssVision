#include <graphics.h>
#include <core.h>

namespace AbyssCore{
    SDL_FRect GLConvertToNormal(SDL_Rect rect){
        float x_mid = Application::screen_width / 2;
        float y_mid = Application::screen_height / 2;

        float x = (-(x_mid - rect.x)) / x_mid;
        float y = (y_mid - rect.y) / y_mid;
        float w = (float)rect.w / x_mid;
        float h = (float)rect.h / y_mid;
        // float w = -(x_mid - (rect.x + rect.w)) / x_mid;
        // float h = (y_mid - (rect.y + rect.h)) / y_mid;

        return SDL_FRect({x, y, w, h});
    }

    void GLDrawRect(SDL_Rect rect){
        SDL_FRect frect = GLConvertToNormal(rect);

        glBegin(GL_LINE_LOOP);

        glVertex2f(frect.x, frect.y - frect.h);
        glVertex2f(frect.x, frect.y);
        glVertex2f(frect.x + frect.w, frect.y);
        glVertex2f(frect.x + frect.w, frect.y - frect.h);

        glEnd();
    }

    void GLFillRect(SDL_Rect rect){
        SDL_FRect frect = GLConvertToNormal(rect);

        glBegin(GL_QUADS);

        glVertex2f(frect.x, frect.y - frect.h);
        glVertex2f(frect.x, frect.y);
        glVertex2f(frect.x + frect.w, frect.y);
        glVertex2f(frect.x + frect.w, frect.y - frect.h);

        glEnd();
    }

    void GLSetColor(SDL_Color color){
        float r = (float)color.r / (float)256;
        float g = (float)color.g / (float)256;
        float b = (float)color.b / (float)256;
        float a = (float)color.a / (float)256;

        glColor4f(r, g, b, a);
    }
}