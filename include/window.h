#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <windowproperty.h>
#include <astring.h>
#include <colors.h>

namespace AbyssCore{
    class Window{
        protected:
            bool canMinimaze;
            bool canClose;
            bool canResize;

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

        protected:
            virtual void CalculateControlHitBox();
    };
}

#endif