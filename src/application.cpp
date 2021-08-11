#include <application.h>

namespace AbyssCore{
    bool Application::isRunning;
    SDL_Window* Application::window;
    IWindowsGroup* Application::group;
    thread* Application::render;
    SDL_GLContext Application::glContext;

    unsigned int Application::windowVAO = 0;
    unsigned int Application::windowVBO = 0;

    unsigned int Application::widgetVAO = 0;
    unsigned int Application::widgetVBO = 0;

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

        Resources::LoadBaseResources();
        CreateFramebuffer();

        OpenGL::GenArrayBuffer(windowVBO, GL_DYNAMIC_DRAW, sizeof(float) * 5 * 4);
        OpenGL::GenVertexArray(windowVAO);

        OpenGL::BindVBO(windowVBO);
        OpenGL::BindVAO(windowVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        OpenGL::GenArrayBuffer(widgetVBO, GL_DYNAMIC_DRAW, sizeof(float) * 5 * 4);
        OpenGL::GenVertexArray(widgetVAO);

        OpenGL::BindVBO(widgetVBO);
        OpenGL::BindVAO(widgetVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glClearColor(1, 1, 1, 1);
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

            // aFPoint v1 = OpenGL::PixelsToNormal(aPoint({0, 200}), screen_width, screen_height);
            // aFPoint v2 = OpenGL::PixelsToNormal(aPoint({0, 0}), screen_width, screen_height);
            // aFPoint v3 = OpenGL::PixelsToNormal(aPoint({200, 10}), screen_width, screen_height);
            // aFPoint v4 = OpenGL::PixelsToNormal(aPoint({200, 200}), screen_width, screen_height);

            // float data[] = {
            //     v1.x, v1.y, 0.0, 0.0, 0.0,
            //     v2.x, v2.y, 0.0, 0.0, 1.0,
            //     v3.x, v3.y, 0.0, 1.0, 1.0,
            //     v4.x, v4.y, 0.0, 1.0, 0.0
            // };

            // OpenGL::BindVBO(windowVBO);
            // OpenGL::BindVAO(windowVAO);

            // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 5 * 4, data);

            // OpenGL::UseProgram("interface");

            // OpenGL::Set1i("textureFill", 0);
            // OpenGL::Set1i("flipTexture", 1);

            // OpenGL::Bind2DTexture(Resources::GetTexture("ozzen").id);

            // OpenGL::Set1i("drawBorder", 1);
            // OpenGL::Set4i("borderRect", 10, 10, 100, 100);
            // OpenGL::Set4f("borderColor", 1, 0, 0, 1);
            // OpenGL::Set4f("backgroundColor", 1, 0, 0, 1);

            // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
            // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
            // glEnableVertexAttribArray(0);
            // glEnableVertexAttribArray(1);

            // glDrawArrays(GL_QUADS, 0, 4);


            for(Window* w : group->GetPull()){
                if(w->IsVisible()){
                    DrawWindow(w);
                }
            }

            SDL_GL_SwapWindow(window);
        }

        Resources::FreeResources();

        glDeleteFramebuffers(1, &framebuffer);
        glDeleteTextures(1, &framebufferTexture);
    }

