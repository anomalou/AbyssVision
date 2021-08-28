#include <agl.h>

namespace AbyssCore{

    PFNGLCREATESHADERPROC glCreateShader;
    PFNGLCREATEPROGRAMPROC glCreateProgram;
    PFNGLSHADERSOURCEPROC glShaderSource;
    PFNGLCOMPILESHADERPROC glCompileShader;
    PFNGLGETSHADERIVPROC glGetShaderiv;
    PFNGLGETPROGRAMIVPROC glGetProgramiv;
    PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
    PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
    PFNGLATTACHSHADERPROC glAttachShader;
    PFNGLLINKPROGRAMPROC glLinkProgram;
    PFNGLDELETESHADERPROC glDeleteShader;
    PFNGLUSEPROGRAMPROC glUseProgram;
    PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1i;
    PFNGLPROGRAMUNIFORM4IPROC glProgramUniform4i;
    PFNGLPROGRAMUNIFORM4FPROC glProgramUniform4f;
    PFNGLUNIFORM1IPROC glUniform1i;
    PFNGLUNIFORM1FPROC glUniform1f;
    PFNGLUNIFORM4FPROC glUniform4f;
    PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
    PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
    PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
    PFNGLGENBUFFERSPROC glGenBuffers;
    PFNGLDELETEBUFFERSPROC glDeleteBuffers;
    PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
    PFNGLBINDBUFFERPROC glBindBuffer;
    PFNGLBUFFERDATAPROC glBufferData;
    PFNGLBUFFERSUBDATAPROC glBufferSubData;
    PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
    PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
    PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
    PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
    PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
    PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
    PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
    PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
    PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
    PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
    PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
    PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
    PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced;
    PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor;

    bool GLInit(SDL_GLContext& context, SDL_Window* window){
        context = SDL_GL_CreateContext(window);

#ifdef WINDOWS
        glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
        glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
        glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
        glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
        glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
        glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
        glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
        glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
        glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
        glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
        glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
        glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
        glProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC)wglGetProcAddress("glProgramUniform1i");
        glProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC)wglGetProcAddress("glProgramUniform4i");
        glProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC)wglGetProcAddress("glProgramUniform4f");
        glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
        glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
        glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
        glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
        glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
        glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
        glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
        glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
        glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
        glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
        glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
        glBufferSubData = (PFNGLBUFFERSUBDATAPROC)wglGetProcAddress("glBufferSubData");
        glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
        glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
        glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
        glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffers");
        glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
        glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D");
        glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
        glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
        glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
        glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
        glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus");
        glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
        glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)wglGetProcAddress("glDrawArraysInstanced");
        glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)wglGetProcAddress("glVertexAttribDivisor");
