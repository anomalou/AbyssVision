#include <renderer.h>

namespace MediumCore{
    Renderer::Renderer(int x, int y){
        startCoords = {x, y};
        startID = 0;

        selectedAtlas = "";

        rectangles = vector<Rectangle>();
        sprites = vector<Sprite>();
        texts = vector<Text>();
    }

    void Renderer::SelectAtlas(string name){
        selectedAtlas = name;
    }

    void Renderer::DrawRect(SDL_Rect rect, aColor backgroundColor, bool drawBorder, aColor borderColor){
        Rectangle rectangle;
        rectangle.id = startID;
        rectangle.position = {rect.x + startCoords.x, rect.y + startCoords.y};
        rectangle.size = {rect.w, rect.h};
        rectangle.backgroundColor = backgroundColor;
        rectangle.drawBorder = drawBorder;
        rectangle.borderColor = borderColor;

        rectangles.push_back(rectangle);

        startID++;
    }

    void Renderer::DrawSprite(SDL_Rect rect, string texture){
        Sprite sprite;
        sprite.id = startID;
        sprite.position = {rect.x + startCoords.x, rect.y + startCoords.y};
        sprite.size = {rect.w, rect.h};
        sprite.textureName = texture;

        sprites.push_back(sprite);

        startID++;
    }

    void Renderer::DrawTextLine(aPoint pos, string str, int maxChars, float scale, int maxWidth){
        Text text;
        text.id = startID;
        text.position = {pos.x + startCoords.x, pos.y + startCoords.y};

        if(str.length() > maxChars && maxChars != 0)
            str.erase(str.begin() + (maxChars), str.end());

        text.str = str;
        text.scale = scale;
        text.maxWidth = maxWidth;

        texts.push_back(text);

        startID++;
    }

    string Renderer::SelectedAtlas(){
        return selectedAtlas;
    }

    vector<Rectangle> Renderer::GetRectangles(){
        return vector<Rectangle>(rectangles);
    }

    vector<Sprite> Renderer::GetSprites(){
        return vector<Sprite>(sprites);
    }

    vector<Text> Renderer::GetTexts(){
        return vector<Text>(texts);
    }

    int Renderer::MaxID(){
        return startID;
    }
}