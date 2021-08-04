#ifndef EMPTYWINDOW_H
#define EMPTYWINDOW_H

#include <window.h>

namespace AbyssCore{
    /**
     * \brief Sub window class for debugging
     */
    class EmptyWindow : public Window{
        public:
            SDL_Point pos;
            EmptyWindow();

        public:
            virtual void Paint(Anchor anchor) override;
    };
}

#endif