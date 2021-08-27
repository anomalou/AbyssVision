#include <resources.h>

namespace AbyssCore{

    // map<string, Texture*> Resources::textures = map<string, Texture*>();
    Atlas Resources::ui;
    Atlas Resources::sprites;
    map<string, Font*> Resources::fonts = map<string, Font*>();
    map<string, unsigned int> Resources::shaders = map<string, unsigned int>();

    // map<string, Texture*> Resources::textCache = map<string, Texture*>();

    bool Resources::GetShaderError(unsigned int id, int type){
        int success;
        char infoLog[512];

        switch(type){
            case PROGRAM:
                glGetProgramiv(id, GL_LINK_STATUS, &success);
            break;
            case VSHADER:
            case FSHADER:
                glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            break;
        }

        if(!success){
            switch(type){
                case PROGRAM:
                    glGetProgramInfoLog(id, 512, NULL, infoLog);
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Shader linking error!", infoLog, NULL);
                break;
                case VSHADER:
                    glGetShaderInfoLog(id, 512, NULL, infoLog);
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Vertex compiling error!", infoLog, NULL);
                break;
                case FSHADER:
                    glGetShaderInfoLog(id, 512, NULL, infoLog);
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fragment compiling error!", infoLog, NULL);
                break;
            }

            return false;
        }

        return true;
    }

    void Resources::LoadBaseResources(){
        // LoadTexture("ozen.png", "ozzen");
        // LoadTexture("close.png", "close");
        // LoadTexture("minimize.png", "minimize");
        // LoadTexture("resize.png", "resize");

        ui = LoadAtlas("ui.ata");
        // sprites = LoadAtlas("sprites.ata");

        LoadFont("arial.ttf", "arial15", 15);
        LoadFont("firacode.ttf", "firacode15", 15);

        // LoadShader("shaders/interfacev.glsl", "shaders/interfacef.glsl", "interface");
        // LoadShader("shaders/windowv.glsl", "shaders/windowf.glsl", "window");
        LoadShader("shaders/icolorv.glsl", "shaders/icolorf.glsl", "icolor");
        LoadShader("shaders/itexturev.glsl", "shaders/itexturef.glsl", "itexture");
    }

    // Texture Resources::LoadTexture(string path, string name){
    //     SDL_Surface* img = IMG_Load(path.c_str());

    //     if(img == NULL){
    //         char texError[256];
    //         snprintf(texError, 256, "This texture can't be loaded: %s(%s)", name.c_str(), path.c_str());
    //         SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Error!", texError, NULL);
    //         return {0, 0, 0, 0};
    //     }

    //     char* namePtr = (char*)malloc(sizeof(char) * 256);
    //     strcpy(namePtr, name.c_str());

    //     while(textures.find(name) != textures.end()){
    //         strcat(namePtr, "copy");
    //     }

    //     const char* nameConst = namePtr;

    //     Texture* texture = (Texture*)malloc(sizeof(Texture));

    //     if(img->format->BitsPerPixel == 24){
    //         texture->id = OpenGL::Create2DTexture(img->pixels, img->w, img->h, GL_RGB, GL_LINEAR);
    //         texture->colorMode = GL_RGB;
    //     }else if(img->format->BitsPerPixel == 32){
    //         texture->id = OpenGL::Create2DTexture(img->pixels, img->w, img->h, GL_RGBA, GL_LINEAR);
    //         texture->colorMode = GL_RGBA;
    //     }

    //     texture->width = img->w;
    //     texture->height = img->h;

    //     textures.insert({nameConst, texture});

    //     SDL_FreeSurface(img);

    //     return *texture;
    // }

