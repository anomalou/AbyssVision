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
#include <colors.h>
#include <wparams.h>
#include <agl.h>
#include <aparams.h>
#include <timeparams.h>
#include <resources.h>
#include <renderer.h>
#include <gamecore.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#define VERTEX_SIZE sizeof(float) * 22

using namespace std;
using namespace glm;

namespace MediumCore{
    class Application{
        private:
            static SDL_Window* window;

            static IWindowsGroup* group;

            static thread* render;

            static SDL_GLContext glContext;

            static float defaultNormilizedWidth;
            static float defaultNormilizedHeight;

            static unsigned int defaultVAO;
            static unsigned int defaultVBO;
            static unsigned int instancedVBO;

            static unsigned int framebuffer;
            static unsigned int framebufferTexture;

        public:
            static int fps;

        private:
            static bool CreateSDLWindow();
            static void DisposeWindow();

            static void DrawGameScene();
            static void DrawWindows();

            static void CreateDefaultBuffers();

            static void DrawWindowHead(Window* w);
            static void DrawWindowBody(Window* w);
            static void DrawWindowControl(Window* w);

            static void ProcessKey(SDL_Event event);

            static void ProcessMouse(SDL_Event event);
            static void OnMouseDown(SDL_MouseButtonEvent event);
            static void OnMouseUp(SDL_MouseButtonEvent event);
            static void OnMouseMove(SDL_MouseMotionEvent event);
            static void OnMouseWheel(SDL_MouseWheelEvent event, aPoint pos);

            static bool WindowHit(Window* w, int x, int y);

            static void Input();
            static void Render();
            static void RenderRects(Renderer renderer);
            static void RenderSprites(Renderer renderer);
            static void RenderText(Renderer renderer);

            static void CreateFramebuffer();

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