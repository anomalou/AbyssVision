#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <windowsgroup.h>
#include <systemgroup.h>
#include <window.h>
#include <mainwindow.h>
#include <astring.h>
#include <colors.h>
#include <windowproperty.h>

#define RESOLUTION_X 1280
#define RESOLUTION_Y 640

#define RENDERER_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

#define FPS10 10
#define FPS30 30
#define FPS60 60
#define FPS120 120
#define FPSINF 1000

#define FPS FPS60

namespace AbyssCore{
    class Core{
        private:
            bool isRunning;

            SDL_Window* window;
            SDL_Renderer* renderer;

            SDL_Thread* renderThread;

            IWindowsGroup* group;

            static Core* INSTANCE;

        public:
            Core();
            static Core* GetInstance();
            ~Core();

        private:
            bool CreateWindow();
            bool CreateRenderer();
            void DisposeWindow();
            void DisposeRenderer();

            void DrawWindow(SDL_Renderer* render, Window* w);

            void DrawWindowHead(SDL_Renderer *render, Window* w);
            void DrawWindowBody(SDL_Renderer* render, Window* w);
            void DrawWindowControl(SDL_Renderer* render, Window* w);

            void ProcessMouse(SDL_Event event);
            void MoveMouse(SDL_Event event);
            void DragMouse(SDL_Event event);
            void ClickMouse(SDL_Event event);

            bool InWindow(Window* w, int x, int y);

            void Input();
            static int Render(void *rendPtr);

        public:
            bool Init();
            void Start();
            void Dispose();

            IWindowsGroup* GetGroup();
            bool IsRunning();
    };

    typedef struct{
        Core* corePtr;
    }RenderPtrs;

    static TTF_Font* font;

    bool InitCore();
    void StartCore();
    void DisposeCore();
    void OpenFont(const char* filePath);
}

#endif