#ifndef EMPTYWINDOW_H
#define EMPTYWINDOW_H

#include <window.h>

namespace AbyssCore{
    class EmptyWindow : public Window{
        public:
            SDL_Point pos;
            EmptyWindow();

        public:
            void Paint(SDL_Renderer* render) override;
    };
}

#endif