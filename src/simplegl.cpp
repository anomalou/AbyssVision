#include <simplegl.h>

namespace AbyssCore{
    void Clear(Anchor anchor, aColor color){
        FillRect(anchor, SDL_Rect({0, 0, anchor.w, anchor.h}), color);
    }

    void DrawLine(Anchor anchor, aPair rect, aColor color){
        aPair globRect = {anchor.x + rect.x1, anchor.y + rect.y1, anchor.x + rect.x2, anchor.y + rect.y2};

        unsigned int VAO, VBO;

        GLBindVertices(GLCreateLineArray(globRect, color), 2, VAO, VBO);
        glDrawArrays(GL_LINE_STRIP, 0, 2);
        GLUnbindVertices(VAO, VBO);
    }

    void DrawRect(Anchor anchor, SDL_Rect rect, aColor color){
        SDL_Rect globRect = {anchor.x + rect.x, anchor.y + rect.y, rect.w, rect.h};

        unsigned int VAO, VBO;

        GLBindVertices(GLCreateRectArray(globRect, color), 4, VAO, VBO);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        GLUnbindVertices(VAO, VBO);
    }

    void FillRect(Anchor anchor, SDL_Rect rect, aColor color){
        SDL_Rect globRect = {anchor.x + rect.x, anchor.y + rect.y, rect.w, rect.h};
        
        unsigned int VAO, VBO;

        GLBindVertices(GLCreateRectArray(globRect, color), 4, VAO, VBO);
        glDrawArrays(GL_QUADS, 0, 4);
        GLUnbindVertices(VAO, VBO);
    }
}