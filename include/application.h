#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <algorithm>
#include <thread>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <GL/glu.h>
#include <windowsgroup.h>
#include <systemgroup.h>
#include <window.h>
#include <mainwindow.h>
#include <astring.h>
#include <colors.h>
#include <wparams.h>
#include <agl.h>
#include <aparams.h>

using namespace std;

namespace AbyssCore{
    class Application{
        private:
            static bool isRunning;

            static SDL_Window* window;

            static IWindowsGroup* group;

            static thread* render;

            static bool isResized;

            static SDL_GLContext glContext;

            static unsigned int globalVAO;
            static unsigned int globalVBO;

            static unsigned int closeTexture;
            static unsigned int minimizeTexture;
            static unsigned int resizeTexture;

            static unsigned int framebuffer;
            static unsigned int framebufferTexture;

        public:
            static unsigned int ozzen;

        private:
            static bool CreateSDLWindow();
            static void DisposeWindow();

            static void DrawWindow(Window* w);

            static void DrawWindowHead(Window* w);
            static void DrawWindowBody(Window* w);
            static void CreateWindowControlTextures();
            static void DrawWindowControl(Window* w);

            static void ProcessMouse(SDL_Event event);
            static void OnMouseDown(SDL_MouseButtonEvent event);
            static void OnMouseUp(SDL_MouseButtonEvent event);
            static void OnMouseMove(SDL_MouseMotionEvent event);
            static void OnMouseWheel(SDL_MouseWheelEvent event, aPoint pos);

            static bool WindowHit(Window* w, int x, int y);

            static void Input();
            static void Render();

            static void CreateFramebuffer();
            static SDL_Surface* LoadImage(const char* name);

        public:
            static bool Init();
            static void Start();
            static void Dispose();

            static IWindowsGroup* GetGroup();
            static bool IsRunning();

            static void Stop();
    };
}

#endif