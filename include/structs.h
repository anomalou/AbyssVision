#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL_ttf.h>
#include <string>
#include <map>

using namespace std;

namespace AbyssCore{
    typedef struct{
        int left;
        int right;
        int top;
        int bottom;
    }aRect;

    typedef struct{
        float left;
        float right;
        float top;
        float bottom;
    }aFRect;

    typedef struct{
        int x1;
        int y1;
        int x2;
        int y2;
    }aPair;

    typedef struct{
        int x;
        int y;
    }aPoint;

    typedef struct{
        int x;
        int y;
        int z;
    }aPoint3;

    typedef struct{
        float x;
        float y;
    }aFPoint;

    typedef struct{
        float a;
        float b;
    }aFRange;

    typedef struct{
        float x;
        float y;
        float z;
    }aFPoint3;

    typedef struct{
        int width;
        int height;
    }aSize;

    typedef struct{
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    }aColor;

    typedef struct{
        float r;
        float g;
        float b;
        float a;
    }aFColor;

    typedef struct{
        aFPoint3 pos;
        aFColor color;
        aFPoint texPos;
    }Vertex;

    typedef struct{
        unsigned int id;
        int width;
        int height;
        int colorMode;
    }Texture;

    typedef struct{
        int minx;
        int maxx;
        int miny;
        int maxy;
        int advance;
        aFRect texRect;
    }Gliph;

    typedef struct{
        TTF_Font* font;
        int psize;
        unsigned int gliphsTexture;
        map<char, Gliph*> gliphs;
    }Font;
}


#endif