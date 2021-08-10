#include <application.h>

namespace AbyssCore{
    bool Application::isRunning;
    SDL_Window* Application::window;
    IWindowsGroup* Application::group;
    thread* Application::render;
    SDL_GLContext Application::glContext;
    unsigned int Application::globalVAO;
    unsigned int Application::globalVBO;
    unsigned int Application::framebuffer;
    unsigned int Application::framebufferTexture;

    bool Application::Init(){
        if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
            return false;

        if(TTF_Init() != 0)
            return false;

        if(!(IMG_Init(TEXTURE_FLAGS) & TEXTURE_FLAGS)){
            return false;
        }

        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        if(!CreateSDLWindow())
            return false;

        group = new SystemGroup();
        // SDL_ShowCursor(SDL_DISABLE);

        return true;
    }

    void Application::Start(){
        isRunning = true;

        if(group->CurrentFocus() == NULL){
            Window* mw = new MainWindow();

            mw->SetPos(0, 0);
            mw->SetSize(RESOLUTION_X, RESOLUTION_Y - HEADER_HEIGHT);

            mw->SetVisible(true);
            group->FocusWindow(mw);
            group->Create(mw, "Main window");
        }

        render = new thread(Render);

        while(isRunning){
            Input();
        }

        Dispose();
    }

    void Application::Dispose(){
        isRunning = false;

        DisposeWindow();

        SDL_Quit();
    }

