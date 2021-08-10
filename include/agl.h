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
    extern PFNGLUNIFORM1IPROC GLUniform1i;
    extern PFNGLUNIFORM1FPROC GLUniform1f;
    extern PFNGLUNIFORM4FPROC GLUniform4f;
    extern PFNGLGETUNIFORMLOCATIONPROC GLGetUniformLocation;
    extern PFNGLGENVERTEXARRAYSPROC GLGenVertexArrays;
    extern PFNGLDELETEVERTEXARRAYSPROC GLDeleteVertexArrays;
    extern PFNGLGENBUFFERSPROC GLGenBuffers;
    extern PFNGLDELETEBUFFERSPROC GLDeleteBuffers;
    extern PFNGLBINDVERTEXARRAYPROC GLBindVertexArray;
    extern PFNGLBINDBUFFERPROC GLBindBuffer;
    extern PFNGLBUFFERDATAPROC GLBufferData;
    extern PFNGLBUFFERSUBDATAPROC GLBufferSubData;
    extern PFNGLVERTEXATTRIBPOINTERPROC GLVertexAttribPointer;
    extern PFNGLENABLEVERTEXATTRIBARRAYPROC GLEnableVertexAttribArray;
    extern PFNGLGENFRAMEBUFFERSPROC GLGenFramebuffers;
    extern PFNGLDELETEFRAMEBUFFERSPROC GLDeleteFramebuffers;
    extern PFNGLBINDFRAMEBUFFERPROC GLBindFramebuffer;
    extern PFNGLFRAMEBUFFERTEXTURE2DPROC GLFramebufferTexture2D;
    extern PFNGLGENRENDERBUFFERSPROC GLGenRenderbuffers;
    extern PFNGLBINDRENDERBUFFERPROC GLBindRenderbuffer;
    extern PFNGLRENDERBUFFERSTORAGEPROC GLRenderbufferStorage;
    extern PFNGLFRAMEBUFFERRENDERBUFFERPROC GLFramebufferRenderbuffer;
    extern PFNGLCHECKFRAMEBUFFERSTATUSPROC GLCheckFramebufferStatus;
    extern PFNGLGENERATEMIPMAPPROC GLGenerateMipmap;

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