    void Application::CreateFramebuffer(){
        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        glGenTextures(1, &framebufferTexture);
        glBindTexture(GL_TEXTURE_2D, framebufferTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screen_width, screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

        glMatrixMode(GL_PROJECTION);
        glMatrixMode(GL_MODELVIEW);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            printf("Framebuffer not done!\n");
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Application::DrawWindow(Window* w){
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

        aFColor focus = OpenGL::NormilizeColor(w->style.focus);
        aFColor nofocus = OpenGL::NormilizeColor(w->style.nofocus);

        aFColor border = OpenGL::NormilizeColor(w->style.border);

        OpenGL::UseProgram("interface");
        OpenGL::Set1i("textureFill", 0);
        OpenGL::Set1i("drawBorder", 1);
        OpenGL::Set4i("borderRect", rect.x, rect.y, rect.w, rect.h);
        OpenGL::Set4f("borderColor", border.r, border.g, border.b, border.a);

        if(group->CurrentFocus() == w)
            OpenGL::Set4f("backgroundColor", focus.r, focus.g, focus.b, focus.a);
        else
            OpenGL::Set4f("backgroundColor", nofocus.r, nofocus.g, nofocus.b, nofocus.a);

        OpenGL::BindVBO(windowVBO);
        OpenGL::BindVAO(windowVAO);

        aFPoint v1 = OpenGL::PixelsToNormal(aPoint({rect.x, rect.y + rect.h}), screen_width, screen_height);
        aFPoint v2 = OpenGL::PixelsToNormal(aPoint({rect.x, rect.y}), screen_width, screen_height);
        aFPoint v3 = OpenGL::PixelsToNormal(aPoint({rect.x + rect.w, rect.y}), screen_width, screen_height);
        aFPoint v4 = OpenGL::PixelsToNormal(aPoint({rect.x + rect.w, rect.y + rect.h}), screen_width, screen_height);

        float rectData[] = {
            v1.x, v1.y, 0, 0, 0,
            v2.x, v2.y, 0, 0, 1,
            v3.x, v3.y, 0, 1, 1,
            v4.x, v4.y, 0, 1, 0
        };

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 5 * 4, rectData);

        glDrawArrays(GL_QUADS, 0, 4);

        // Vertex* headRectArray = GLCreateRectArray(rect, aColor({WHITE}));
        // GLCreateVertexObjects(headRectArray, 4, globalVAO, globalVBO);

        // colorShader->SetInt1("useVertexColor", 0);

        // if(group->CurrentFocus() == w)
        //     colorShader->SetFloat4("color", focus.r, focus.g, focus.b, focus.a);
        // else
        //     colorShader->SetFloat4("color", nofocus.r, nofocus.g, nofocus.b, nofocus.a);

        // glBindVertexArray(globalVAO);

        // glDrawArrays(GL_QUADS, 0, 4);

        // unsigned int textVAO, textVBO;

        // Texture text = Resources::CreateStringTexture(w->GetTitle(), "arial15", 200);

        // GLCreateVertexObjects(GLCreateRectArray(SDL_Rect({rect.x + 10, rect.y + 10, text.width, text.height}), aColor({WHITE})), 4, textVAO, textVBO);

        // GLBind2DTexture(text.id);

        // GLBindVertexArray(textVAO);

        // textureShader->Use();
        // textureShader->SetInt1("flip", 1);

        // glDrawArrays(GL_QUADS, 0, 4);

        // GLDestroyVertexObjects(textVAO, textVBO);

        // glBindVertexArray(globalVAO);

        // colorShader->Use();

        // colorShader->SetFloat4("color", border.r, border.g, border.b, border.a);

        // glDrawArrays(GL_LINE_LOOP, 0, 4);

        // GLDestroyVertexObjects(globalVAO, globalVBO);
    }

    void Application::DrawWindowBody(Window* w){
        SDL_Rect rect = w->GetRect();

        if(w->IsFull())
            rect.y += HEADER_HEIGHT;

        aFColor border = OpenGL::NormilizeColor(w->style.border);
        aFColor background = OpenGL::NormilizeColor(w->style.background);

        aFPoint v1 = OpenGL::PixelsToNormal(aPoint({rect.x, rect.y + rect.h}), screen_width, screen_height);
        aFPoint v2 = OpenGL::PixelsToNormal(aPoint({rect.x, rect.y}), screen_width, screen_height);
        aFPoint v3 = OpenGL::PixelsToNormal(aPoint({rect.x + rect.w, rect.y}), screen_width, screen_height);
        aFPoint v4 = OpenGL::PixelsToNormal(aPoint({rect.x + rect.w, rect.y + rect.h}), screen_width, screen_height);

        float rectData[] = {
            v1.x, v1.y, 0, 0, 0,
            v2.x, v2.y, 0, 0, 1,
            v3.x, v3.y, 0, 1, 1,
            v4.x, v4.y, 0, 1, 0
        };

        OpenGL::BindVBO(windowVBO);
        OpenGL::BindVAO(windowVAO);

        OpenGL::UseProgram("interface");
        OpenGL::Set1i("textureFill", 0);
        OpenGL::Set1i("drawBorder", 1);
        OpenGL::Set4i("borderRect", rect.x, rect.y, rect.w, rect.h);
        OpenGL::Set4f("borderColor", border.r, border.g, border.b, border.a);
        OpenGL::Set4f("backgroundColor", background.r, background.g, background.b, background.a);

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 5 * 4, rectData);



        // colorShader->Use();

        // colorShader->SetInt1("useVertexColor", 0);

        // GLCreateVertexObjects(GLCreateRectArray(rect, aColor({WHITE})), 4, globalVAO, globalVBO);

        glEnable(GL_STENCIL_TEST);

        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilMask(0xFF);

        glStencilFunc(GL_ALWAYS, 1, 0xFF);

        glDrawArrays(GL_QUADS, 0, 4);
        
        // colorShader->SetFloat4("color", 1, 1, 1, 1);
        // glBindVertexArray(globalVAO);

        // glDrawArrays(GL_QUADS, 0, 4);

        //TODO: update paint functions

        // glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        // glStencilFunc(GL_EQUAL, 1, 0xFF);
        // glStencilMask(0);

        // Anchor anchor = {rect.x, rect.y, rect.w, rect.h};
        // w->Paint(anchor);

        for(Widget * wg : w->GetPull()){
            if(wg->IsVisible() && wg->GetRect().x <= w->GetRect().w && wg->GetRect().y <= w->GetRect().h){ 
                SDL_Rect wrect = wg->GetRect();
                wrect.x += rect.x;
                wrect.y += rect.y;

                aFColor border = OpenGL::NormilizeColor(wg->style.border);
                aFColor background = OpenGL::NormilizeColor(wg->style.background);

                aFPoint wv1 = OpenGL::PixelsToNormal(aPoint({wrect.x, wrect.y + wrect.h}), screen_width, screen_height);
                aFPoint wv2 = OpenGL::PixelsToNormal(aPoint({wrect.x, wrect.y}), screen_width, screen_height);
                aFPoint wv3 = OpenGL::PixelsToNormal(aPoint({wrect.x + wrect.w, wrect.y}), screen_width, screen_height);
                aFPoint wv4 = OpenGL::PixelsToNormal(aPoint({wrect.x + wrect.w, wrect.y + wrect.h}), screen_width, screen_height);

                float wrectData[] = {
                    wv1.x, wv1.y, 0, 0, 0,
                    wv2.x, wv2.y, 0, 0, 1,
                    wv3.x, wv3.y, 0, 1, 1,
                    wv4.x, wv4.y, 0, 1, 0
                };

                OpenGL::BindVBO(widgetVBO);
                OpenGL::BindVAO(widgetVAO);

                OpenGL::UseProgram("interface");
                OpenGL::Set1i("textureFill", 0);
                OpenGL::Set1i("drawBorder", 1);
                OpenGL::Set4i("borderRect", wrect.x, wrect.y, wrect.w, wrect.h);
                OpenGL::Set4f("borderColor", border.r, border.g, border.b, border.a);
                OpenGL::Set4f("backgroundColor", background.r, background.g, background.b, background.a);

                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 5 * 4, wrectData);

                glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
                glStencilFunc(GL_EQUAL, 1, 0xFF);
                glStencilMask(0xFF);

                glDrawArrays(GL_QUADS, 0, 4);

                glStencilFunc(GL_EQUAL, 2, 0xFF);
                glStencilMask(0);

                //TODO: here too

                // Anchor anchor = {wrect.x, wrect.y, wrect.w, wrect.h};

                // wg->Paint(anchor);

                OpenGL::UseProgram("interface");

                OpenGL::BindVBO(widgetVBO);
                OpenGL::BindVAO(widgetVAO);

                glStencilOp(GL_DECR, GL_KEEP, GL_KEEP);
                glStencilFunc(GL_LESS, 2, 0xFF);
                glStencilMask(0xFF);

                glDrawArrays(GL_QUADS, 0, 4);

                glStencilFunc(GL_EQUAL, 1, 0xFF);
                glStencilMask(0x00);
            }
        }
        //     
        //         glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
        //         glStencilFunc(GL_EQUAL, 1, 0xFF);
        //         glStencilMask(0xFF);

