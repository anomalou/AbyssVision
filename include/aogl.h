#ifndef AOGL_H
#define AOGL_H

#define WINDOWS

#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <application.h>
#include <astring.h>

#define VSHADER 0
#define FSHADER 1
#define PROGRAM 2

using namespace std;

namespace AbyssCore{

    typedef struct{
        int left;
        int right;
        int top;
        int bottom;
    }aRect;

    typedef struct{
        float left;
        float right;
        float top;
        float bottom;
    }aFRect;

    typedef struct{
        float r;
        float g;
        float b;
        float a;
    }aFColor;

    extern PFNGLCREATESHADERPROC GLCreateShader;
    extern PFNGLCREATEPROGRAMPROC GLCreateProgram;
    extern PFNGLSHADERSOURCEPROC GLShaderSource;
    extern PFNGLCOMPILESHADERPROC GLCompileShader;
    extern PFNGLGETSHADERIVPROC GLGetShaderiv;
    extern PFNGLGETPROGRAMIVPROC GLGetProgramiv;
    extern PFNGLGETSHADERINFOLOGPROC GLGetShaderInfoLog;
    extern PFNGLATTACHSHADERPROC GLAttachShader;
    extern PFNGLLINKPROGRAMPROC GLLinkProgram;
    extern PFNGLDELETESHADERPROC GLDeleteShader;
    extern PFNGLUSEPROGRAMPROC GLUseProgram;
    extern PFNGLUNIFORM1FPROC GLUniform1f;
    extern PFNGLGETUNIFORMLOCATIONPROC GLGetUniformLocation;
    extern PFNGLGENVERTEXARRAYSPROC GLGenVertexArrays;
    extern PFNGLGENBUFFERSPROC GLGenBuffers;
    extern PFNGLBINDVERTEXARRAYPROC GLBindVertexArray;
    extern PFNGLBINDBUFFERPROC GLBindBuffer;
    extern PFNGLBUFFERDATAPROC GLBufferData;
    extern PFNGLVERTEXATTRIBPOINTERPROC GLVertexAttribPointer;
    extern PFNGLENABLEVERTEXATTRIBARRAYPROC GLEnableVertexAttribArray;

    bool GLInit(SDL_GLContext& context, SDL_Window* window);

    bool GLGetError();

    aFRect GLConvertToNormal(SDL_Rect rect);
    aFColor GLConvertColor(SDL_Color color);
    void GLDraw2DRect(SDL_Rect rect, SDL_Color color);
    void GLFill2DRect(SDL_Rect rect, SDL_Color color);
    void GLBind2DVertices(float* vertices, int size);
    void GLDraw2DVertices(GLenum mode, int vnumber);
    void GLUnbindVertices();

    class Shader{
        private:
            unsigned int ID;

        public:
            Shader();

        public:
            void Use();

            void Load(AString* vpath, AString* fpath);

            bool GetError(int proc, Uint32 type);

            void SetFloat(AString* name, float value);
    };

    extern Shader* defaultShader; 
    extern Shader* clearShader;
}

#endif