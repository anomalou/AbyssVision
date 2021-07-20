#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <windowproperty.h>
#include <astring.h>
#include <colors.h>
#include <widget.h>
#include <vector>
#include <stdio.h>

using namespace std;

namespace AbyssCore{
    class Window{
        protected:
            bool canMinimaze;
            bool canClose;
            bool canResize;

            bool needDestroy;

        protected:
            int id;
            AString* name;
            SDL_Rect rect;
            SDL_Color color;
            bool isVisible;
            bool isMinimazied;

        protected:
            SDL_Rect closeHitBox;
            SDL_Rect minimazeHitBox;
            SDL_Rect resizeHitBox;

        protected:
            vector<Widget*> widgetPull;

        public:
            Window();

            virtual int GetID();
            virtual AString* GetName();
            virtual SDL_Rect GetRect();
            virtual SDL_Color GetColor();
            virtual bool IsVisible();
            virtual bool IsMinimazed();
            virtual bool CanMinimaze();
            virtual bool CanClose();
            virtual bool CanResize();
            virtual SDL_Rect GetCloseHitBox();
            virtual SDL_Rect GetMinimazeHitBox();
            virtual SDL_Rect GetResizeHitBox();
            virtual bool NeedDestroy();

            virtual void SetID(int id);
            virtual void SetName(AString* name);
            virtual void SetPos(int x, int y);
            virtual void SetSize(int w, int h);
            virtual void SetRect(SDL_Rect rect);
            virtual void SetColor(SDL_Color color);
            virtual void SetVisible(bool v);
            virtual void SetMinimaze(bool m);
            virtual void AllowMinimaze(bool b);
            virtual void AllowClose(bool b);
            virtual void AllowResize(bool b);

            virtual void ProcessClick(SDL_MouseButtonEvent event);
            virtual void ProcessHeaderClick(SDL_MouseButtonEvent event);
            virtual void ProcessBodyClick(SDL_MouseButtonEvent event);
            virtual void ProcessMove(SDL_MouseMotionEvent event);
            virtual void ProcessDrag(SDL_MouseMotionEvent event);

            virtual vector<Widget*> GetPull();
            virtual bool AssignWidget(Widget* w, AString* byName);
            virtual bool DestroyWidget(Widget* w);
            virtual Widget* Find(AString* byName);


        protected:
            virtual void CalculateControlHitBox();

            virtual bool InHeader(int x, int y);
            virtual bool InBody(int x, int y);

            virtual bool CloseHit(int x, int y);
            virtual bool MinimazeHit(int x, int y);
            virtual bool ResizeHit(int x, int y);
    };
}

#endif