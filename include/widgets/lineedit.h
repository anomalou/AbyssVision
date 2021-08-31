#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <widget.h>
#include <string>

using namespace std;

namespace MediumCore{
    class LineEdit : public Widget{
        private:
            string text;
            float scale;
            int startPointText;
            int startPointCursore;
            double textPosition;
            double cursorePosition;

            bool typingMode;
            State state;

        public:
            float smooth;
            int cursoreOffset;
        
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