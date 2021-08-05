#include <agl.h>

namespace AbyssCore{

    PFNGLCREATESHADERPROC GLCreateShader;
    PFNGLCREATEPROGRAMPROC GLCreateProgram;
    PFNGLSHADERSOURCEPROC GLShaderSource;
    PFNGLCOMPILESHADERPROC GLCompileShader;
    PFNGLGETSHADERIVPROC GLGetShaderiv;
    PFNGLGETPROGRAMIVPROC GLGetProgramiv;
    PFNGLGETSHADERINFOLOGPROC GLGetShaderInfoLog;
    PFNGLGETPROGRAMINFOLOGPROC GLGetProgramInfoLog;
    PFNGLATTACHSHADERPROC GLAttachShader;
    PFNGLLINKPROGRAMPROC GLLinkProgram;
    PFNGLDELETESHADERPROC GLDeleteShader;
    PFNGLUSEPROGRAMPROC GLUseProgram;
    PFNGLUNIFORM1FPROC GLUniform1f;
    PFNGLGETUNIFORMLOCATIONPROC GLGetUniformLocation;
    PFNGLGENVERTEXARRAYSPROC GLGenVertexArrays;
    PFNGLDELETEVERTEXARRAYSPROC GLDeleteVertexArrays;
    PFNGLGENBUFFERSPROC GLGenBuffers;
    PFNGLDELETEBUFFERSPROC GLDeleteBuffers;
    PFNGLBINDVERTEXARRAYPROC GLBindVertexArray;
    PFNGLBINDBUFFERPROC GLBindBuffer;
    PFNGLBUFFERDATAPROC GLBufferData;
    PFNGLVERTEXATTRIBPOINTERPROC GLVertexAttribPointer;
    PFNGLENABLEVERTEXATTRIBARRAYPROC GLEnableVertexAttribArray;
    PFNGLGENFRAMEBUFFERSPROC GLGenFramebuffers;
    PFNGLBINDFRAMEBUFFERPROC GLBindFramebuffer;
    PFNGLFRAMEBUFFERTEXTURE2DPROC GLFramebufferTexture2D;
    PFNGLGENRENDERBUFFERSPROC GLGenRenderbuffers;
    PFNGLBINDRENDERBUFFERPROC GLBindRenderbuffer;
    PFNGLRENDERBUFFERSTORAGEPROC GLRenderbufferStorage;
    PFNGLFRAMEBUFFERRENDERBUFFERPROC GLFramebufferRenderbuffer;
    PFNGLCHECKFRAMEBUFFERSTATUSPROC GLCheckFramebufferStatus;

    Shader* defaultShader; 
    Shader* clearShader;

    bool GLInit(SDL_GLContext& context, SDL_Window* window){
        context = SDL_GL_CreateContext(window);

#ifdef WINDOWS
        GLCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
        GLCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
        GLShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
        GLCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
        GLGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
        GLGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
        GLGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
        GLGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
        GLAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
        GLLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
        GLDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
        GLUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
        GLUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
        GLGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
        GLGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
        GLDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
        GLGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
        GLDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
        GLBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
        GLBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
        GLBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
        GLVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
        GLEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
        GLGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
        GLBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
        GLFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D");
        GLGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
        GLBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
        GLRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
        GLFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
        GLCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus");
#endif

        defaultShader = new Shader();
        defaultShader->Load(new AString("shaders/defaultVertex.glsl"), new AString("shaders/defaultFragment.glsl"));

        clearShader = new Shader();
        clearShader->Load(new AString("shaders/clearVertex.glsl"), new AString("shaders/clearFragment.glsl"));

        SDL_GL_SetSwapInterval(1);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        if(GLGetError())
            return false;

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        if(GLGetError())
            return false;

        return true;
    }

    bool GLGetError(){
        auto error = GL_NO_ERROR;
        error = glGetError();
        if(error != GL_NO_ERROR){
            printf("Error! %s\n", gluErrorString(error));
            return true;
        }

        return false;
    }

    aFPoint GLConvertToNormal(aPoint pos){
        float x_mid = Application::screen_width / 2;
        float y_mid = Application::screen_height / 2;

        float x = (-(x_mid - pos.x)) / x_mid;
        // float r = -(x_mid - (rect.x + rect.w)) / x_mid;
        float y = (y_mid - pos.y) / y_mid;
        // float b = (y_mid - (rect.y + rect.h)) / y_mid;

        return aFPoint({x, y});
    }

    aFColor GLConvertColor(aColor color){
        float r = (float)color.r / (float)255;
        float g = (float)color.g / (float)255;
        float b = (float)color.b / (float)255;
        float a = (float)color.a / (float)255;

        return aFColor({r, g, b, a});
    }

    void GLDraw2DRect(SDL_Rect rect, aColor color){
        unsigned int VAO, VBO;

        GLBind2DRect(rect, color, VAO, VBO);

        GLDraw2DVertices(GL_LINE_LOOP, 4);

        GLUnbindVertices(VAO, VBO);
    }

    void GLFill2DRect(SDL_Rect rect, aColor color){
        unsigned int VAO, VBO;

        GLBind2DRect(rect, color, VAO, VBO);

        GLDraw2DVertices(GL_QUADS, 4);

        GLUnbindVertices(VAO, VBO);
    }

