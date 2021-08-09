#ifndef RESOURCES_H
#define RESOURCES_H

#include <agl.h>
#include <SDL_image.h>
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

    class Resources{
        private:
            static map<string, Texture*> textures;

        public:
            static void LoadBaseTextures();
            static Texture Load(string path, string name);
            static Texture Get(string name);
            static void FreeResources();
    };
}

#endif