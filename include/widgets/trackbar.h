#ifndef TRACKBAR_H
#define TRACKBAR_H

#include <widget.h>
#include <math.h>

#define TRACKBAR_WIDTH 10
#define TRACKBAR_HEIGHT 30

#define HANDLE_OFFSET 15

namespace AbyssCore{
    class Trackbar : public Widget{
        private:
            int value;
            State handleState;

            bool beginLMove;

        public:
            int minValue;
            int maxValue;

            Action valueChanged;

        private:
            int CalculateHandlePosition();
            aRect CalculateHandleRect();
            double CalculateHandleStep();
            bool HandleHit(int x, int y);

        public:
            Trackbar(Window* parent);
            void Paint(Anchor anchor);
            void OnMouseDown(SDL_MouseButtonEvent event);
            void OnMouseUp(SDL_MouseButtonEvent event);
            void OnMouseMove(SDL_MouseMotionEvent event);
            void OnMouseWheel(SDL_MouseWheelEvent event);
    };
}

#endif