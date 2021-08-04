#ifndef WIDGET_H
#define WIDGET_H

#include <SDL.h>
#include <simplegl.h>
#include <astring.h>
#include <colors.h>
#include <style.h>
#include <map>

using namespace std;

namespace AbyssCore{
    class Window;

    typedef enum{
        Click,
        Drag,
        Move
    }ActionType;

    typedef struct{
        Window* parent;
        int x;
        int y;
        int xrel;
        int yrel;
        Uint32 button;
    }ActionEvent;

    class Widget{

        typedef void (*Action)(Widget*, ActionEvent);

        protected:
            AString* name;
            SDL_Rect rect;
            
            State state;
            bool isVisible;
            bool isDisabled;

            map<ActionType, Action> actions;

        public:
            /**
             * \brief Widget style
             */
            Style style;

        public:
            Widget();

            virtual AString* GetName();
            virtual SDL_Rect GetRect();
            virtual State GetState();
            virtual bool IsVisible();
            virtual bool IsDisabled();

            virtual void SetName(AString* name);
            virtual void SetPos(int x, int y);
            virtual void SetSize(int w, int h);
            virtual void SetRect(SDL_Rect rect);
            virtual void SetState(State state);
            virtual void SetVisible(bool v);
            virtual void SetDisable(bool d);
            virtual void SetAction(ActionType type, Action action);

            /**
             * \brief void * parent ptr to parent window
             */
            virtual void ProcessClick(SDL_MouseButtonEvent event, Window * parent) = 0;

            /**
             * \brief void * parent ptr to parent window
             */
            virtual void ProcessDrag(SDL_MouseMotionEvent event, Window * parent) = 0;

            /**
             * \brief void * parent ptr to parent window
             */
            virtual void ProcessMove(SDL_MouseMotionEvent event, Window * parent) = 0;

            virtual void Paint(Anchor anchor) = 0;
    };
}

#endif