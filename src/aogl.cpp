#include <aogl.h>
#include <core.h>

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
    PFNGLGENBUFFERSPROC GLGenBuffers;
    PFNGLBINDVERTEXARRAYPROC GLBindVertexArray;
    PFNGLBINDBUFFERPROC GLBindBuffer;
    PFNGLBUFFERDATAPROC GLBufferData;
    PFNGLVERTEXATTRIBPOINTERPROC GLVertexAttribPointer;
    PFNGLENABLEVERTEXATTRIBARRAYPROC GLEnableVertexAttribArray;

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
        GLGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
        GLBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
        GLBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
        GLBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
        GLVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
        GLEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
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

    aFRect GLConvertToNormal(SDL_Rect rect){
        float x_mid = Application::screen_width / 2;
        float y_mid = Application::screen_height / 2;

        float l = (-(x_mid - rect.x)) / x_mid;
        float r = -(x_mid - (rect.x + rect.w)) / x_mid;
        float t = (y_mid - rect.y) / y_mid;
        float b = (y_mid - (rect.y + rect.h)) / y_mid;

        return aFRect({l, r, t, b});
    }

    aFColor GLConvertColor(SDL_Color color){
        float r = (float)color.r / (float)255;
        float g = (float)color.g / (float)255;
        float b = (float)color.b / (float)255;
        float a = (float)color.a / (float)255;

        return aFColor({r, g, b, a});
    }

    void GLDraw2DRect(SDL_Rect rect, SDL_Color color){
        aFRect frect = GLConvertToNormal(rect);
        aFColor fcolor = GLConvertColor(color);

        float vertices[] = {
            frect.left, frect.bottom, fcolor.r, fcolor.g, fcolor.b, fcolor.a,
            frect.left, frect.top, fcolor.r, fcolor.g, fcolor.b, fcolor.a,
            frect.right, frect.top, fcolor.r, fcolor.g, fcolor.b, fcolor.a,
            frect.right, frect.bottom, fcolor.r, fcolor.g, fcolor.b, fcolor.a
        };

        GLBind2DVertices(vertices, 24);

        GLDraw2DVertices(GL_LINE_LOOP, 4);

        GLUnbindVertices();
    }

    void GLFill2DRect(SDL_Rect rect, SDL_Color color){
        aFRect frect = GLConvertToNormal(rect);
        aFColor fcolor = GLConvertColor(color);

        float vertices[] = {
            frect.left, frect.bottom, fcolor.r, fcolor.g, fcolor.b, fcolor.a,
            frect.left, frect.top, fcolor.r, fcolor.g, fcolor.b, fcolor.a,
            frect.right, frect.top, fcolor.r, fcolor.g, fcolor.b, fcolor.a,
            frect.right, frect.bottom, fcolor.r, fcolor.g, fcolor.b, fcolor.a
        };

        GLBind2DVertices(vertices, 24);

        GLDraw2DVertices(GL_QUADS, 4);

        GLUnbindVertices();
    }

    void GLBind2DVertices(float* vertices, int size){
        // float fvertices[] = {vertices};

        unsigned int VBO, VAO;

        GLGenVertexArrays(1, &VAO);
        GLGenBuffers(1, &VBO);

        GLBindVertexArray(VAO);

        GLBindBuffer(GL_ARRAY_BUFFER, VBO);
        GLBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices, GL_STATIC_DRAW);

        GLVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        GLEnableVertexAttribArray(0);

        GLVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
        GLEnableVertexAttribArray(1);
    }

    void GLDraw2DVertices(GLenum mode, int vnumber){
        glDrawArrays(mode, 0, vnumber);
    }

    void GLUnbindVertices(){
        GLBindBuffer(GL_ARRAY_BUFFER, 0);
        GLBindVertexArray(0);
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