#ifndef EMPTYWINDOW_H
#define EMPTYWINDOW_H

#include <window.h>

namespace MediumCore{
    /**
     * \brief Sub window class for debugging
     */
    class EmptyWindow : public Window{
        public:
            SDL_Point pos;
            EmptyWindow();

        public:
            virtual void Paint(Renderer &renderer) override;
    };
}

#endif