    void Application::Input(){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    isRunning = false;
                break;
                // case SDL_WINDOWEVENT:
                // {
                //     if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                //         SDL_GetWindowSize(window, &screen_width, &screen_height);
                //     }
                // }
                break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                case SDL_MOUSEWHEEL:
                    ProcessMouse(event);
                break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    ProcessKey(event);
                break;
            }
        }

        group->ProcessWindows();
        
    }

    void Application::Render(){

        if(!GLInit(glContext, window)){
            DisposeWindow();
            isRunning = false;
            return;
        }

        Resources::LoadBaseTextures();
        Resources::LoadBaseFonts();
        CreateFramebuffer();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClearStencil(0x00);

        Uint64 NOW = SDL_GetPerformanceCounter();
        Uint64 LAST = 0;

        glViewport(0, 0, screen_width, screen_height);

        while(isRunning){
            LAST = NOW;
            NOW = SDL_GetPerformanceCounter();

            Time::deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_STENCIL_BUFFER_BIT);

            // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            // unsigned int VAO, VBO, texture;

            // defaultShader->Use();

            // Vertex* rect = GLCreateRectArray(SDL_Rect({10, 10, 100, 100}), aColor({WHITE}));
            // GLBindVertices(rect, 4, VAO, VBO);

            // unsigned char data[] = {
            //     255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0,
            //     255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0,
            //     255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0,
            //     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
            // };

            // glGenTextures(1, &texture);
            // GLBind2DTexture(texture);

            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 4, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            // GLGenerateMipmap(GL_TEXTURE_2D);

            // glDrawArrays(GL_QUADS, 0, 4);
            // GLUnbindVertices(VAO, VBO);

            // GLBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

            // glClearColor(1.0f, 0.8f, 0.8f, 1.0f);

            // glClear(GL_COLOR_BUFFER_BIT);

            // colorShader->Use();

            // glViewport(0, 0, screen_width, screen_height);

            // GLBindVertices(GLCreateRectArray(SDL_Rect({10, 10, 100, 100}), aColor({RED})), 4, globalVAO, globalVBO);
            // glDrawArrays(GL_QUADS, 0, 4);
            // GLUnbindVertices(globalVAO, globalVBO);

            // GLBindFramebuffer(GL_FRAMEBUFFER, 0);

            // glViewport(0, 0, screen_width, screen_height);

            // glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            // glClear(GL_COLOR_BUFFER_BIT);

            // textureShader->Use();

            // textureShader->SetInt1(AString("flip"), 1);

            // GLBind2DTexture(testTexture);

            // GLBindVertices(GLCreateRectArray(SDL_Rect({0, 0, 360, 360}), aColor({WHITE})), 4, globalVAO, globalVBO);
            // glDrawArrays(GL_QUADS, 0, 4);
            // GLUnbindVertices(globalVAO, globalVBO);

            // colorShader->Use();

            // GLBindVertices(GLCreateRectArray(SDL_Rect({10, 10, 100, 100}), aColor({BLACK})), 4, globalVAO, globalVBO);
            // glDrawArrays(GL_QUADS, 0, 4);
            // GLUnbindVertices(globalVAO, globalVBO);

            for(Window* w : group->GetPull()){
                if(w->IsVisible()){
                    DrawWindow(w);
                }
            }

            SDL_GL_SwapWindow(window);
        }

        Resources::FreeResources();

        GLDeleteFramebuffers(1, &framebuffer);
        glDeleteTextures(1, &framebufferTexture);
    }

    void Application::CreateFramebuffer(){
        GLGenFramebuffers(1, &framebuffer);
        GLBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        glGenTextures(1, &framebufferTexture);
        glBindTexture(GL_TEXTURE_2D, framebufferTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screen_width, screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glBindTexture(GL_TEXTURE_2D, 0);

        GLFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

        glMatrixMode(GL_PROJECTION);
        glMatrixMode(GL_MODELVIEW);

        if(GLCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            printf("Framebuffer not done!\n");
        
        GLBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Application::DrawWindow(Window* w){
        SDL_Rect rect = w->GetRect();

        int width = rect.w;
        int height = rect.h;

        // rect.w += w->style.shadow_size;
        // rect.h += w->style.shadow_size;

        if(w->IsMinimized())
            rect.h -= height;

        if(w->IsFull())
            rect.h += HEADER_HEIGHT;

        if(w->IsFull())
            DrawWindowHead(w);
        if(!w->IsMinimized())
            DrawWindowBody(w);
        if(w->IsFull())
            DrawWindowControl(w);
    }

    void Application::DrawWindowHead(Window* w){
        SDL_Rect rect = w->GetRect();
        rect.h = HEADER_HEIGHT;

        aFColor focus = GLConvertColor(w->style.focus);
        aFColor nofocus = GLConvertColor(w->style.nofocus);

        aFColor border = GLConvertColor(w->style.border);

        colorShader->Use();

        Vertex* headRectArray = GLCreateRectArray(rect, aColor({WHITE}));
        GLCreateVertexObjects(headRectArray, 4, globalVAO, globalVBO);

        colorShader->SetInt1("useVertexColor", 0);

        if(group->CurrentFocus() == w)
            colorShader->SetFloat4("color", focus.r, focus.g, focus.b, focus.a);
        else
            colorShader->SetFloat4("color", nofocus.r, nofocus.g, nofocus.b, nofocus.a);

        GLBindVertexArray(globalVAO);

        glDrawArrays(GL_QUADS, 0, 4);

        unsigned int textVAO, textVBO;

        Texture text = Resources::CreateStringTexture(w->GetTitle(), "arial15", 200);

        GLCreateVertexObjects(GLCreateRectArray(SDL_Rect({rect.x + 10, rect.y + 10, text.width, text.height}), aColor({WHITE})), 4, textVAO, textVBO);

        GLBind2DTexture(text.id);

        GLBindVertexArray(textVAO);

        textureShader->Use();
        textureShader->SetInt1("flip", 1);

        glDrawArrays(GL_QUADS, 0, 4);

        GLDestroyVertexObjects(textVAO, textVBO);

        GLBindVertexArray(globalVAO);

        colorShader->Use();

        colorShader->SetFloat4("color", border.r, border.g, border.b, border.a);

        glDrawArrays(GL_LINE_LOOP, 0, 4);

        GLDestroyVertexObjects(globalVAO, globalVBO);
    }

    void Application::DrawWindowBody(Window* w){
        SDL_Rect rect = w->GetRect();

        if(w->IsFull())
            rect.y += HEADER_HEIGHT;

        aFColor border = GLConvertColor(w->style.border);

        colorShader->Use();

        colorShader->SetInt1("useVertexColor", 0);

        GLCreateVertexObjects(GLCreateRectArray(rect, aColor({WHITE})), 4, globalVAO, globalVBO);

        glEnable(GL_STENCIL_TEST);

        glStencilOp(GL_REPLACE, GL_KEEP, GL_INCR);
        glStencilMask(0xFF);

        glStencilFunc(GL_NEVER, 1, 0xFF);
        
        colorShader->SetFloat4("color", 1, 1, 1, 1);
        GLBindVertexArray(globalVAO);

        glDrawArrays(GL_QUADS, 0, 4);

        glStencilFunc(GL_EQUAL, 1, 0xFF);
        glStencilMask(0);

        Anchor anchor = {rect.x, rect.y, rect.w, rect.h};
        w->Paint(anchor);

        unsigned int wVAO, wVBO;

        for(Widget * wg : w->GetPull()){
            if(wg->IsVisible() && wg->GetRect().x <= w->GetRect().w && wg->GetRect().y <= w->GetRect().h){
                glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
                glStencilFunc(GL_EQUAL, 1, 0xFF);
                glStencilMask(0xFF);

                SDL_Rect wrect = wg->GetRect();
                wrect.x += rect.x;
                wrect.y += rect.y;

                GLCreateVertexObjects(GLCreateRectArray(wrect, aColor({WHITE})), 4, wVAO, wVBO);

                colorShader->Use();
                colorShader->SetInt1("useVertexColor", 1);

                GLBindVertexArray(wVAO);

                glDrawArrays(GL_QUADS, 0, 4);

                glStencilFunc(GL_EQUAL, 2, 0xFF);
                glStencilMask(0);

                Anchor anchor = {wrect.x, wrect.y, wrect.w, wrect.h};

                wg->Paint(anchor);

                glStencilOp(GL_DECR, GL_KEEP, GL_KEEP);
                glStencilFunc(GL_LESS, 2, 0xFF);
                glStencilMask(0xFF);

                GLBindVertexArray(wVAO);
                glDrawArrays(GL_QUADS, 0, 4);

                glStencilFunc(GL_EQUAL, 1, 0xFF);
                glStencilMask(0x00);

                aFColor border = GLConvertColor(wg->style.border);

                colorShader->Use();
                colorShader->SetInt1("useVertexColor", 0);
                colorShader->SetFloat4("color", border.r, border.g, border.b, border.a);

                GLBindVertexArray(wVAO);
                glDrawArrays(GL_LINE_LOOP, 0, 4);

                GLDestroyVertexObjects(wVAO, wVBO);
            }
        }

        glDisable(GL_STENCIL_TEST);
        glStencilMask(0xFF);

        colorShader->SetInt1("useVertexColor", 0);
        colorShader->SetFloat4("color", border.r, border.g, border.b, border.a);

        GLBindVertexArray(globalVAO);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        GLDestroyVertexObjects(globalVAO, globalVBO);

        glClear(GL_STENCIL_BUFFER_BIT);
    }

    void Application::DrawWindowControl(Window* w){
        SDL_Rect wRect = w->GetRect();

        SDL_Rect closeHitBox = w->GetCloseHitBox();
        SDL_Rect minimazeHitBox = w->GetMinimizeHitBox();
        SDL_Rect resizeHitBox = w->GetResizeHitBox();

        SDL_Rect crossRect = {wRect.x + closeHitBox.x, wRect.y + closeHitBox.y, closeHitBox.w, closeHitBox.h};
        SDL_Rect minRect = {wRect.x + minimazeHitBox.x - 1, wRect.y + minimazeHitBox.y, minimazeHitBox.w, minimazeHitBox.h};
        SDL_Rect resRect = {wRect.x + resizeHitBox.x - 1, wRect.y + resizeHitBox.y - 1, resizeHitBox.w, resizeHitBox.h};
        SDL_Rect rects[2] = {crossRect, minRect};

        aColor control = w->style.control;
        aColor border = w->style.border;
        aFColor enabled = GLConvertColor(w->style.enabled);
        aFColor disabled = GLConvertColor(w->style.disabled);

        string uniformName = "colorModificator";

        controlShader->Use();

        GLBind2DTexture(Resources::GetTexture("close").id);

        if(w->CanClose())
            controlShader->SetFloat4(uniformName, enabled.r, enabled.g, enabled.b, enabled.a);
        else
            controlShader->SetFloat4(uniformName, disabled.r, disabled.g, disabled.b, disabled.a);

        GLCreateVertexObjects(GLCreateRectArray(rects[0], control), 4, globalVAO, globalVBO);

        GLBindVertexArray(globalVAO);
        glDrawArrays(GL_QUADS, 0, 4);

        colorShader->Use();

        colorShader->SetInt1("useVertexColor", 0);
        colorShader->SetFloat4("color", border.r, border.g, border.b, border.a);

        glDrawArrays(GL_LINE_LOOP, 0, 4);
        GLDestroyVertexObjects(globalVAO, globalVBO);

        controlShader->Use();

        GLBind2DTexture(Resources::GetTexture("minimize").id);

        if(w->CanMinimize())
            controlShader->SetFloat4(uniformName, enabled.r, enabled.g, enabled.b, enabled.a);
        else
            controlShader->SetFloat4(uniformName, disabled.r, disabled.g, disabled.b, disabled.a);

        GLCreateVertexObjects(GLCreateRectArray(rects[1], control), 4, globalVAO, globalVBO);
        
        GLBindVertexArray(globalVAO);
        glDrawArrays(GL_QUADS, 0, 4);

        colorShader->Use();

        glDrawArrays(GL_LINE_LOOP, 0, 4);
        GLDestroyVertexObjects(globalVAO, globalVBO);

        if(!w->IsMinimized() && w->CanResize()){
            controlShader->Use();

            controlShader->SetFloat4(uniformName, enabled.r, enabled.g, enabled.b, enabled.a);

            GLBind2DTexture(Resources::GetTexture("resize").id);

            GLCreateVertexObjects(GLCreateRectArray(resRect, control), 4, globalVAO, globalVBO);
            GLBindVertexArray(globalVAO);
            glDrawArrays(GL_QUADS, 0, 4);
            GLDestroyVertexObjects(globalVAO, globalVBO);
        }
    }

    void Application::ProcessKey(SDL_Event event){
        Window* focus = group->CurrentFocus();
        if(focus != NULL){
            if(event.key.state == SDL_PRESSED){
                focus->OnKeyPressed(event.key);
            }
            if(event.key.state == SDL_RELEASED){
                focus->OnKeyReleased(event.key);
            }
        }
    }

    void Application::ProcessMouse(SDL_Event event){
        switch(event.type){
            case SDL_MOUSEBUTTONDOWN:
                OnMouseDown(event.button);
            break;
            case SDL_MOUSEBUTTONUP:
                OnMouseUp(event.button);
            break;
            case SDL_MOUSEMOTION:
                OnMouseMove(event.motion);
            break;
            case SDL_MOUSEWHEEL:
                aPoint pos;
                SDL_GetMouseState(&pos.x, &pos.y);
                OnMouseWheel(event.wheel, pos);
            break;
        }
    }

    void Application::OnMouseDown(SDL_MouseButtonEvent event){
        int x = event.x;
        int y = event.y;

        bool inWindow = false;

        for(Window* w : group->GetInvertedPull()){
            if(w->IsVisible()){
                if(WindowHit(w, x, y)){
                    if(w != group->CurrentFocus())
                        group->FocusWindow(w);
                    inWindow = true;
                    break;
                }
            }
        }

        Window* focus = group->CurrentFocus();
        if(focus != NULL)
            focus->OnMouseDown(event);
    }

    void Application::OnMouseUp(SDL_MouseButtonEvent event){
        Window* focus = group->CurrentFocus();
        if(focus != NULL)
            focus->OnMouseUp(event);
    }

    void Application::OnMouseMove(SDL_MouseMotionEvent event){
        Window* focus = group->CurrentFocus();
        if(focus != NULL)
            focus->OnMouseMove(event);
    }

    void Application::OnMouseWheel(SDL_MouseWheelEvent event, aPoint pos){
        Window* focus = group->CurrentFocus();
        if(focus != NULL)
            focus->OnMouseWheel(event, pos);
    }

    IWindowsGroup* Application::GetGroup(){
        return group;
    }

    bool Application::IsRunning(){
        return isRunning;
    }

    void Application::Stop(){
        isRunning = false;
    }

    bool Application::WindowHit(Window* w, int x, int y){
        SDL_Rect rect = w->GetRect();
        int left = rect.x;
        int right = rect.x + rect.w;
        int top = rect.y;
        int bottom = rect.y + rect.h + HEADER_HEIGHT;

        if(w->IsMinimized()){
            if(w->IsFull())
                bottom = rect.y + HEADER_HEIGHT;
            else
                bottom = rect.y;
        }else{
            if(w->IsFull())
                bottom = rect.y + rect.h + HEADER_HEIGHT;
            else
                bottom = rect.y + rect.h;
        }


        if(x > left && x < right && y > top && y < bottom)
            return true;

        return false;
    }

    bool Application::CreateSDLWindow(){
        window = SDL_CreateWindow(
            "AbyssVision", 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            RESOLUTION_X, 
            RESOLUTION_Y, 
            WINDOW_FLAGS
        );

        if(!window)
            return false;
        return true;
    }

    void Application::DisposeWindow(){
        if(window){
            SDL_DestroyWindow(window);
        }
    }
}