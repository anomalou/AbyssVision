#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <widget.h>
#include <string>

#define OFFSET 5

using namespace std;

namespace MediumCore{
    class LineEdit : public Widget{
        private:
            string text;
            State state;
        
        public:
            LineEdit(Window* parent);

            void OnKeyPressed(SDL_KeyboardEvent event);
            void OnKeyReleased(SDL_KeyboardEvent event);

            void OnMouseDown(SDL_MouseButtonEvent event);
            void OnMouseUp(SDL_MouseButtonEvent event);

            void Paint(Renderer &renderer);
    };
}

#endif