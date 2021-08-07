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
    unsigned int Application::windowfb;
    unsigned int Application::widgetfb;
    unsigned int Application::windowTex;
    unsigned int Application::widgetTex;
    unsigned int Application::windowStencil;
    unsigned int Application::widgetStencil;

    bool Application::Init(){
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

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClearStencil(0x00);

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
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_STENCIL_BUFFER_BIT);

            // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            // unsigned int VAO, VBO;

            // defaultShader->Use();

            // Vertex* rect = GLCreateRectArray(SDL_Rect({10, 10, 100, 100}), aColor({RED}));
            // GLBindVertices(rect, 4, VAO, VBO);
            // glDrawArrays(GL_QUADS, 0, 4);
            // GLUnbindVertices(VAO, VBO);


            for(Window* w : group->GetPull()){
                if(w->IsVisible()){
                    DrawWindow(w);
                }
            }

            SDL_GL_SwapWindow(window);
        }
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

        aColor focus = w->style.focus;
        aColor nofocus = w->style.nofocus;

        aColor border = w->style.border;

        clearShader->Use();

        Vertex* headFillRectArray;
        Vertex* headBorderRectArray = GLCreateRectArray(rect, border);

        if(group->CurrentFocus() == w)
            headFillRectArray = GLCreateRectArray(rect, focus);
        else
            headFillRectArray = GLCreateRectArray(rect, nofocus);

        GLBindVertices(headFillRectArray, 4, globalVAO, globalVBO);
        glDrawArrays(GL_QUADS, 0, 4);
        GLUnbindVertices(globalVAO, globalVBO);

        defaultShader->Use();

        GLBindVertices(headBorderRectArray, 4, globalVAO, globalVBO);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        GLUnbindVertices(globalVAO, globalVBO);

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

        aColor border = w->style.border;

        clearShader->Use();

        glEnable(GL_STENCIL_TEST);

        glStencilOp(GL_REPLACE, GL_KEEP, GL_INCR);
        glStencilMask(0xFF);

        glStencilFunc(GL_NEVER, 1, 0xFF);

        GLBindVertices(GLCreateRectArray(rect, aColor({WHITE})), 4, globalVAO, globalVBO);
        glDrawArrays(GL_QUADS, 0, 4);
        GLUnbindVertices(globalVAO, globalVBO);

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

                GLBindVertices(GLCreateRectArray(mrect, aColor({WHITE})), 4, globalVAO, globalVBO);
                glDrawArrays(GL_QUADS, 0, 4);
                GLUnbindVertices(globalVAO, globalVBO);

                glStencilFunc(GL_EQUAL, 2, 0xFF);
                glStencilMask(0);

                Anchor anchor = {wrect.x, wrect.y, wrect.w, wrect.h};

                wg->Paint(anchor);

                aColor border = wg->style.border;

                clearShader->Use();

                glStencilFunc(GL_EQUAL, 1, 0xFF);
                
                GLBindVertices(GLCreateRectArray(wrect, border), 4, globalVAO, globalVBO);
                glDrawArrays(GL_LINE_LOOP, 0, 4);
                GLUnbindVertices(globalVAO, globalVBO);

                glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
                glStencilFunc(GL_NEVER, 1, 0xFF);
                glStencilMask(0xFF);

                GLBindVertices(GLCreateRectArray(mrect, aColor({WHITE})), 4, globalVAO, globalVBO);
                glDrawArrays(GL_QUADS, 0, 4);
                GLUnbindVertices(globalVAO, globalVBO);
            }
        }

        glDisable(GL_STENCIL_TEST);
        glStencilMask(0xFF);

        defaultShader->Use();

        GLBindVertices(GLCreateRectArray(rect, border), 4, globalVAO, globalVBO);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        GLUnbindVertices(globalVAO, globalVBO);

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

    void Application::DrawWindowControl(Window* w){
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

        GLBindVertices(GLCreateRectArray(rects[0], control), 4, globalVAO, globalVBO);
        glDrawArrays(GL_QUADS, 0, 4);
        GLUnbindVertices(globalVAO, globalVBO);

        GLBindVertices(GLCreateRectArray(rects[1], control), 4, globalVAO, globalVBO);
        glDrawArrays(GL_QUADS, 0, 4);
        GLUnbindVertices(globalVAO, globalVBO);

        defaultShader->Use();

        GLBindVertices(GLCreateRectArray(rects[0], border), 4, globalVAO, globalVBO);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        GLUnbindVertices(globalVAO, globalVBO);

        GLBindVertices(GLCreateRectArray(rects[1], border), 4, globalVAO, globalVBO);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        GLUnbindVertices(globalVAO, globalVBO);

        if(!w->IsMinimized() && w->CanResize()){
            GLBindVertices(GLCreateRectArray(resRect, border), 4, globalVAO, globalVBO);
            glDrawArrays(GL_LINE_LOOP, 0, 4);
            GLUnbindVertices(globalVAO, globalVBO);
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

        group->CurrentFocus()->OnMouseDown(event);
    }

    void Application::OnMouseUp(SDL_MouseButtonEvent event){
        group->CurrentFocus()->OnMouseUp(event);
    }

    void Application::OnMouseMove(SDL_MouseMotionEvent event){
        group->CurrentFocus()->OnMouseMove(event);
    }

    void Application::OnMouseWheel(SDL_MouseWheelEvent event, aPoint pos){
        group->CurrentFocus()->OnMouseWheel(event, pos);
    }

    // void UICore::MoveMouse(SDL_Event event){
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

    // void UICore::DragMouse(SDL_Event event){
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

    // void UICore::ProcessClick(Window* w, SDL_MouseButtonEvent event){
    //     if(w != group->CurrentFocus()){
    //         group->FocusWindow(w);
    //     }

    //     w->ProcessGlobalClick(event);

    //     event.x -= w->GetRect().x;
    //     event.y -= w->GetRect().y;

    //     w->ProcessClick(event);
    // }

    // void UICore::ClickMouse(SDL_Event event){
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