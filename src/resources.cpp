#include <resources.h>

namespace AbyssCore{

    map<string, Texture*> Resources::textures = map<string, Texture*>();

    void Resources::LoadBaseTextures(){
        Load("ozen.png", "ozzen");
        Load("close.png", "close");
        Load("minimize.png", "minimize");
        Load("resize.png", "resize");
    }

    Texture Resources::Load(string path, string name){
        SDL_Surface* img = IMG_Load(path.c_str());

        if(img == NULL){
            char texError[256];
            snprintf(texError, 256, "This texture can't be loaded: %s(%s)", name, path);
            SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Error!", texError, NULL);
            return {0, 0, 0, 0};
        }

        char* namePtr = (char*)malloc(sizeof(char) * 256);
        strcpy(namePtr, name.c_str());

        while(textures.find(name) != textures.end()){
            strcat(namePtr, "1");
        }

        const char* nameConst = namePtr;

        Texture* texture = (Texture*)malloc(sizeof(Texture));

        if(img->format->BitsPerPixel == 24){
            texture->id = GLCreate2DTexture(img->pixels, img->w, img->h, GL_RGB, GL_LINEAR);
            texture->colorMode = GL_RGB;
        }else if(img->format->BitsPerPixel == 32){
            texture->id = GLCreate2DTexture(img->pixels, img->w, img->h, GL_RGBA, GL_LINEAR);
            texture->colorMode = GL_RGBA;
        }

        texture->width = img->w;
        texture->height = img->h;

        textures.insert({nameConst, texture});

        return *texture;
    }

    Texture Resources::Get(string name){
        if(textures.find(name) != textures.end())
            return *textures.at(name);
        else
            return {0, 0, 0, 0};
    }

    void Resources::FreeResources(){
        for(auto& item : textures){
            glDeleteTextures(1, &item.second->id);
        }
    }
}