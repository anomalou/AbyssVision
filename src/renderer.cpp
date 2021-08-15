#include <renderer.h>

namespace AbyssCore{
    Renderer::Renderer(int x, int y){
        startCoords = {x, y};
        startID = 0;

        rectangles = vector<Rectangle>();
        sprites = vector<Sprite>();
    }

    void Renderer::DrawRect(SDL_Rect rect, aColor backgroundColor, bool drawBorder, aColor borderColor){
        Rectangle rectangle;
        rectangle.id = startID;
        rectangle.position = {rect.x, rect.y};
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
        sprite.position = {rect.x, rect.y};
        sprite.size = {rect.w, rect.h};
        sprite.textureName = texture;

        sprites.push_back(sprite);

        startID++;
    }

    vector<Rectangle> Renderer::GetRectangles(){
        return vector<Rectangle>(rectangles);
    }

    vector<Sprite> Renderer::GetSprites(){
        return vector<Sprite>(sprites);
    }
}