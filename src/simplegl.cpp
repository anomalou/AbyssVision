#include <simplegl.h>

namespace AbyssCore{
    void Clear(Anchor anchor, aColor color){
        FillRect(anchor, SDL_Rect({0, 0, anchor.w, anchor.h}), color);
    }

    void DrawLine(Anchor anchor, aPair rect, aColor color){
        aPair globRect = {anchor.x + rect.x1, anchor.y + rect.y1, anchor.x + rect.x2, anchor.y + rect.y2};
        Vertex* vertices = (Vertex*)malloc(sizeof(Vertex) * 2);
        vertices[0].pos = {rect.x1, rect.y1};
        vertices[0].color = color;
        vertices[1].pos = {rect.x2, rect.y2};
        vertices[1].color = color;

        Vertex2DArray array = {anchor.x, anchor.y, 2, vertices};

        unsigned int VAO, VBO;

        GLBind2DVertices(array, VAO, VBO);
        GLDraw2DVertices(GL_LINE_STRIP, 2);
        GLUnbindVertices(VAO, VBO);
    }

    void DrawRect(Anchor anchor, SDL_Rect rect, aColor color){
        SDL_Rect globRect = {anchor.x + rect.x, anchor.y + rect.y, rect.w, rect.h};
        GLDraw2DRect(globRect, color);
    }

    void FillRect(Anchor anchor, SDL_Rect rect, aColor color){
        SDL_Rect globRect = {anchor.x + rect.x, anchor.y + rect.y, rect.w, rect.h};
        GLFill2DRect(globRect, color);
    }
}