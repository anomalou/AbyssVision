#ifndef BUTTON_H
#define BUTTON_H

#include <widget.h>

namespace AbyssCore{
    class Button : public Widget{
        public:
            void ProcessClick(SDL_MouseButtonEvent event, Window * parent);
            void ProcessDrag(SDL_MouseMotionEvent event, Window * parent);
            void ProcessMove(SDL_MouseMotionEvent event, Window * parent);
            void Paint(Anchor anchor);
    };
}

#endif