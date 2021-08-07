#ifndef AGL_H
#define AGL_H

#define WINDOWS

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <aparams.h>
#include <astring.h>

#define VSHADER 0
#define FSHADER 1
#define PROGRAM 2

#define VERTEX_PARAMS 9

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
        int x1;
        int y1;
        int x2;
        int y2;
    }aPair;

    typedef struct{
        int x;
        int y;
    }aPoint;

    typedef struct{
        int x;
        int y;
        int z;
    }aPoint3;

    typedef struct{
        float x;
        float y;
    }aFPoint;

    typedef struct{
        float x;
        float y;
        float z;
    }aFPoint3;

    typedef struct{
        int width;
        int height;
    }aSize;

    typedef struct{
        BYTE r;
        BYTE g;
        BYTE b;
        BYTE a;
    }aColor;

    typedef struct{
        float r;
        float g;
        float b;
        float a;
    }aFColor;

    typedef struct{
        aFPoint3 pos;
        aFColor color;
        aFPoint texPos;
    }Vertex;

    // typedef struct{
    //     int size;
    //     Vertex* vertices;
    // }VertexArray;

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
    extern PFNGLDELETEVERTEXARRAYSPROC GLDeleteVertexArrays;
    extern PFNGLGENBUFFERSPROC GLGenBuffers;
    extern PFNGLDELETEBUFFERSPROC GLDeleteBuffers;
    extern PFNGLBINDVERTEXARRAYPROC GLBindVertexArray;
    extern PFNGLBINDBUFFERPROC GLBindBuffer;
    extern PFNGLBUFFERDATAPROC GLBufferData;
    extern PFNGLVERTEXATTRIBPOINTERPROC GLVertexAttribPointer;
    extern PFNGLENABLEVERTEXATTRIBARRAYPROC GLEnableVertexAttribArray;
    extern PFNGLGENFRAMEBUFFERSPROC GLGenFramebuffers;
    extern PFNGLBINDFRAMEBUFFERPROC GLBindFramebuffer;
    extern PFNGLFRAMEBUFFERTEXTURE2DPROC GLFramebufferTexture2D;
    extern PFNGLGENRENDERBUFFERSPROC GLGenRenderbuffers;
    extern PFNGLBINDRENDERBUFFERPROC GLBindRenderbuffer;
    extern PFNGLRENDERBUFFERSTORAGEPROC GLRenderbufferStorage;
    extern PFNGLFRAMEBUFFERRENDERBUFFERPROC GLFramebufferRenderbuffer;
    extern PFNGLCHECKFRAMEBUFFERSTATUSPROC GLCheckFramebufferStatus;

    bool GLInit(SDL_GLContext& context, SDL_Window* window);

    bool GLGetError();

    aFPoint3 GLScreenToNormal(aPoint3 pos);
    aFColor GLConvertColor(aColor color);
    Vertex* GLCreateRectArray(SDL_Rect rect, aColor color);
    Vertex* GLCreateLineArray(aPair pairs, aColor color);
    void GLBindVertices(Vertex* array, int size, unsigned int &VAO, unsigned int &VBO);
    void GLUnbindVertices(unsigned int VAO, unsigned int VBO);
    void GLBind2DTexture(unsigned int texture);

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