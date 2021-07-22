#ifndef WIDGET_H
#define WIDGET_H

#include <SDL.h>
#include <astring.h>
#include <colors.h>
#include <style.h>

namespace AbyssCore{
    typedef void (*Action)(void*, void*);

    typedef enum{
        Click,
        Drag,
        Move
    }ActionType;

    class Widget{
        protected:
            AString* name;
            SDL_Rect rect;
            Style style;
            State state;
            bool isVisible;
            bool isDisabled;

            Action click;
            Action drag;
            Action move;
            

        public:
            Widget();

            virtual AString* GetName();
            virtual SDL_Rect GetRect();
            virtual Style GetStyle();
            virtual State GetState();
            virtual bool IsVisible();
            virtual bool IsDisabled();

            virtual void SetName(AString* name);
            virtual void SetPos(int x, int y);
            virtual void SetSize(int w, int h);
            virtual void SetRect(SDL_Rect rect);
            virtual void SetStyle(Style style);
            virtual void SetState(State state);
            virtual void SetVisible(bool v);
            virtual void SetDisable(bool d);
            virtual void SetAction(ActionType type, Action action);

            /**
             * \brief void * parent ptr to parent window
             */
            virtual void ProcessClick(SDL_MouseButtonEvent event, void * parent);

            /**
             * \brief void * parent ptr to parent window
             */
            virtual void ProcessDrag(SDL_MouseMotionEvent event, void * parent);

            /**
             * \brief void * parent ptr to parent window
             */
            virtual void ProcessMove(SDL_MouseMotionEvent event, void * parent);

            virtual void Paint(SDL_Renderer* render);
    };
}

#endif