        //         
        //     }
        // }

        glDisable(GL_STENCIL_TEST);
        glStencilMask(0xFF);

        // colorShader->SetInt1("useVertexColor", 0);
        // colorShader->SetFloat4("color", border.r, border.g, border.b, border.a);

        // glBindVertexArray(globalVAO);
        // glDrawArrays(GL_LINE_LOOP, 0, 4);
        // GLDestroyVertexObjects(globalVAO, globalVBO);

        glClear(GL_STENCIL_BUFFER_BIT);
    }

    void Application::DrawWindowControl(Window* w){
        // SDL_Rect wRect = w->GetRect();

        // SDL_Rect closeHitBox = w->GetCloseHitBox();
        // SDL_Rect minimazeHitBox = w->GetMinimizeHitBox();
        // SDL_Rect resizeHitBox = w->GetResizeHitBox();

        // SDL_Rect crossRect = {wRect.x + closeHitBox.x, wRect.y + closeHitBox.y, closeHitBox.w, closeHitBox.h};
        // SDL_Rect minRect = {wRect.x + minimazeHitBox.x - 1, wRect.y + minimazeHitBox.y, minimazeHitBox.w, minimazeHitBox.h};
        // SDL_Rect resRect = {wRect.x + resizeHitBox.x - 1, wRect.y + resizeHitBox.y - 1, resizeHitBox.w, resizeHitBox.h};
        // SDL_Rect rects[2] = {crossRect, minRect};

        // aColor control = w->style.control;
        // aColor border = w->style.border;
        // aFColor enabled = GLConvertColor(w->style.enabled);
        // aFColor disabled = GLConvertColor(w->style.disabled);

        // string uniformName = "colorModificator";

        // controlShader->Use();

        // GLBind2DTexture(Resources::GetTexture("close").id);

        // if(w->CanClose())
        //     controlShader->SetFloat4(uniformName, enabled.r, enabled.g, enabled.b, enabled.a);
        // else
        //     controlShader->SetFloat4(uniformName, disabled.r, disabled.g, disabled.b, disabled.a);

        // GLCreateVertexObjects(GLCreateRectArray(rects[0], control), 4, globalVAO, globalVBO);

        // glBindVertexArray(globalVAO);
        // glDrawArrays(GL_QUADS, 0, 4);

        // colorShader->Use();

        // colorShader->SetInt1("useVertexColor", 0);
        // colorShader->SetFloat4("color", border.r, border.g, border.b, border.a);

        // glDrawArrays(GL_LINE_LOOP, 0, 4);
        // GLDestroyVertexObjects(globalVAO, globalVBO);

        // controlShader->Use();

        // GLBind2DTexture(Resources::GetTexture("minimize").id);

        // if(w->CanMinimize())
        //     controlShader->SetFloat4(uniformName, enabled.r, enabled.g, enabled.b, enabled.a);
        // else
        //     controlShader->SetFloat4(uniformName, disabled.r, disabled.g, disabled.b, disabled.a);

        // GLCreateVertexObjects(GLCreateRectArray(rects[1], control), 4, globalVAO, globalVBO);
        
        // glBindVertexArray(globalVAO);
        // glDrawArrays(GL_QUADS, 0, 4);

        // colorShader->Use();

        // glDrawArrays(GL_LINE_LOOP, 0, 4);
        // GLDestroyVertexObjects(globalVAO, globalVBO);

        // if(!w->IsMinimized() && w->CanResize()){
        //     controlShader->Use();

        //     controlShader->SetFloat4(uniformName, enabled.r, enabled.g, enabled.b, enabled.a);

        //     GLBind2DTexture(Resources::GetTexture("resize").id);

        //     GLCreateVertexObjects(GLCreateRectArray(resRect, control), 4, globalVAO, globalVBO);
        //     glBindVertexArray(globalVAO);
        //     glDrawArrays(GL_QUADS, 0, 4);
        //     GLDestroyVertexObjects(globalVAO, globalVBO);
        // }
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