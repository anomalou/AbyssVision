#ifndef RESOURCES_H
#define RESOURCES_H

#include <agl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>

#define TEXTURE_FLAGS IMG_INIT_PNG

using namespace std;

namespace AbyssCore{
    typedef struct{
        unsigned int id;
        int width;
        int height;
        int colorMode;
    }Texture;

    typedef struct{
        TTF_Font* font;
        int psize;
    }Font;

    class Resources{
        private:
            static map<string, Texture*> textures;
            static map<string, Font*> fonts;
            
            static map<string, Texture*> textCache;

        public:
            static void LoadBaseTextures();
            static void LoadBaseFonts();
            static Texture LoadTexture(string path, string name);
            static void LoadFont(string path, string name, int psize);
            static Texture GetTexture(string name);
            static Texture CreateStringTexture(string str, string font, int maxChars = screen_width, int maxLines = 1);
            static void FreeResources();
    };
}

#endif