#endif

        SDL_GL_SetSwapInterval(1);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        OpenGL::GetError();

        return true;
    }

    aFPoint3 GLPixelsToNormal(aPoint3 coord, int w, int h){
        float x_mid = w / 2;
        float y_mid = h / 2;

        float x = (-(x_mid - coord.x)) / x_mid;
        // float r = -(x_mid - (rect.x + rect.w)) / x_mid;
        float y = (y_mid - coord.y) / y_mid;
        // float b = (y_mid - (rect.y + rect.h)) / y_mid;
        float z = (float)coord.z;

        return aFPoint3({x, y, z});
    }

    aFPoint3 GLScreenToNormal(aPoint3 coord){
        return GLPixelsToNormal(coord, screen_width, screen_height);
    }

    aFColor GLConvertColor(aColor color){
        float r = (float)color.r / (float)255;
        float g = (float)color.g / (float)255;
        float b = (float)color.b / (float)255;
        float a = (float)color.a / (float)255;

        return aFColor({r, g, b, a});
    }

    // Vertex* GLCreateRectArray(SDL_Rect rect, aColor color){
    //     aPoint3 v1 = {rect.x, rect.y + rect.h, 0};
    //     aPoint3 v2 = {rect.x, rect.y, 0};
    //     aPoint3 v3 = {rect.x + rect.w, rect.y, 0};
    //     aPoint3 v4 = {rect.x + rect.w, rect.y + rect.h, 0};

    //     aFPoint3 nv1 = GLScreenToNormal(v1);
    //     aFPoint3 nv2 = GLScreenToNormal(v2);
    //     aFPoint3 nv3 = GLScreenToNormal(v3);
    //     aFPoint3 nv4 = GLScreenToNormal(v4);

    //     aFColor ncolor = GLConvertColor(color);

    //     Vertex* vertices = (Vertex*)malloc(sizeof(Vertex) * 4);
    //     vertices[0] = {nv1, ncolor, {0, 0}};
    //     vertices[1] = {nv2, ncolor, {0, 1}};
    //     vertices[2] = {nv3, ncolor, {1, 1}};
    //     vertices[3] = {nv4, ncolor, {1, 0}};

    //     return vertices;
    // }

    // Vertex* GLCreateLineArray(aPair pairs, aColor color){
    //     aFPoint3 nv1 = GLScreenToNormal(aPoint3({pairs.x1, pairs.y1, 0}));
    //     aFPoint3 nv2 = GLScreenToNormal(aPoint3({pairs.x2, pairs.y2, 0}));

    //     aFColor ncolor = GLConvertColor(color);

    //     Vertex* vertices = (Vertex*)malloc(sizeof(Vertex) * 2);
    //     vertices[0] = {nv1, ncolor, {0, 0}};
    //     vertices[1] = {nv2, ncolor, {0, 0}};

    //     return vertices;
    // }

    // float* GLVAtoFA(Vertex* array, int size){
    //     float* fvertices = (float*)malloc(sizeof(float) * size * VERTEX_PARAMS);

    //     for(int i = 0; i < size; i++){
    //         fvertices[i * VERTEX_PARAMS + 0] = array[i].pos.x;
    //         fvertices[i * VERTEX_PARAMS + 1] = array[i].pos.y;
    //         fvertices[i * VERTEX_PARAMS + 2] = array[i].pos.z;
    //         fvertices[i * VERTEX_PARAMS + 3] = array[i].color.r;
    //         fvertices[i * VERTEX_PARAMS + 4] = array[i].color.g;
    //         fvertices[i * VERTEX_PARAMS + 5] = array[i].color.b;
    //         fvertices[i * VERTEX_PARAMS + 6] = array[i].color.a;
    //         fvertices[i * VERTEX_PARAMS + 7] = array[i].texPos.x;
    //         fvertices[i * VERTEX_PARAMS + 8] = array[i].texPos.y;
    //     }
        
    //     return fvertices;
    // }

    // void GLCreateVertexObjects(Vertex* vertices, int size, unsigned int &VAO, unsigned int &VBO){
    //     glGenVertexArrays(1, &VAO);
    //     glGenBuffers(1, &VBO);

    //     glBindVertexArray(VAO);
    //     glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //     float* fvertices = GLVAtoFA(vertices, size);

    //     glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size * VERTEX_PARAMS, fvertices, GL_STATIC_DRAW);

    //     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_PARAMS * sizeof(float), (void*)0);
    //     glEnableVertexAttribArray(0);

    //     glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VERTEX_PARAMS * sizeof(float), (void*)(3 * sizeof(float)));
    //     glEnableVertexAttribArray(1);

    //     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VERTEX_PARAMS * sizeof(float), (void*)(7 * sizeof(float)));
    //     glEnableVertexAttribArray(2);

    //     delete vertices;
    //     delete fvertices;

    //     glBindVertexArray(0);
    //     glBindBuffer(GL_ARRAY_BUFFER, 0);
    // }

    // void GLDestroyVertexObjects(unsigned int VAO, unsigned int VBO){
    //     glBindBuffer(GL_ARRAY_BUFFER, 0);
    //     glBindVertexArray(0);

    //     glDeleteVertexArrays(1, &VAO);
    //     glDeleteBuffers(1, &VBO);
    // }

    // unsigned int GLCreate2DTexture(void* data, int width, int height, int colorMode, int filtration){
    //     unsigned int texture;
    //     glGenTextures(1, &texture);

    //     glBindTexture(GL_TEXTURE_2D, texture);

    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtration);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtration);

    //     glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
    //     glGenerateMipmap(GL_TEXTURE_2D);

    //     glBindTexture(GL_TEXTURE_2D, 0);

    //     return texture;
    // }

    void GLBind2DTexture(unsigned int texture){
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    // void GLRenderText(string str, string font, aPoint pos, int maxWidth){
    //     Font fontObj = Resources::GetFont(font);

    //     aFPoint3 nstart = GLScreenToNormal(aPoint3({pos.x, pos.y, 0}));

    //     unsigned int dVAO, dVBO;

    //     glGenVertexArrays(1, &dVAO);
    //     glGenBuffers(1, &dVBO);
    //     glBindVertexArray(dVAO);
    //     glBindBuffer(GL_ARRAY_BUFFER, dVBO);

    //     glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * VERTEX_PARAMS, NULL, GL_DYNAMIC_DRAW);

    //     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_PARAMS * sizeof(float), (void*)0);
    //     glEnableVertexAttribArray(0);

    //     glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VERTEX_PARAMS * sizeof(float), (void*)(3 * sizeof(float)));
    //     glEnableVertexAttribArray(1);

    //     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VERTEX_PARAMS * sizeof(float), (void*)(7 * sizeof(float)));
    //     glEnableVertexAttribArray(2);

    //     glBindBuffer(GL_ARRAY_BUFFER, 0);

    //     aFColor black = {0, 0, 0, 1};

    //     GLBind2DTexture(fontObj.gliphsTexture);

    //     textureShader->Use();
    //     textureShader->SetInt1("flip", 1);

    //     for(int i = 0; i < str.length(); i++){
    //         char c = str[i];
    //         if(fontObj.gliphs.find(c) == fontObj.gliphs.end()){
    //             SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error with text!", "Foundned unsupported simbols in text!", NULL);
    //             return;
    //         }
    //         Gliph *gliph = fontObj.gliphs.at(c);
    //         // gliph->texCoord.

    //         int width = gliph->maxx - gliph->minx;
    //         int height = gliph->maxy - gliph->miny;

    //         aFPoint3 nlu = GLScreenToNormal(aPoint3({pos.x + gliph->minx, pos.y - gliph->maxy, 0}));
    //         aFPoint3 nrb = GLScreenToNormal(aPoint3({pos.x + gliph->advance, pos.y - gliph->miny, 0}));

    //         Vertex* gliphVertices = (Vertex*)malloc(sizeof(Vertex) * 4);
    //         gliphVertices[0] = {{nlu.x, nrb.y, 0}, black, {gliph->texRect.left, gliph->texRect.bottom}};
    //         gliphVertices[1] = {{nlu.x, nlu.y, 0}, black, {gliph->texRect.left, gliph->texRect.top}};
    //         gliphVertices[2] = {{nrb.x, nlu.y, 0}, black, {gliph->texRect.right, gliph->texRect.top}};
    //         gliphVertices[3] = {{nrb.x, nrb.y, 0}, black, {gliph->texRect.right, gliph->texRect.bottom}};

    //         glBindBuffer(GL_ARRAY_BUFFER, dVBO);
    //         glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 4, GLVAtoFA(gliphVertices, 4));
    //         glBindBuffer(GL_ARRAY_BUFFER, 0);

    //         glDrawArrays(GL_QUADS, 0, 4);

    //         pos.x += gliph->advance;
    //     }

    //     // 
    //     // gliphVertices[0] = {{}}

    // }

    unsigned int OpenGL::currentVAO = 0;
    unsigned int OpenGL::currentVBO = 0;
    unsigned int OpenGL::current2DTexture = 0;
    unsigned int OpenGL::currentProgram = 0;

    void OpenGL::GetError(){
        auto error = GL_NO_ERROR;
        error = glGetError();
        if(error != GL_NO_ERROR){
            printf("Error! %s\n", gluErrorString(error));
        }
    }

    float OpenGL::Proportion(int pixels, int maxValue){
        return (float)((float)(pixels) / (float)(maxValue));
    }

    float OpenGL::ScreenProportion(int pixels, int maxPixels){
        return (float)((float)(pixels * 2) / (float)(maxPixels));
    }

    aFPoint OpenGL::PixelsToNormal(aPoint coord, int w, int h){
        float x_mid = w / 2;
        float y_mid = h / 2;

        float x = (-(x_mid - coord.x)) / x_mid;
        // float r = -(x_mid - (rect.x + rect.w)) / x_mid;
        float y = (y_mid - coord.y) / y_mid;
        // float b = (y_mid - (rect.y + rect.h)) / y_mid;

        return aFPoint({x, y});
    }

    aFPoint OpenGL::TexelsToNormal(aPoint coord, int w, int h){
        aFPoint npoint = {
            (float)coord.x / (float)w,
            (float)coord.y / (float)h
        };

        return npoint;
    }

    aFColor OpenGL::NormilizeColor(aColor color){
        float r = (float)color.r / (float)255;
        float g = (float)color.g / (float)255;
        float b = (float)color.b / (float)255;
        float a = (float)color.a / (float)255;

        return aFColor({r, g, b, a});
    }

    void OpenGL::GenArrayBuffer(unsigned int &name){
        glGenBuffers(1, &name);
    }   

    void OpenGL::GenVertexArray(unsigned int &name){
        glGenVertexArrays(1, &name);
    }

    void OpenGL::Bind2DTexture(unsigned int name){
        if(current2DTexture != name){
            glBindTexture(GL_TEXTURE_2D, name);
            current2DTexture = name;
        }
    }

    unsigned int OpenGL::Create2DTexture(void* data, int width, int height, int colorMode, int filtration){
        unsigned int texture;
        glGenTextures(1, &texture);

        GLBind2DTexture(texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtration);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtration);

        glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        GLBind2DTexture(0);

        return texture;
    }

    void OpenGL::BindVAO(unsigned int name){
        if(currentVAO != name){
            glBindVertexArray(name);
            currentVAO = name;
        }
    }

    void OpenGL::BindVBO(unsigned int name){
        if(currentVBO != name){
            glBindBuffer(GL_ARRAY_BUFFER, name);
            currentVBO = name;
        }
    }

    void OpenGL::UseProgram(unsigned int name){
        if(currentProgram != name){
            glUseProgram(name);
            currentProgram = name;
        }
    }

    void OpenGL::UseProgram(string name){
        UseProgram(Resources::GetShader(name));
    }

    void OpenGL::Set1i(string name, int x){
        if(currentProgram != 0){
            glProgramUniform1i(currentProgram, glGetUniformLocation(currentProgram, name.c_str()), x);
        }
    }

    void OpenGL::Set4i(string name, int x, int y, int z, int w){
        if(currentProgram != 0){
            glProgramUniform4i(currentProgram, glGetUniformLocation(currentProgram, name.c_str()), x, y, z, w);
        }
    }

    void OpenGL::Set4f(string name, float x, float y, float z, float w){
        if(currentProgram != 0){
            glProgramUniform4f(currentProgram, glGetUniformLocation(currentProgram, name.c_str()), x, y, z, w);
        }
    }

    Shader::Shader(){
        
    }

    void Shader::Use(){
        glUseProgram(ID);
    }

    void Shader::Load(string vpath, string fpath){
        
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

        if(!GetError(vertex, VSHADER))
            return;

        fragment = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragment, 1, &fShaderCode, NULL);

        glCompileShader(fragment);

        if(!GetError(fragment, FSHADER))
            return;

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        GetError(ID, PROGRAM);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    bool Shader::GetError(int proc, Uint32 type){
        int success;
        char infoLog[512];

        switch(type){
            case PROGRAM:
                glGetProgramiv(proc, GL_LINK_STATUS, &success);
            break;
            case VSHADER:
            case FSHADER:
                glGetShaderiv(proc, GL_COMPILE_STATUS, &success);
            break;
        }

        if(!success){
            switch(type){
                case PROGRAM:
                    glGetProgramInfoLog(proc, 512, NULL, infoLog);
                    printf("Some error in linking shader program! %s\n", infoLog);
                break;
                case VSHADER:
                    glGetShaderInfoLog(proc, 512, NULL, infoLog);
                    printf("Vertex shader compile error! %s\n", infoLog);
                break;
                case FSHADER:
                    glGetShaderInfoLog(proc, 512, NULL, infoLog);
                    printf("Fragment shader compile error! %s\n", infoLog);
                break;
            }

            return false;
        }

        return true;
    }

    void Shader::SetInt1(string name, int i){
        glUniform1i(glGetUniformLocation(ID, name.c_str()), i);
    }

    void Shader::SetFloat4(string name, float x, float y, float z, float w){
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
}