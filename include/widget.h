#ifndef WIDGET_H
#define WIDGET_H

#include <SDL.h>
#include <astring.h>
#include <colors.h>

namespace AbyssCore{
    typedef void (*Action)(void*);

    class Widget{
        protected:
            AString* name;
            SDL_Rect rect;
            SDL_Color color;
            bool isVisible;

            Action action;

        public:
            Widget();

            virtual AString* GetName();
            virtual SDL_Rect GetRect();
            virtual SDL_Color GetColor();
            virtual bool IsVisible();
            virtual void DoAction(void * ptr);

            virtual void SetName(AString* name);
            virtual void SetPos(int x, int y);
            virtual void SetSize(int w, int h);
            virtual void SetRect(SDL_Rect rect);
            virtual void SetColor(SDL_Color color);
            virtual void SetVisible(bool v);
            virtual void SetAction(Action action);
    };
}

#endif