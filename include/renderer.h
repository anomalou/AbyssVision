#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>
#include <structs.h>

using namespace std;

namespace AbyssCore{
    class Renderer{
        private:
            aPoint startCoords;
            int startID;
            vector<Rectangle> rectangles;
            vector<Sprite> sprites;
            vector<Text> texts;
        
        public:
            Renderer(int x, int y);
            void DrawRect(SDL_Rect rect, aColor backgroundColor, bool drawBorder, aColor borderColor);
            void DrawSprite(SDL_Rect rect, string texture);
            void DrawText(aPoint pos, string str);
            vector<Rectangle> GetRectangles();
            vector<Sprite> GetSprites();
            vector<Text> GetTexts();
            int MaxID();
    };
}

#endif