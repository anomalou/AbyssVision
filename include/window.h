#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <simplegl.h>
#include <wparams.h>
#include <astring.h>
#include <colors.h>
#include <widget.h>
#include <style.h>
#include <vector>
#include <stdio.h>

using namespace std;

namespace AbyssCore{
    class Window{
        protected:
            bool canMinimaze;
            bool canClose;
            bool canResize;
            bool canMove;

            bool needDestroy;

            bool beginLMove;
            bool beginRMove;
            bool beginLClick;
            bool beginRClick;
            bool beginLClose;
            bool beginLMinimize;
            bool beginLResize;
            

        protected:
            int id;
            AString* name;
            SDL_Rect rect;
            bool isVisible;
            bool isMinimized;
            bool isFull;

        protected:
            SDL_Rect closeHitBox;
            SDL_Rect minimizeHitBox;
            SDL_Rect resizeHitBox;

        protected:
            vector<Widget*> widgetPull;
            Widget* focusWidget;

        public:
            Style style;

        public:
            Window();

            virtual int GetID();
            virtual AString* GetName();
            virtual SDL_Rect GetRect();
            virtual bool IsVisible();
            virtual bool IsMinimized();
            virtual bool IsFull();
            virtual bool CanMinimize();
            virtual bool CanClose();
            virtual bool CanResize();
            virtual bool CanMoving();
            virtual SDL_Rect GetCloseHitBox();
            virtual SDL_Rect GetMinimizeHitBox();
            virtual SDL_Rect GetResizeHitBox();
            virtual bool NeedDestroy();

            virtual void SetID(int id);
            virtual void SetName(AString* name);
            virtual void SetPos(int x, int y);
            virtual void SetSize(int w, int h);
            virtual void SetRect(SDL_Rect rect);
            virtual void SetVisible(bool v);
            virtual void SetMinimize(bool m);
            virtual void SetFull(bool f);
            virtual void AllowMinimize(bool b);
            virtual void AllowClose(bool b);
            virtual void AllowResize(bool b);
            virtual void AllowMoving(bool m);

            virtual void OnMouseDown(SDL_MouseButtonEvent event);
            virtual void OnMouseUp(SDL_MouseButtonEvent event);
            virtual void OnMouseMove(SDL_MouseMotionEvent event);
            virtual void OnMouseWheel(SDL_MouseWheelEvent event, aPoint pos);

            // virtual void CloseAction();
            // virtual void MinimazeAction();
            // virtual void ResizeAction(int w, int h);

            virtual void Paint(Anchor anchor);

            virtual vector<Widget*> GetPull();
            virtual bool AssignWidget(Widget* w, AString* byName);
            virtual bool DestroyWidget(Widget* w);
            virtual Widget* Find(AString* byName);

        protected:
            virtual void CalculateControlHitBox();

            virtual bool WindowHit(int x, int y);
            virtual bool HeaderHit(int x, int y);

            virtual bool InHeader(int x, int y);
            virtual bool InBody(int x, int y);
            virtual bool InWidget(Widget* w, int x, int y);

            virtual bool CloseHit(int x, int y);
            virtual bool MinimizeHit(int x, int y);
            virtual bool ResizeHit(int x, int y);
    };

    typedef struct{
        SDL_MouseButtonEvent click;
        SDL_MouseMotionEvent move;
        Window* parent;
    }DataPack;
}

#endif