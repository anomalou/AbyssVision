#include <resources.h>

namespace AbyssCore{

    map<string, Texture*> Resources::textures = map<string, Texture*>();
    map<string, Font*> Resources::fonts = map<string, Font*>();

    map<string, Texture*> Resources::textCache = map<string, Texture*>();

    void Resources::LoadBaseTextures(){
        LoadTexture("ozen.png", "ozzen");
        LoadTexture("close.png", "close");
        LoadTexture("minimize.png", "minimize");
        LoadTexture("resize.png", "resize");
    }

    void Resources::LoadBaseFonts(){
        LoadFont("arial.ttf", "arial15", 15);
        LoadFont("firacode.ttf", "firacode15", 15);
    }

    Texture Resources::LoadTexture(string path, string name){
        SDL_Surface* img = IMG_Load(path.c_str());

        if(img == NULL){
            char texError[256];
            snprintf(texError, 256, "This texture can't be loaded: %s(%s)", name.c_str(), path.c_str());
            SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Error!", texError, NULL);
            return {0, 0, 0, 0};
        }

        char* namePtr = (char*)malloc(sizeof(char) * 256);
        strcpy(namePtr, name.c_str());

        while(textures.find(name) != textures.end()){
            strcat(namePtr, "copy");
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

        SDL_FreeSurface(img);

        return *texture;
    }

    void Resources::LoadFont(string path, string name, int psize){
        TTF_Font* sfont = TTF_OpenFont(path.c_str(), psize);

        if(sfont == NULL){
            char fontError[256];
            snprintf(fontError, 256, "This font can't be loaded: %s(%s)", name.c_str(), path.c_str());
            SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Error!", fontError, NULL);
            return;
        }

        char* namePtr = (char*)malloc(sizeof(char) * 256);
        strcpy(namePtr, name.c_str());

        while(fonts.find(name) != fonts.end()){
            strcat(namePtr, "copy");
        }

        const char* nameConst = namePtr;

        Font* font = new Font({sfont, psize});

        fonts.insert({nameConst, font});
    }

    Texture Resources::GetTexture(string name){
        if(textures.find(name) != textures.end())
            return *textures.at(name);
        else{
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Cant load texture!", name.c_str(), NULL);
            return {0, 0, 0, 0};
        }
    }

    Texture Resources::CreateStringTexture(string str, string font, int maxChars, int maxLines){
        if(textCache.find(str) != textCache.end()){
            return *textCache.at(str);
        }

        if(fonts.find(font) == fonts.end()){
            SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Can't open font!", font.c_str(), NULL);
            return {0, 0, 0, 0};
        }

        SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(fonts.at(font)->font, str.c_str(), SDL_Color({0, 0, 0, 255}), maxChars);

        unsigned int textTexture;

        textTexture = GLCreate2DTexture(surface->pixels, surface->w, surface->h, GL_RGBA, GL_LINEAR);

        Texture *tex = new Texture({textTexture, surface->w, surface->h, GL_RGBA});

        if(textCache.size() > 100){
            textCache.erase(textCache.begin());
        }

        textCache.insert({str.c_str(), tex});

        return *tex;
    }

    void Resources::FreeResources(){
        for(auto& item : textures){
            glDeleteTextures(1, &item.second->id);
        }

        for(auto& item : fonts){
            TTF_CloseFont(item.second->font);
        }

        for(auto& item : textCache){
            glDeleteTextures(1, &item.second->id);
        }
    }
}