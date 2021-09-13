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

namespace MediumCore{
    class Resources{
        private:
            static map<string, Atlas> atlases;
            static map<string, Font*> fonts;
            static map<string, unsigned int> shaders;


        public:
            static Atlas ui;

        private:
            static bool GetShaderError(unsigned int id, int type);

        public:
            static void LoadBaseResources();
            static Atlas LoadAtlas(string path);
            static void LoadFont(string path, string name, int psize);
            static void LoadShader(string vpath, string fpath, string name);
            static Texture GetUI(string name);
            static Atlas GetAtlas(string name);
            static Font GetFont(string name);
            static Font GetCurrentFont();
            static int CountStringWidth(string str, Font font, float scale = 1);
            static char ConvertKeyCode(SDL_Keycode keycode);
            static unsigned int GetShader(string name);
            static void FreeResources();
    };
}

#endif