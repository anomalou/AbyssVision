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

    void GLDrawRect(SDL_Rect rect, SDL_Color color){
        aFRect frect = GLConvertToNormal(rect);
        aFColor fcolor = GLConvertColor(color);

        unsigned int VBO, VAO;

        float vertices[] = {
            frect.left, frect.bottom, fcolor.r, fcolor.g, fcolor.b, fcolor.a,
            frect.left, frect.top, fcolor.r, fcolor.g, fcolor.b, fcolor.a,
            frect.right, frect.top, fcolor.r, fcolor.g, fcolor.b, fcolor.a,
            frect.right, frect.bottom, fcolor.r, fcolor.g, fcolor.b, fcolor.a
        };

        Shader* defaultShader = new Shader();

        defaultShader->Use();

        GLGenVertexArrays(1, &VAO);
        GLGenBuffers(1, &VBO);

        GLBindVertexArray(VAO);

        GLBindBuffer(GL_ARRAY_BUFFER, VBO);
        GLBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        GLVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        GLEnableVertexAttribArray(0);

        GLVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
        GLEnableVertexAttribArray(1);

        glDrawArrays(GL_LINE_LOOP, 0, 4);

        GLBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GLFillRect(SDL_Rect rect, SDL_Color color){
        aFRect frect = GLConvertToNormal(rect);
        aFColor fcolor = GLConvertColor(color);

        unsigned int VBO, VAO;

        float vertices[] = {
            frect.left, frect.bottom, fcolor.r, fcolor.g, fcolor.b, fcolor.a,
            frect.left, frect.top, fcolor.r, fcolor.g, fcolor.b, fcolor.a,
            frect.right, frect.top, fcolor.r, fcolor.g, fcolor.b, fcolor.a,
            frect.right, frect.bottom, fcolor.r, fcolor.g, fcolor.b, fcolor.a
        };

        Shader* defaultShader = new Shader();

        defaultShader->Use();

        GLGenVertexArrays(1, &VAO);
        GLGenBuffers(1, &VBO);

        GLBindVertexArray(VAO);

        GLBindBuffer(GL_ARRAY_BUFFER, VBO);
        GLBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        GLVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        GLEnableVertexAttribArray(0);

        GLVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
        GLEnableVertexAttribArray(1);

        glDrawArrays(GL_QUADS, 0, 4);

        GLBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Shader::Shader(){
        const char* vShaderCode = "#version 330 core\n"
                                  "layout (location = 0) in vec2 aPos;\n"
                                  "layout (location = 1) in vec4 color;\n"
                                  "out vec4 vertexColor;\n"
                                  "void main()\n"
                                  "{\n"
                                  "   gl_Position = vec4(aPos, 0.0, 1.0);\n"
                                  "   vertexColor = vec4(aPos, color.b, color.a);\n"
                                  "}\0";

        const char* fShaderCode = "#version 330 core\n"
                                  "out vec4 FragColor;\n"
                                  "in vec4 vertexColor;\n"
                                  "void main()\n"
                                  "{\n"
                                  "   FragColor = vertexColor;\n"
                                  "}\n\0";

        unsigned int vertex, fragment;
        int success;
        char info[512];

        vertex = GLCreateShader(GL_VERTEX_SHADER);

        GLShaderSource(vertex, 1, &vShaderCode, NULL);

        GLCompileShader(vertex);

        GLGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success){
            GLGetShaderInfoLog(vertex, 512, NULL, info);
            printf("Vertex shader compile error! %s\n", info);
        }

        fragment = GLCreateShader(GL_FRAGMENT_SHADER);

        GLShaderSource(fragment, 1, &fShaderCode, NULL);

        GLCompileShader(fragment);

        GLGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success){
            GLGetShaderInfoLog(fragment, 512, NULL, info);
            printf("Fragment shader compile error! %s\n", info);
        }

        ID = GLCreateProgram();
        GLAttachShader(ID, vertex);
        GLAttachShader(ID, fragment);
        GLLinkProgram(ID);

        GLGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success){
            GLGetProgramInfoLog(ID, 512, NULL, info);
            printf("Some error in linking shader program! %s\n", info);
        }

        GLDeleteShader(vertex);
        GLDeleteShader(fragment);
    }

    void Shader::Use(){
        GLUseProgram(ID);
    }

    void Shader::SetFloat(AString* name, float value){
        GLUniform1f(GLGetUniformLocation(ID, name->ToChars()), value);
    }
}