#ifndef RESOURCES_H
#define RESOURCES_H

#include <structs.h>
#include <agl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>
#include <vector>

#define TEXTURE_FLAGS IMG_INIT_PNG
#define GLIPHS " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"

using namespace std;

namespace AbyssCore{
    class Resources{
        private:
            // static map<string, Texture*> textures;
            static map<string, Font*> fonts;
            static map<string, unsigned int> shaders;
            
            static map<string, Texture*> textCache;

        public:
            static Atlas ui;
            static Atlas sprites;

        private:
            static bool GetShaderError(unsigned int id, int type);

        public:
            static void LoadBaseResources();
            static Atlas LoadAtlas(string path);
            static void LoadFont(string path, string name, int psize);
            static void LoadShader(string vpath, string fpath, string name);
            static Texture GetUI(string name);
            static Font GetFont(string name);
            static unsigned int GetShader(string name);
            /**
             * \brief Depricated
             */
            // static Texture CreateStringTexture(string str, string font, int maxChars = screen_width, int maxLines = 1);
            static void FreeResources();
    };
}

#endif