    void GLBind2DRect(SDL_Rect rect, aColor color, unsigned int &VAO, unsigned int &VBO){
        Vertex* vertices = (Vertex*)malloc(sizeof(Vertex) * 4);
        vertices[0].pos = {0, rect.h};
        vertices[0].color = color;
        vertices[1].pos = {0, 0};
        vertices[1].color = color;
        vertices[2].pos = {rect.w, 0};
        vertices[2].color = color;
        vertices[3].pos = {rect.w, rect.h};
        vertices[3].color = color;

        GLBind2DVertices(Vertex2DArray({rect.x, rect.y, 4, vertices}), VAO, VBO);
    }

    void GLBind2DRectTex(SDL_Rect rect, unsigned int &VAO, unsigned int &VBO){
        Vertex* vertices = (Vertex*)malloc(sizeof(Vertex) * 4);
        vertices[0].pos = {0, rect.h};
        vertices[0].texPos = {0, 0};
        vertices[1].pos = {0, 0};
        vertices[1].texPos = {0, 1.0};
        vertices[2].pos = {rect.w, 0};
        vertices[2].texPos = {1.0, 1.0};
        vertices[3].pos = {rect.w, rect.h};
        vertices[3].texPos = {1.0, 0};

        GLBind2DVertices(Vertex2DArray({rect.x, rect.y, 4, vertices}), VAO, VBO);
    }

    void GLBind2DVertices(Vertex2DArray array, unsigned int &VAO, unsigned int &VBO){
        GLGenVertexArrays(1, &VAO);
        GLGenBuffers(1, &VBO);

        GLBindVertexArray(VAO);

        GLBindBuffer(GL_ARRAY_BUFFER, VBO);

        Vertex *arrayPtr = array.vertices;

        float* vertices = (float*)malloc(sizeof(float) * array.size * 8);

        for(int i = 0; i < array.size; i++){
            aPoint globPos = {arrayPtr[i].pos.x + array.x, arrayPtr[i].pos.y + array.y};

            aFPoint normalCoord = GLConvertToNormal(globPos);
            aFColor normalColor = GLConvertColor(arrayPtr[i].color);

            vertices[0 + i * 8] = normalCoord.x;
            vertices[1 + i * 8] = normalCoord.y;
            vertices[2 + i * 8] = arrayPtr->texPos.x;
            vertices[3 + i * 8] = arrayPtr->texPos.y;
            vertices[4 + i * 8] = normalColor.r;
            vertices[5 + i * 8] = normalColor.g;
            vertices[6 + i * 8] = normalColor.b;
            vertices[7 + i * 8] = normalColor.a;
        }

        GLBufferData(GL_ARRAY_BUFFER, sizeof(float) * array.size * 8, vertices, GL_STATIC_DRAW);

        GLVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        GLEnableVertexAttribArray(0);

        GLVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
        GLEnableVertexAttribArray(1);

        GLVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
        GLEnableVertexAttribArray(2);
    }

    void GLDraw2DVertices(GLenum mode, int vnumber){
        glDrawArrays(mode, 0, vnumber);
    }

    void GLUnbindVertices(unsigned int VAO, unsigned int VBO){
        GLBindBuffer(GL_ARRAY_BUFFER, 0);
        GLBindVertexArray(0);

        GLDeleteVertexArrays(1, &VAO);
        GLDeleteBuffers(1, &VBO);
    }

    void GLBind2DTexture(unsigned int texture){
        glBindTexture(GL_TEXTURE_2D, texture);
        GLGetError();
    }

    void GLBindFrameBuffer(unsigned int framebuffer){
        GLBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    }

    Shader::Shader(){
        
    }

    void Shader::Use(){
        GLUseProgram(ID);
    }

    void Shader::Load(AString* vpath, AString* fpath){
        
        ifstream vfile(vpath->ToChars(), ios::binary);
        ifstream ffile(fpath->ToChars(), ios::binary);

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

        vertex = GLCreateShader(GL_VERTEX_SHADER);

        GLShaderSource(vertex, 1, &vShaderCode, NULL);

        GLCompileShader(vertex);

        if(!GetError(vertex, VSHADER))
            return;

        fragment = GLCreateShader(GL_FRAGMENT_SHADER);

        GLShaderSource(fragment, 1, &fShaderCode, NULL);

        GLCompileShader(fragment);

        if(!GetError(fragment, FSHADER))
            return;

        ID = GLCreateProgram();
        GLAttachShader(ID, vertex);
        GLAttachShader(ID, fragment);
        GLLinkProgram(ID);

        GetError(ID, PROGRAM);
        GLDeleteShader(vertex);
        GLDeleteShader(fragment);
    }

    bool Shader::GetError(int proc, Uint32 type){
        int success;
        char infoLog[512];

        switch(type){
            case PROGRAM:
                GLGetProgramiv(proc, GL_LINK_STATUS, &success);
            break;
            case VSHADER:
            case FSHADER:
                GLGetShaderiv(proc, GL_COMPILE_STATUS, &success);
            break;
        }

        if(!success){
            switch(type){
                case PROGRAM:
                    GLGetProgramInfoLog(proc, 512, NULL, infoLog);
                    printf("Some error in linking shader program! %s\n", infoLog);
                break;
                case VSHADER:
                    GLGetShaderInfoLog(proc, 512, NULL, infoLog);
                    printf("Vertex shader compile error! %s\n", infoLog);
                break;
                case FSHADER:
                    GLGetShaderInfoLog(proc, 512, NULL, infoLog);
                    printf("Fragment shader compile error! %s\n", infoLog);
                break;
            }

            return false;
        }

        return true;
    }

    void Shader::SetFloat(AString* name, float value){
        GLUniform1f(GLGetUniformLocation(ID, name->ToChars()), value);
    }
}