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
#include <structs.h>
#include <resources.h>
#include <string>

#define VSHADER 0
#define FSHADER 1
#define PROGRAM 2

#define VERTEX_PARAMS 9

using namespace std;

namespace AbyssCore{

    // typedef struct{
    //     int size;
    //     Vertex* vertices;
    // }VertexArray;

    extern PFNGLCREATESHADERPROC glCreateShader;
    extern PFNGLCREATEPROGRAMPROC glCreateProgram;
    extern PFNGLSHADERSOURCEPROC glShaderSource;
    extern PFNGLCOMPILESHADERPROC glCompileShader;
    extern PFNGLGETSHADERIVPROC glGetShaderiv;
    extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
    extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
    extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
    extern PFNGLATTACHSHADERPROC glAttachShader;
    extern PFNGLLINKPROGRAMPROC glLinkProgram;
    extern PFNGLDELETESHADERPROC glDeleteShader;
    extern PFNGLUSEPROGRAMPROC glUseProgram;
    extern PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1i;
    extern PFNGLPROGRAMUNIFORM4IPROC glProgramUniform4i;
    extern PFNGLPROGRAMUNIFORM4FPROC glProgramUniform4f;
    extern PFNGLUNIFORM1IPROC glUniform1i;
    extern PFNGLUNIFORM1FPROC glUniform1f;
    extern PFNGLUNIFORM4FPROC glUniform4f;
    extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
    extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
    extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
    extern PFNGLGENBUFFERSPROC glGenBuffers;
    extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
    extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
    extern PFNGLBINDBUFFERPROC glBindBuffer;
    extern PFNGLBUFFERDATAPROC glBufferData;
    extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
    extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
    extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
    extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
    extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
    extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
    extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
    extern PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
    extern PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
    extern PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
    extern PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
    extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
    extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

    bool GLInit(SDL_GLContext& context, SDL_Window* window);

    bool GLGetError();

    aFPoint3 GLPixelsToNormal(aPoint3 coord, int w, int h);
    aFPoint3 GLScreenToNormal(aPoint3 coord);
    aFColor GLConvertColor(aColor color);
    Vertex* GLCreateRectArray(SDL_Rect rect, aColor color);
    Vertex* GLCreateLineArray(aPair pairs, aColor color);
    float* GLVAtoFA(Vertex* array, int size);
    void GLCreateVertexObjects(Vertex* array, int size, unsigned int &VAO, unsigned int &VBO);
    void GLDestroyVertexObjects(unsigned int VAO, unsigned int VBO);
    unsigned int GLCreate2DTexture(void* data, int width, int height, int colorMode, int filtration);
    void GLBind2DTexture(unsigned int texture);
    void GLRenderText(string str, string font, aPoint pos, int maxWidth = screen_width);

    class OpenGL{
        private:
            static unsigned int currentVAO;
            static unsigned int currentVBO;
            static unsigned int current2DTexture;
            static unsigned int currentProgram;

        public:
            static void GetError();
            static aFPoint PixelsToNormal(aPoint coord, int w, int h);
            static aFPoint TexelsToNormal(aPoint coord, int w, int h);
            static aFColor NormilizeColor(aColor color);
            static void GenArrayBuffer(unsigned int &name, GLenum mode, GLsizeiptr size, void* data = NULL);
            static void GenVertexArray(unsigned int &name);
            static void Bind2DTexture(unsigned int name);
            static void BindVAO(unsigned int name);
            static void BindVBO(unsigned int name);
            static void UseProgram(unsigned int name);
            static void UseProgram(string name);
            static void Set1i(string name, int x);
            static void Set4i(string name, int x, int y, int z, int w);
            static void Set4f(string name, float x, float y, float z, float w);
    };

    class Shader{
        private:
            unsigned int ID;

        public:
            Shader();

        public:
            void Use();

            void Load(string vpath, string fpath);

            bool GetError(int proc, Uint32 type);

            void SetInt1(string name, int i);
            void SetFloat4(string name, float x, float y, float z, float w);
    };

    extern Shader* controlShader;
    extern Shader* textureShader; 
    extern Shader* colorShader;
}

#endif