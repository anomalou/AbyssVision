#ifndef BUTTON_H
#define BUTTON_H

#include <widget.h>

namespace AbyssCore{
    class Button : public Widget{
        private:
            bool beginClick;
            State state;

        public:
            Action clickAction;

        public:
            Button(Window* parent);
            void Paint(Renderer &renderer);
            void OnMouseDown(SDL_MouseButtonEvent event);
            void OnMouseUp(SDL_MouseButtonEvent event);
            void OnMouseMove(SDL_MouseMotionEvent event);
            void OnMouseWheel(SDL_MouseWheelEvent event, aPoint pos);
    };
}

#endif