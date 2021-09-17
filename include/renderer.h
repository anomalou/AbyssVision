#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>
#include <structs.h>
#include <colors.h>

#define TEXT_SCALE 0.35

using namespace std;

namespace MediumCore{
    class Renderer{
        private:
            aPoint startCoords;
            aSize maxSize;
            int startID;
            vector<Rectangle> rectangles;
            vector<Sprite> sprites;
            vector<Text> texts;
            string selectedAtlas;

        private:
            bool InRect(SDL_Rect rect);
        
        public:
            Renderer(int x, int y, int w, int h);
            void SelectAtlas(string name);
            void DrawRect(SDL_Rect rect, aColor backgroundColor, bool drawBorder, aColor borderColor = {WHITE});
            void DrawSprite(SDL_Rect rect, string texture);
            void DrawTextLine(aPoint pos, string str, int maxChars = 0, float scale = TEXT_SCALE, int maxWidth = 0);
            string SelectedAtlas();
            vector<Rectangle> GetRectangles();
            vector<Sprite> GetSprites();
            vector<Text> GetTexts();
            int MaxID();
    };
}

#endif