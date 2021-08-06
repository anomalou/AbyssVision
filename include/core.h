#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <algorithm>
#include <thread>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include <SDL_ttf.h>
#include <windowsgroup.h>
#include <systemgroup.h>
#include <window.h>
#include <mainwindow.h>
#include <astring.h>
#include <colors.h>
#include <wparams.h>
#include <agl.h>
#include <application.h>

using namespace std;

namespace AbyssCore{
    class Core{
        private:
            static bool isRunning;

            static SDL_Window* window;

            static IWindowsGroup* group;

            static thread* render;

            static bool isResized;

            static SDL_GLContext glContext;

            static unsigned int windowfb;
            static unsigned int widgetfb;
            static unsigned int windowTex;
            static unsigned int widgetTex;
            static unsigned int windowStencil;
            static unsigned int widgetStencil;

        private:
            static bool CreateSDLWindow();
            static void DisposeWindow();

            static void DrawWindow(Window* w);

            static void DrawWindowHead(Window* w);
            static void DrawWindowBody(Window* w);
            static void DrawWindowControl(Window* w);

            static void ProcessMouse(SDL_Event event);
            static void OnMouseDown(SDL_MouseButtonEvent event);
            static void OnMouseUp(SDL_MouseButtonEvent event);
            static void OnMouseMove(SDL_MouseMotionEvent event);
            static void OnMouseWheel(SDL_MouseWheelEvent event, aPoint pos);

            // static void MoveMouse(SDL_Event event);
            // static void DragMouse(SDL_Event event);
            // static void ProcessClick(Window* w, SDL_MouseButtonEvent event);
            // static void ClickMouse(SDL_Event event);

            static bool WindowHit(Window* w, int x, int y);

            static void Input();
            static void Render();
            static bool CreateFrameBuffer(unsigned int &framebuffer, unsigned int &texColorBuffer, unsigned int &stencilBuffer);

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