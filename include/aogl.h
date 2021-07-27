#ifndef AOGL_H
#define AOGL_H

#define WINDOWS

#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <application.h>
#include <astring.h>


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
    void GLDrawRect(SDL_Rect rect, SDL_Color color);
    void GLFillRect(SDL_Rect rect, SDL_Color color);

    class Shader{
        private:
            unsigned int ID;

        public:
            Shader();

        public:
            void Use();

            void SetFloat(AString* name, float value);
    };
}

#endif