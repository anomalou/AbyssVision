#include <application.h>

namespace AbyssCore{
    bool Application::isRunning;
    SDL_Window* Application::window;
    IWindowsGroup* Application::group;
    thread* Application::render;
    bool Application::isResized;
    SDL_GLContext Application::glContext;
    unsigned int Application::globalVAO;
    unsigned int Application::globalVBO;
    unsigned int Application::closeTexture;
    unsigned int Application::minimizeTexture;
    unsigned int Application::resizeTexture;
    unsigned int Application::framebuffer;
    unsigned int Application::framebufferTexture;

    unsigned int Application::ozzen;
    double Application::deltaTime;

    bool Application::Init(){
        if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
            return false;

        int flags = IMG_INIT_PNG;
        if(!(IMG_Init(flags) & flags)){
            return false;
        }
        // if(TTF_Init() != 0)
        //     return false;

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
            group->Create(mw, new AString("Main window"));
        }

        render = new thread(Render);

        while(isRunning){
            Input();
        }

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
                case SDL_WINDOWEVENT:
                {
                    if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                        SDL_GetWindowSize(window, &screen_width, &screen_height);
                        isResized = true;
                    }
                }
                break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                case SDL_MOUSEWHEEL:
                    ProcessMouse(event);
                break;
                case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.scancode){
                        case SDL_SCANCODE_ESCAPE:
                            isRunning = false;
                        break;
                    }
                }   
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

        isResized = true;

        CreateWindowControlTextures();
        CreateFramebuffer();

        //easter egg =)
        SDL_Surface* img = LoadImage("texture.png");

        ozzen = GLCreate2DTexture(img->pixels, img->w, img->h, GL_RGBA, GL_LINEAR);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClearStencil(0x00);

        Uint64 NOW = SDL_GetPerformanceCounter();
        Uint64 LAST = 0;

        while(isRunning){
            if(isResized){
                glViewport(0, 0, screen_width, screen_height);
                // if(!CreateFrameBuffer(windowfb, windowTex, windowStencil)){
                //     isRunning = false;
                //     return;
                // }
                // if(!CreateFrameBuffer(widgetfb, widgetTex, widgetStencil)){
                //     isRunning = false;
                //     return;
                // }

                isResized = false;
            }

            LAST = NOW;
            NOW = SDL_GetPerformanceCounter();

            deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
            
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

        glDeleteTextures(1, &closeTexture);
        glDeleteTextures(1, &minimizeTexture);
        glDeleteTextures(1, &resizeTexture);

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

    SDL_Surface* Application::LoadImage(const char* name){
        SDL_Surface* img = IMG_Load(name);

        if(img == NULL){
            printf("Cant load img!\n");
            return NULL;
        }

        

        // img = SDL_ConvertSurface(img, SDL_GetWindowSurface(window)->format, 0);

        return img;
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
        // int x = 0;
        // int y = 0;
        // int width = w->GetRect().w;
        // int height = HEADER_HEIGHT;
        SDL_Rect rect = w->GetRect();
        rect.h = HEADER_HEIGHT;

        aFColor focus = GLConvertColor(w->style.focus);
        aFColor nofocus = GLConvertColor(w->style.nofocus);

        aFColor border = GLConvertColor(w->style.border);

        colorShader->Use();

        Vertex* headRectArray = GLCreateRectArray(rect, aColor({WHITE}));
        GLCreateVertexObjects(headRectArray, 4, globalVAO, globalVBO);

        colorShader->SetInt1(AString("useVertexColor"), 0);

        if(group->CurrentFocus() == w)
            colorShader->SetFloat4(AString("color"), focus.r, focus.g, focus.b, focus.a);
        else
            colorShader->SetFloat4(AString("color"), nofocus.r, nofocus.g, nofocus.b, nofocus.a);

        GLBindVertexArray(globalVAO);

        glDrawArrays(GL_QUADS, 0, 4);

        colorShader->SetFloat4(AString("color"), border.r, border.g, border.b, border.a);

        glDrawArrays(GL_LINE_LOOP, 0, 4);

        GLDestroyVertexObjects(globalVAO, globalVBO);

        // SDL_Color shadow = w->style.shadow;
        // int shadow_size = w->style.shadow_size;

        // SDL_SetRenderDrawColor(render, shadow.r, shadow.g, shadow.b, shadow.a);
        // SDL_RenderFillRect(render, new SDL_Rect({rect.x + rect.w, rect.y + shadow_size, shadow_size, HEADER_HEIGHT}));

        // if(w->IsMinimazed())
        //     SDL_RenderFillRect(render, new SDL_Rect({rect.x + shadow_size, rect.y + HEADER_HEIGHT, rect.w - shadow_size, shadow_size}));
        
        // //window title

        // rect.x = x + FSIGN_WIDTH / 2;
        // rect.y = y + FSIGN_HEIGHT / 2;
        // rect.w = FSIGN_WIDTH * w->GetName()->Length();
        // rect.h = FSIGN_HEIGHT;

        // if((rect.w + FSIGN_WIDTH / 2) > w->GetRect().w)
        //     rect.w = w->GetRect().w - FSIGN_WIDTH / 2;

        // SDL_Color color = {BLACK};

        // SDL_Surface* surface = TTF_RenderText_Solid(font, w->GetName()->ToChars(), color);

        // SDL_Texture* header = SDL_CreateTextureFromSurface(render, surface);

        // SDL_RenderCopy(render, header, NULL, &rect);

        // SDL_FreeSurface(surface);
        // SDL_DestroyTexture(header);
    }

    void Application::DrawWindowBody(Window* w){
        SDL_Rect rect = w->GetRect();

        if(w->IsFull())
            rect.y += HEADER_HEIGHT;

        aFColor border = GLConvertColor(w->style.border);

        colorShader->Use();

        colorShader->SetInt1(AString("useVertexColor"), 0);

        GLCreateVertexObjects(GLCreateRectArray(rect, aColor({WHITE})), 4, globalVAO, globalVBO);

        glEnable(GL_STENCIL_TEST);

        glStencilOp(GL_REPLACE, GL_KEEP, GL_INCR);
        glStencilMask(0xFF);

        glStencilFunc(GL_NEVER, 1, 0xFF);
        
        colorShader->SetFloat4(AString("color"), 1, 1, 1, 1);
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
                colorShader->SetInt1(AString("useVertexColor"), 1);
                // colorShader->SetFloat4(AString("color"), 1, 1, 1, 1);

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
                colorShader->SetInt1(AString("useVertexColor"), 0);
                colorShader->SetFloat4(AString("color"), border.r, border.g, border.b, border.a);

                GLBindVertexArray(wVAO);
                glDrawArrays(GL_LINE_LOOP, 0, 4);

                // GLCreateVertexObjects(GLCreateRectArray(mrect, aColor({WHITE})), 4, globalVAO, globalVBO);
                // glDrawArrays(GL_QUADS, 0, 4);
                GLDestroyVertexObjects(wVAO, wVBO);
            }
        }

        glDisable(GL_STENCIL_TEST);
        glStencilMask(0xFF);

        colorShader->SetInt1(AString("useVertexColor"), 0);
        colorShader->SetFloat4(AString("color"), border.r, border.g, border.b, border.a);

        GLBindVertexArray(globalVAO);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        GLDestroyVertexObjects(globalVAO, globalVBO);

        glClear(GL_STENCIL_BUFFER_BIT);

        // else
        //     rect.y = 0;

        // SDL_Color border = w->GetStyle().border;
        // SDL_Texture* currTarget = SDL_GetRenderTarget(render);

        // SDL_Texture* bodyTex = SDL_CreateTexture(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
        // SDL_SetRenderTarget(render, bodyTex);
        // w->Paint(render);

        // for(Widget* w : w->GetPull()){
        //     if(w->IsVisible()){
        //         SDL_Rect wrect = w->GetRect();

        //         SDL_Texture* widgetTex = SDL_CreateTexture(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, wrect.w, wrect.h);
        //         SDL_SetRenderTarget(render, widgetTex);
        //         w->Paint(render);
        //         SDL_SetRenderTarget(render, bodyTex);
        //         SDL_RenderCopy(render, widgetTex, NULL, &wrect);
        //         SDL_DestroyTexture(widgetTex);

        //         // SDL_Color border = w->GetStyle().border;

        //         // SDL_SetRenderDrawColor(render, border.r, border.g, border.b, border.a);
        //         // SDL_RenderDrawRect(render, &wrect);
        //     }
        // }

        // SDL_SetRenderTarget(render, currTarget);
        // SDL_RenderCopy(render, bodyTex, NULL, &rect);
        // SDL_DestroyTexture(bodyTex);

        // // SDL_SetRenderDrawColor(render, border.r, border.g, border.b, border.a);
        // // SDL_RenderDrawRect(render, &rect);

        // SDL_Color shadow = w->style.shadow;
        // int shadow_size = w->style.shadow_size;

        // SDL_SetRenderDrawColor(render, shadow.r, shadow.g, shadow.b, shadow.a);
        // SDL_Rect shadows[2] = {{rect.x + shadow_size, rect.y + rect.h, rect.w - shadow_size, shadow_size},
        //                        {rect.x + rect.w, rect.y + shadow_size + 1, shadow_size, rect.h - 1}};

        // SDL_RenderFillRects(render, shadows, 2);
    }

    void Application::CreateWindowControlTextures(){
        SDL_Surface* close = LoadImage("close.png");
        SDL_Surface* minimize = LoadImage("minimize.png");
        SDL_Surface* resize = LoadImage("resize.png");

        closeTexture = GLCreate2DTexture(close->pixels, close->w, close->h, GL_RGB, GL_NEAREST);
        minimizeTexture = GLCreate2DTexture(minimize->pixels, minimize->w, minimize->h, GL_RGB, GL_LINEAR);
        resizeTexture = GLCreate2DTexture(resize->pixels, resize->w, resize->h, GL_RGB, GL_NEAREST);
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

        AString uniformName = AString("colorModificator");

        controlShader->Use();

        GLBind2DTexture(closeTexture);

        if(w->CanClose())
            controlShader->SetFloat4(uniformName, enabled.r, enabled.g, enabled.b, enabled.a);
        else
            controlShader->SetFloat4(uniformName, disabled.r, disabled.g, disabled.b, disabled.a);

        GLCreateVertexObjects(GLCreateRectArray(rects[0], control), 4, globalVAO, globalVBO);

        GLBindVertexArray(globalVAO);
        glDrawArrays(GL_QUADS, 0, 4);

        colorShader->Use();

        colorShader->SetInt1(AString("useVertexColor"), 0);
        colorShader->SetFloat4(AString("color"), border.r, border.g, border.b, border.a);

        glDrawArrays(GL_LINE_LOOP, 0, 4);
        GLDestroyVertexObjects(globalVAO, globalVBO);

        controlShader->Use();

        GLBind2DTexture(minimizeTexture);

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

            GLBind2DTexture(resizeTexture);

            GLCreateVertexObjects(GLCreateRectArray(resRect, control), 4, globalVAO, globalVBO);
            GLBindVertexArray(globalVAO);
            glDrawArrays(GL_QUADS, 0, 4);
            GLDestroyVertexObjects(globalVAO, globalVBO);
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

        // if(group->Background() != NULL && inWindow == false){
        //     if(WindowHit(group->Background(), x, y)){
        //         if(group->CurrentFocus() != group->Background()){
        //             group->FocusWindow(group->Background());
        //         }
        //     }
        // }
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