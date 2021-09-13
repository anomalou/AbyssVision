#include <resources.h>

namespace MediumCore{

    // map<string, Texture*> Resources::textures = map<string, Texture*>();
    Atlas Resources::ui;
    map<string, Atlas> atlases = map<string, Atlas>();
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

        LoadFont("arial.ttf", "arial", 50);
        // LoadFont("firacode.ttf", "firacode", 50);

        // LoadShader("shaders/interfacev.glsl", "shaders/interfacef.glsl", "interface");
        // LoadShader("shaders/windowv.glsl", "shaders/windowf.glsl", "window");
        LoadShader("shaders/icolorv.glsl", "shaders/icolorf.glsl", "icolor");
        LoadShader("shaders/itexturev.glsl", "shaders/itexturef.glsl", "itexture");
    }

    Atlas Resources::LoadAtlas(string path){
        //TODO: Update reading with atlas name
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

            vector<char> pixelData = vector<char>();

            for(int i = 0; i < (width * height); i++){
                char r;
                char g;
                char b;
                char a;

                stream.read((char*)&r, sizeof(char));
                stream.read((char*)&g, sizeof(char));
                stream.read((char*)&b, sizeof(char));
                stream.read((char*)&a, sizeof(char));

                // aFColor fColor = OpenGL::NormilizeColor(aColor{r, g, b, a});

                pixelData.push_back(r);
                pixelData.push_back(g);
                pixelData.push_back(b);
                pixelData.push_back(a);
            }

            size_t s = pixelData.size();

            atlas.count = size;
            atlas.width = width;
            atlas.height = height;
            
            atlas.id = OpenGL::Create2DTexture(pixelData.data(), width, height, GL_RGBA, GL_LINEAR);
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

        int maxHeight = 0;
        int min = 0;

        for(int i = 0; i < 96; i++){
            char c = GLIPHS[i];

            Gliph* gliph = new Gliph();

            TTF_GlyphMetrics(sfont, c, &gliph->minx, &gliph->maxx, &gliph->miny, &gliph->maxy, &gliph->advance);

            if(gliph->miny < min)
                min = gliph->miny;

            if(gliph->maxy - gliph->miny > maxHeight)
                maxHeight = gliph->maxy - gliph->miny;

            float a = (float)(offset + gliph->minx) / (float)gliphSurface->w;
            float b = (float)(offset + gliph->maxx) / (float)gliphSurface->w;

            offset += gliph->advance;

            gliph->texRect = {a, b, 0, 0};

            font->gliphs.insert({c, gliph});
        }

        min = abs(min);

        for(int i = 0; i < 96; i++){
            char c = GLIPHS[i];
            Gliph *gliph = font->gliphs.at(c);
            gliph->texRect.bottom = (float)(min + gliph->miny) / (float)(gliphSurface->h);
            gliph->texRect.top = (float)(gliph->maxy - gliph->miny) / (float)(gliphSurface->h);
        }

        SDL_FreeSurface(gliphSurface);

        font->height = maxHeight;

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

    Texture Resources::GetUI(string name){
        if(ui.textures.find(name) != ui.textures.end()){
            return ui.textures.at(name);
        }else{
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "UI Texture error!", "Cant load selected texture from UI atlas!", NULL);
            return Texture();
        }
    }

    Atlas Resources::GetAtlas(string name){
        if(atlases.find(name) != atlases.end()){
            return atlases.at(name);
        }else{
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Atlas error!", "Cant load selected texture atlas!", NULL);
            return Atlas();
        }
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

    Font Resources::GetCurrentFont(){
        if(!fonts.empty()){
            return *(prev(fonts.end())->second);
        }
        return Font();
    }

    int Resources::CountStringWidth(string str, Font font, float scale){
        int width = 0;
        for(int i = 0; i < str.length(); i++){
            Gliph* gliph = font.gliphs[str[i]];
            width += gliph->advance * scale;
        }

        return width;
    }

    char Resources::ConvertKeyCode(SDL_Keycode keycode){
        string code = SDL_GetKeyName(keycode);
        if(code.length() == 1)
            return code[0];
        else{
            switch(keycode){
                case SDLK_AMPERSAND:
                    return '&';
                case SDLK_ASTERISK:
                    return '*';
                case SDLK_AT:
                    return '@';
                case SDLK_CARET:
                    return '^';
                case SDLK_COLON:
                    return ':';
                case SDLK_DOLLAR:
                    return '$';
                case SDLK_EXCLAIM:
                    return '!';
                case SDLK_GREATER:
                    return '>';
                case SDLK_HASH:
                    return '#';
                case SDLK_LEFTPAREN:
                    return '(';
                case SDLK_LESS:
                    return '<';
                case SDLK_PERCENT:
                    return '%';
                case SDLK_PLUS:
                    return '+';
                case SDLK_QUESTION:
                    return '?';
                case SDLK_QUOTEDBL:
                    return '"';
                case SDLK_RIGHTPAREN:
                    return ')';
                case SDLK_UNDERSCORE:
                    return '_';
                default:
                    return ' ';
            }
        }
    }

    unsigned int Resources::GetShader(string name){
        if(shaders.find(name) != shaders.end()){
            return shaders.at(name);
        }

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Shader not founded!", name.c_str(), NULL);

        return 0;
    }

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