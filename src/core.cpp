#include "core.h"

namespace AbyssCore{
    bool Core::isRunning;
    SDL_Window* Core::window;
    IWindowsGroup* Core::group;
    thread* Core::render;
    bool Core::isResized;
    SDL_GLContext Core::glContext;
    unsigned int Core::windowfb;
    unsigned int Core::widgetfb;
    unsigned int Core::windowTex;
    unsigned int Core::widgetTex;
    unsigned int Core::windowStencil;
    unsigned int Core::widgetStencil;

    bool Core::Init(){
        if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
            return false;

        if(TTF_Init() != 0)
            return false;

        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        if(!CreateSDLWindow())
            return false;

        group = new SystemGroup();
        // SDL_ShowCursor(SDL_DISABLE);

        return true;
    }

    void Core::Start(){
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

    void Core::Dispose(){
        isRunning = false;

        DisposeWindow();

        SDL_Quit();
    }

    void Core::Input(){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    isRunning = false;
                break;
                case SDL_WINDOWEVENT:
                {
                    if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                        SDL_GetWindowSize(window, &Application::screen_width, &Application::screen_height);
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

    void Core::Render(){

        if(!GLInit(glContext, window)){
            DisposeWindow();
            isRunning = false;
            return;
        }

        isResized = true;

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClearStencil(0x00);

        while(isRunning){
            if(isResized){
                glViewport(0, 0, Application::screen_width, Application::screen_height);
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
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_STENCIL_BUFFER_BIT);

            // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            // unsigned int VAO, VBO;

            // GLBindFrameBuffer(windowfb);

            // glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
            // glClear(GL_COLOR_BUFFER_BIT);

            // glBegin(GL_QUADS);
            // GLGetError();

            // glColor3f(1.0, 0, 0);
            // GLGetError();

            // glVertex2f(-0.5, -0.5);
            // GLGetError();
            // glVertex2f(-0.5, 0.5);
            // GLGetError();
            // glVertex2f(0.5, 0.5);
            // GLGetError();
            // glVertex2f(0.5, -0.5);
            // GLGetError();

            // glEnd();
            // GLGetError();

            // defaultShader->Use();

            // GLBind2DRect(SDL_Rect({10, 10, 100, 100}), aColor({RED}), VAO, VBO);
            // GLGetError();
            // GLDraw2DVertices(GL_QUADS, 4);
            // GLGetError();

            // GLUnbindVertices(VAO, VBO);
            // GLGetError();

            // GLUseProgram(0);
            // GLBindFrameBuffer(0);

            // glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

            // // glClear(GL_COLOR_BUFFER_BIT);

            // clearShader->Use();
            // GLBind2DRectTex(SDL_Rect({0, 0, Application::screen_width, Application::screen_height}), VAO, VBO);
            // GLBind2DTexture(windowTex);
            // GLDraw2DVertices(GL_QUADS, 4);

            // GLUnbindVertices(VAO, VBO);

            for(Window* w : group->GetPull()){
                if(w->IsVisible()){
                    DrawWindow(w);
                }
            }


            // SDL_FRect frect = ConvertToNormal(screen_width, screen_height, rect);

            // glBegin(GL_LINE_LOOP);

            //     glVertex2f(frect.x, frect.y - frect.h);
            //     glVertex2f(frect.x, frect.y);
            //     glVertex2f(frect.x + frect.w, frect.y);
            //     glVertex2f(frect.x + frect.w, frect.y - frect.h);

            // glEnd();

            SDL_GL_SwapWindow(window);
        }
    }

    bool Core::CreateFrameBuffer(unsigned int &framebuffer, unsigned int &texColorBuffer, unsigned int &stencilBuffer){
        GLGenFramebuffers(1, &framebuffer);

        GLBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        int width = Application::screen_width;
        int height = Application::screen_height;
        
        glGenTextures(1, &texColorBuffer);
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);

        GLFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

        GLGenRenderbuffers(1, &stencilBuffer);
        GLBindRenderbuffer(GL_RENDERBUFFER, stencilBuffer);
        GLRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        GLBindRenderbuffer(GL_RENDERBUFFER, 0);

        GLFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, stencilBuffer);

        if(GLCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
            printf("Framebuffer not done!\n");
            return false;
        }
        GLBindFrameBuffer(0);

        return true;
    }

    void Core::DrawWindow(Window* w){
        SDL_Rect rect = w->GetRect();

        int width = rect.w;
        int height = rect.h;

        // rect.w += w->style.shadow_size;
        // rect.h += w->style.shadow_size;

        if(w->IsMinimized())
            rect.h -= height;

        if(w->IsFull())
            rect.h += HEADER_HEIGHT;

        // SDL_Texture* windowTexture = SDL_CreateTexture(render, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
        // SDL_SetRenderTarget(render, windowTexture);
        // SDL_SetTextureBlendMode(windowTexture, SDL_BlendMode::SDL_BLENDMODE_BLEND);

        if(w->IsFull())
            DrawWindowHead(w);
        if(!w->IsMinimized())
            DrawWindowBody(w);
        if(w->IsFull())
            DrawWindowControl(w);

        // GLBind2DRect(SDL_Rect({0, 0, Application::screen_width, Application::screen_height}), aColor({WHITE}));
        // GLBind2DTexture(windowTex);
        // GLDraw2DVertices(GL_QUADS, 4);

        // SDL_SetRenderTarget(render, NULL);
        // SDL_RenderCopy(render, windowTexture, NULL, &rect);
        // SDL_DestroyTexture(windowTexture);
    }

    void Core::DrawWindowHead(Window* w){
        // int x = 0;
        // int y = 0;
        // int width = w->GetRect().w;
        // int height = HEADER_HEIGHT;
        SDL_Rect rect = w->GetRect();
        rect.h = HEADER_HEIGHT;

        aColor focus = w->style.focus;
        aColor nofocus = w->style.nofocus;

        aColor border = w->style.border;

        clearShader->Use();

        if(group->CurrentFocus() == w)
            GLFill2DRect(rect, focus);
        else
            GLFill2DRect(rect, nofocus);

        defaultShader->Use();

        GLDraw2DRect(rect, border);

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

    void Core::DrawWindowBody(Window* w){
        SDL_Rect rect = w->GetRect();

        if(w->IsFull())
            rect.y += HEADER_HEIGHT;

        aColor border = w->style.border;

        clearShader->Use();

        glEnable(GL_STENCIL_TEST);

        glStencilOp(GL_REPLACE, GL_KEEP, GL_INCR);
        glStencilMask(0xFF);

        glStencilFunc(GL_NEVER, 1, 0xFF);

        GLFill2DRect(rect, aColor({WHITE}));

        glStencilFunc(GL_EQUAL, 1, 0xFF);
        glStencilMask(0);

        Anchor anchor = {rect.x, rect.y, rect.w, rect.h};
        w->Paint(anchor);

        for(Widget * wg : w->GetPull()){
            if(wg->IsVisible() && wg->GetRect().x <= w->GetRect().w && wg->GetRect().y <= w->GetRect().h){
                glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
                glStencilFunc(GL_EQUAL, 1, 0xFF);
                glStencilMask(0xFF);

                SDL_Rect wrect = wg->GetRect();
                wrect.x += rect.x;
                wrect.y += rect.y;

                SDL_Rect mrect = wrect;
                mrect.w -= 1;
                mrect.h -= 1;

                GLFill2DRect(mrect, aColor({BLACK}));

                glStencilFunc(GL_EQUAL, 2, 0xFF);
                glStencilMask(0);

                Anchor anchor = {wrect.x, wrect.y, wrect.w, wrect.h};

                wg->Paint(anchor);

                aColor border = wg->style.border;

                clearShader->Use();

                glStencilFunc(GL_EQUAL, 1, 0xFF);
                GLDraw2DRect(wrect, border);

                glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
                glStencilFunc(GL_NEVER, 1, 0xFF);
                glStencilMask(0xFF);

                GLFill2DRect(mrect, aColor({WHITE}));
            }
        }

        glDisable(GL_STENCIL_TEST);
        glStencilMask(0xFF);

        defaultShader->Use();

        GLDraw2DRect(rect, border);

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

    void Core::DrawWindowControl(Window* w){
        SDL_Rect wRect = w->GetRect();

        SDL_Rect closeHitBox = w->GetCloseHitBox();
        SDL_Rect minimazeHitBox = w->GetMinimizeHitBox();
        SDL_Rect resizeHitBox = w->GetResizeHitBox();

        SDL_Rect crossRect = {wRect.x + closeHitBox.x, wRect.y + closeHitBox.y, closeHitBox.w, closeHitBox.h};
        SDL_Rect minRect = {wRect.x + minimazeHitBox.x - 1, wRect.y + minimazeHitBox.y, minimazeHitBox.w, minimazeHitBox.h};
        SDL_Rect resRect = {wRect.x + resizeHitBox.x, wRect.y + resizeHitBox.y, resizeHitBox.w, resizeHitBox.h};
        SDL_Rect rects[2] = {crossRect, minRect};

        aColor control = w->style.control;
        aColor border = w->style.border;
        aColor enabled = w->style.enabled;
        aColor disabled = w->style.disabled;

        clearShader->Use();

        GLFill2DRect(rects[0], control);
        GLFill2DRect(rects[1], control);

        defaultShader->Use();

        GLDraw2DRect(rects[0], border);
        GLDraw2DRect(rects[1], border);

        if(!w->IsMinimized() && w->CanResize()){
            GLDraw2DRect(resRect, border);
        }
    }

    void Core::ProcessMouse(SDL_Event event){
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
                OnMouseWheel(event.wheel);
            break;
        }
    }

    void Core::OnMouseDown(SDL_MouseButtonEvent event){
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

        group->CurrentFocus()->OnMouseDown(event);
    }

    void Core::OnMouseUp(SDL_MouseButtonEvent event){
        group->CurrentFocus()->OnMouseUp(event);
    }

    void Core::OnMouseMove(SDL_MouseMotionEvent event){
        group->CurrentFocus()->OnMouseMove(event);
    }

    void Core::OnMouseWheel(SDL_MouseWheelEvent event){
        group->CurrentFocus()->OnMouseWheel(event);
    }

    // void Core::MoveMouse(SDL_Event event){
    //     Window* currentFocus = group->CurrentFocus();

    //     int x = event.motion.x;
    //     int y = event.motion.y;

    //     Application::mousePosition = {x, y};

    //     if(currentFocus->IsVisible()){
    //         currentFocus->ProcessGlobalMove(event.motion);
    //     }

    //     if(InWindow(currentFocus, x, y) && currentFocus->IsVisible()){
    //         event.motion.x -= currentFocus->GetRect().x;
    //         event.motion.y -= currentFocus->GetRect().y;

    //         currentFocus->ProcessMove(event.motion);
    //     }
    // }

    // void Core::DragMouse(SDL_Event event){
    //     Window* currentFocus = group->CurrentFocus();

    //     int x = event.motion.x;
    //     int y = event.motion.y;

    //     Application::mousePosition = {x, y};

    //     if(currentFocus->IsVisible()){
    //         currentFocus->ProcessGlobalDrag(event.motion);
    //     }

    //     if(InWindow(currentFocus, x, y) && currentFocus->IsVisible()){
    //         event.motion.x -= currentFocus->GetRect().x;
    //         event.motion.y -= currentFocus->GetRect().y;

    //         currentFocus->ProcessDrag(event.motion);
    //     }        
    // }

    // void Core::ProcessClick(Window* w, SDL_MouseButtonEvent event){
    //     if(w != group->CurrentFocus()){
    //         group->FocusWindow(w);
    //     }

    //     w->ProcessGlobalClick(event);

    //     event.x -= w->GetRect().x;
    //     event.y -= w->GetRect().y;

    //     w->ProcessClick(event);
    // }

    // void Core::ClickMouse(SDL_Event event){
    //     int x = event.button.x;
    //     int y = event.button.y;

    //     vector<Window*> windowPull = group->GetPull();
    //     vector<Window*> invertPull = vector<Window*>();

    //     while(windowPull.size() != 0){
    //         invertPull.push_back(windowPull.back());
    //         windowPull.pop_back();
    //     }

    //     for(Window* w : invertPull){
    //         if(w->IsVisible() && w != group->Background()){
    //             if(InWindow(w, x, y)){
    //                 ProcessClick(w, event.button);
    //                 return;
    //             }
    //         }
    //     }

    //     if(group->Background() != NULL){
    //         if(InWindow(group->Background(), x, y)){
    //             ProcessClick(group->Background(), event.button);
    //         }
    //     }
    // }

    IWindowsGroup* Core::GetGroup(){
        return group;
    }

    bool Core::IsRunning(){
        return isRunning;
    }

    void Core::Stop(){
        isRunning = false;
    }

    bool Core::WindowHit(Window* w, int x, int y){
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

    bool Core::CreateSDLWindow(){
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

    void Core::DisposeWindow(){
        if(window){
            SDL_DestroyWindow(window);
        }
    }
}