    Atlas Resources::LoadAtlas(string path){
        ifstream stream(path, ios::binary);
        Atlas atlas;

        if(stream.is_open()){
            int size;
            stream.read((char*)&size, sizeof(size));
            for(int i = 0; i < size; i++){
                int length;
                stream.read((char*)&length, sizeof(int));
                string name;
                char c;
                for(int t = 0; t < length; t++){
                    stream.read((char*)&c, sizeof(char));
                    name.append(1, c);
                }
                uint16_t x;
                uint16_t y;
                uint16_t w;
                uint16_t h;
                stream.read((char*)&x, sizeof(uint16_t));
                stream.read((char*)&y, sizeof(uint16_t));
                stream.read((char*)&w, sizeof(uint16_t));
                stream.read((char*)&h, sizeof(uint16_t));

                Texture tex = {
                    x,
                    y,
                    w,
                    h
                };

                atlas.textures.insert({name, tex});
            }

            int width;
            int height;

            stream.read((char*)&width, sizeof(int));
            stream.read((char*)&height, sizeof(int));

            vector<float> pixelData = vector<float>();

            for(int i = 0; i < (width * height); i++){
                char r;
                char g;
                char b;
                char a;

                stream.read((char*)&r, sizeof(char));
                stream.read((char*)&g, sizeof(char));
                stream.read((char*)&b, sizeof(char));
                stream.read((char*)&a, sizeof(char));

                aFColor fColor = OpenGL::NormilizeColor(aColor{r, g, b, a});

                pixelData.push_back(fColor.r);
                pixelData.push_back(fColor.g);
                pixelData.push_back(fColor.b);
                pixelData.push_back(fColor.a);
            }

            size_t s = pixelData.size();

            atlas.count = size;
            atlas.width = width;
            atlas.height = height;
            
            atlas.id = OpenGL::Create2DTexture(pixelData.data(), width, height, GL_RGBA, GL_NEAREST);
        }

        return atlas;
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

        Font* font = new Font();
        font->font = sfont;
        font->psize = psize;
        SDL_Surface *gliphSurface = TTF_RenderText_Blended(sfont, GLIPHS, SDL_Color({0, 0, 0, 255}));
        font->gliphsTexture = OpenGL::Create2DTexture(gliphSurface->pixels, gliphSurface->w, gliphSurface->h, GL_RGBA, GL_LINEAR);

        if(font->gliphsTexture == 0){
            SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Error with font initialization!", name.c_str(), NULL);
            return;
        }

        int offset = 0;

        int min = 0;

        for(int i = 0; i < 96; i++){
            char c = GLIPHS[i];

            Gliph* gliph = new Gliph();

            TTF_GlyphMetrics(sfont, c, &gliph->minx, &gliph->maxx, &gliph->miny, &gliph->maxy, &gliph->advance);

            if(gliph->miny < min)
                min = gliph->miny;

            float a = (float)(offset + gliph->minx) / (float)gliphSurface->w;
            float b = (float)(offset + gliph->advance) / (float)gliphSurface->w;

            offset += gliph->advance;

            gliph->texRect = {a, b, 0, 0};

            font->gliphs.insert({c, gliph});
        }

        min = abs(min);

        for(int i = 0; i < 96; i++){
            char c = GLIPHS[i];
            Gliph *gliph = font->gliphs.at(c);
            gliph->texRect.bottom = (float)(min + gliph->miny) / (float)(psize);
            gliph->texRect.top = (float)(min + gliph->maxy) / (float)(psize);
        }

        SDL_FreeSurface(gliphSurface);

        fonts.insert({nameConst, font});
    }

    void Resources::LoadShader(string vpath, string fpath, string name){
        unsigned int id;

        ifstream vfile(vpath, ios::binary);
        ifstream ffile(fpath, ios::binary);

        if(!vfile.is_open() || !ffile.is_open())
            return;

        stringstream vss;
        stringstream fss;

        vss << vfile.rdbuf();
        fss << ffile.rdbuf();

        string vs = vss.str();
        string fs = fss.str();

        vfile.close();
        ffile.close();

        const char* vShaderCode = vs.c_str();
        const char* fShaderCode = fs.c_str();

        unsigned int vertex, fragment;
        int success;
        char info[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertex, 1, &vShaderCode, NULL);

        glCompileShader(vertex);

        if(!GetShaderError(vertex, VSHADER))
            return;

        fragment = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragment, 1, &fShaderCode, NULL);

        glCompileShader(fragment);

        if(!GetShaderError(fragment, FSHADER))
            return;

        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);

        GetShaderError(id, PROGRAM);
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        shaders.insert({name, id});
    }

    // Texture Resources::GetTexture(string name){
    //     if(textures.find(name) != textures.end())
    //         return *textures.at(name);
    //     else{
    //         SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Cant get texture!", name.c_str(), NULL);
    //         return {0, 0, 0, 0};
    //     }
    // }

    Font Resources::GetFont(string name){
        if(fonts.find(name) != fonts.end())
            return *fonts.at(name);
        else{
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Cant get font!", name.c_str(), NULL);
            return {};
        }
    }

    unsigned int Resources::GetShader(string name){
        if(shaders.find(name) != shaders.end()){
            return shaders.at(name);
        }

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Shader not founded!", name.c_str(), NULL);

        return 0;
    }

    // Texture Resources::CreateStringTexture(string str, string font, int maxChars, int maxLines){
    //     if(textCache.find(str) != textCache.end()){
    //         return *textCache.at(str);
    //     }

    //     if(fonts.find(font) == fonts.end()){
    //         SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Can't open font!", font.c_str(), NULL);
    //         return {0, 0, 0, 0};
    //     }

    //     SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(fonts.at(font)->font, str.c_str(), SDL_Color({0, 0, 0, 255}), maxChars);

    //     unsigned int textTexture;

    //     textTexture = OpenGL::Create2DTexture(surface->pixels, surface->w, surface->h, GL_RGBA, GL_LINEAR);

    //     Texture *tex = new Texture({textTexture, surface->w, surface->h, GL_RGBA});

    //     if(textCache.size() > 100){
    //         textCache.erase(textCache.begin());
    //     }

    //     textCache.insert({str.c_str(), tex});

    //     return *tex;
    // }

    void Resources::FreeResources(){
        // for(auto& item : textures){
        //     glDeleteTextures(1, &item.second->id);
        // }

        for(auto& item : fonts){
            TTF_CloseFont(item.second->font);
        }

        // for(auto& item : textCache){
        //     glDeleteTextures(1, &item.second->id);
        // }
    }
}