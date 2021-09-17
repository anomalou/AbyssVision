#include <application.h>

namespace MediumCore{
    SDL_Window* Application::window;
    IWindowsGroup* Application::group;
    thread* Application::render;
    SDL_GLContext Application::glContext;

    float Application::defaultNormilizedWidth;
    float Application::defaultNormilizedHeight;

    unsigned int Application::defaultVAO = 0;
    unsigned int Application::defaultVBO = 0;
    unsigned int Application::instancedVBO = 0;

    unsigned int Application::framebuffer;
    unsigned int Application::framebufferTexture;

    int Application::fps;

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

        if(SDL_WaitEvent(&event)){
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

            // SDL_Delay(fps);
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

        CreateDefaultBuffers();

        glClearColor(1, 1, 1, 1);
        glClearStencil(0x00);

        Uint64 now = SDL_GetPerformanceCounter();
        Uint64 last = 0;

        glViewport(0, 0, screen_width, screen_height);

        while(isRunning){
            last = now;
            now = SDL_GetPerformanceCounter();

            Time::deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());

            int lTime = SDL_GetTicks();
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_STENCIL_BUFFER_BIT);

            //Render game scene

            //Render UI

            //Render window interface
            DrawGameScene();

            DrawWindows();

            SDL_GL_SwapWindow(window);
            // SDL_Delay(1000/120);

            int cTime = SDL_GetTicks();
            if(cTime - lTime > 0){
                fps = 1000/(cTime - lTime);
                // printf("FPS: %d\n", fps);
            }
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

    void Application::CreateDefaultBuffers(){
        defaultNormilizedWidth = OpenGL::ScreenProportion(screen_width, screen_width) / 2;
        defaultNormilizedHeight = OpenGL::ScreenProportion(screen_width, screen_height) / 2;

        float baseRect[] = {
            -defaultNormilizedWidth, -defaultNormilizedHeight, 0, 0, 0,
            -defaultNormilizedWidth, defaultNormilizedHeight, 0, 0, 1,
            defaultNormilizedWidth, defaultNormilizedHeight, 0, 1, 1,
            defaultNormilizedWidth, -defaultNormilizedHeight, 0, 1, 0
        };

        OpenGL::GenArrayBuffer(defaultVBO);
        OpenGL::GenVertexArray(defaultVAO);

        OpenGL::BindVBO(defaultVBO);
        OpenGL::BindVAO(defaultVAO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5 * 4, baseRect, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(3);

        OpenGL::GenArrayBuffer(instancedVBO);
        OpenGL::BindVBO(instancedVBO);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, 0);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*)(sizeof(float) * 3));
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*)(sizeof(float) * 6));
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*)(sizeof(float) * 10));
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*)(sizeof(float) * 14));
        glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*)(sizeof(float) * 18));
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(4);
        glEnableVertexAttribArray(5);
        glEnableVertexAttribArray(6);
        glEnableVertexAttribArray(7);
        glVertexAttribDivisor(1, 1);
        glVertexAttribDivisor(2, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
        glVertexAttribDivisor(7, 1);
    }

    void Application::RenderRects(Renderer renderer){
        vector<Rectangle> rects = renderer.GetRectangles();

        int rectsSize = rects.size();

        if(rectsSize > 0){
            OpenGL::BindVBO(instancedVBO);
            vector<Instanced> irects = vector<Instanced>();

            for(int i = 0; i < rectsSize; i++){
                aFPoint rpos = OpenGL::PixelsToNormal(rects[i].position, screen_width, screen_height);
                float scaleX = OpenGL::Proportion(rects[i].size.width, screen_width);
                float scaleY = OpenGL::Proportion(rects[i].size.height, screen_width);

                aFColor background = OpenGL::NormilizeColor(rects[i].backgroundColor);
                aFColor border = background;
                if(rects[i].drawBorder)
                    border = OpenGL::NormilizeColor(rects[i].borderColor);

                float depth = OpenGL::Proportion(rects[i].id, renderer.MaxID());

                Instanced inst;

                inst.offset = {rpos.x + defaultNormilizedWidth * scaleX, rpos.y - defaultNormilizedHeight * scaleY, depth};
                inst.scale = {scaleX, scaleY, 1};
                inst.texOffset = {0, 0, 0, 0};
                inst.background = {background.r, background.g, background.b, background.a};
                inst.border = {border.r, border.g, border.b, border.a};
                inst.borderRect = {rects[i].position.x, rects[i].position.y, rects[i].size.width, rects[i].size.height};
            
                irects.push_back(inst);
            }

            //TODO: optimize
            glBufferData(GL_ARRAY_BUFFER, sizeof(Instanced) * rectsSize, irects.data(), GL_STATIC_DRAW);

            //TODO:depth test

            OpenGL::UseProgram("icolor");

            glDrawArraysInstanced(GL_QUADS, 0, 4, rectsSize);
        }
    }

    void Application::RenderSprites(Renderer renderer){
        vector<Sprite> sprites = renderer.GetSprites();
        //TODO: Update atlas file writing
        if(sprites.size() > 0){
            Atlas atlas = Resources::GetAtlas(renderer.SelectedAtlas());
            if(atlas.id != 0){
                OpenGL::BindVBO(instancedVBO);
                vector<Instanced> isprites = vector<Instanced>();

                for(int i = 0; i < sprites.size(); i++){
                    Sprite sprite = sprites[i];
                    if(atlas.textures.find(sprite.textureName) == atlas.textures.end()){
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Texture not founded!", sprite.textureName.c_str(), window);
                        continue;
                    }

                    Texture texture = atlas.textures.at(sprite.textureName);

                    aFPoint pos = OpenGL::PixelsToNormal(sprite.position, screen_width, screen_height);
                    float scaleX = OpenGL::Proportion(sprite.size.width, screen_width);
                    float scaleY = OpenGL::Proportion(sprite.size.height, screen_width);

                    aFPoint tpos = OpenGL::TexelsToNormal(aPoint({texture.x, texture.y}), atlas.width, atlas.height);
                    float tscaleX = OpenGL::Proportion(texture.width, atlas.width);
                    float tscaleY = OpenGL::Proportion(texture.height, atlas.height);

                    Instanced iso;

                    iso.offset = {pos.x + defaultNormilizedWidth * scaleX, pos.y - defaultNormilizedHeight * scaleY, 0};
                    iso.scale = {scaleX, scaleY, 1};
                    iso.texOffset = {tpos.x, tpos.y, tscaleX, tscaleY};

                    isprites.push_back(iso);
                }

                OpenGL::Bind2DTexture(atlas.id);
                OpenGL::UseProgram("itexture");
                OpenGL::Set1i("fFlip", 1);

                glBufferData(GL_ARRAY_BUFFER, sizeof(Instanced) * isprites.size(), isprites.data(), GL_STATIC_DRAW);

                glDrawArraysInstanced(GL_QUADS, 0, 4, isprites.size());
            }
        }
    }

    void Application::RenderText(Renderer renderer){
        vector<Text> texts = renderer.GetTexts();

        int textsSize = texts.size();

        if(textsSize > 0){
            OpenGL::BindVBO(instancedVBO);
            vector<Instanced> gliphs = vector<Instanced>();

            Font font = Resources::GetCurrentFont();

            OpenGL::Bind2DTexture(font.gliphsTexture);

            for(Text text : texts){
                float scale = text.scale;
                aPoint startPoint = text.position;
                aPoint offset = startPoint;
                for(int i = 0; i < text.str.length(); i++){
                    char c = text.str[i];

                    if(font.gliphs.find(c) != font.gliphs.end()){
                        Gliph *gliph;

                        gliph = font.gliphs.at(c);

                        if(((offset.x + gliph->advance * scale) - startPoint.x) > text.maxWidth && text.maxWidth != 0){
                            break;
                        }

                        aPoint gliphPos = {offset.x, offset.y - (int)(gliph->maxy * scale)};
                        aFPoint npos = OpenGL::PixelsToNormal(gliphPos, screen_width, screen_height);
                        float scaleX = OpenGL::Proportion((gliph->maxx - gliph->minx) * scale, screen_width);
                        float scaleY = OpenGL::Proportion((gliph->maxy - gliph->miny) * scale, screen_width);

                        Instanced glh;

                        glh.offset = {npos.x + defaultNormilizedWidth * scaleX, npos.y - defaultNormilizedHeight * scaleY, 0};
                        glh.scale = {scaleX, scaleY, 1};
                        glh.texOffset = {gliph->texRect.left, gliph->texRect.bottom, gliph->texRect.right - gliph->texRect.left, gliph->texRect.top};

                        gliphs.push_back(glh);

                        offset.x += gliph->advance * scale;
                    }
                }
            }

            glBufferData(GL_ARRAY_BUFFER, sizeof(Instanced) * gliphs.size(), gliphs.data(), GL_STATIC_DRAW);

            OpenGL::UseProgram("itexture");
            OpenGL::Set1i("fFlip", 1);

            glDrawArraysInstanced(GL_QUADS, 0, 4, gliphs.size());
        }
    }

    void Application::DrawGameScene(){
        Renderer renderer(0, 0, screen_width, screen_height);

        GameCore::Paint(renderer);

        RenderRects(renderer);
        RenderSprites(renderer);
        RenderText(renderer);
    }

    void Application::DrawWindows(){
        glBufferData(GL_ARRAY_BUFFER, sizeof(Instanced), NULL, GL_DYNAMIC_DRAW);

        for(Window* w : group->GetPull()){
            if(w->IsFull()){
                DrawWindowHead(w);
            }

            if(!w->IsMinimized())
                DrawWindowBody(w);

            if(w->IsFull())
                DrawWindowControl(w);
        }

    }

    void Application::DrawWindowHead(Window* w){
        SDL_Rect rect = w->GetRect();
        rect.h = HEADER_HEIGHT;

        aFColor focus = OpenGL::NormilizeColor(w->style.focus);
        aFColor nofocus = OpenGL::NormilizeColor(w->style.nofocus);

        aFColor border = OpenGL::NormilizeColor(w->style.border);

        float scaleX = OpenGL::Proportion(rect.w, screen_width);

        float scaleY = 0;
        if(w->IsFull())
            scaleY = OpenGL::Proportion(HEADER_HEIGHT, screen_width);

        aFPoint pos = OpenGL::PixelsToNormal(aPoint({rect.x, rect.y}), screen_width, screen_height);

        aFColor background;
        if(group->CurrentFocus() == w)
            background = focus;
        else
            background = nofocus;

        float attribs[] = {
            pos.x + defaultNormilizedWidth * scaleX, pos.y - defaultNormilizedHeight * scaleY, 0, 
            scaleX, scaleY, 1, 
            0, 0, 0, 0,
            background.r, background.g, background.b, background.a,
            border.r, border.g, border.b, border.a,
            (float)rect.x, (float)rect.y, (float)rect.w, (float)rect.h
        };

        OpenGL::BindVAO(defaultVAO);
        OpenGL::BindVBO(instancedVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Instanced), attribs);

        OpenGL::UseProgram("icolor");

        glDrawArrays(GL_QUADS, 0, 4);
    }

    void Application::DrawWindowBody(Window* w){
        SDL_Rect rect = w->GetRect();

        if(w->IsFull())
            rect.y += HEADER_HEIGHT;

        aFColor border = OpenGL::NormilizeColor(w->style.border);
        aFColor background = OpenGL::NormilizeColor(w->style.background);

        float scaleX = OpenGL::Proportion(rect.w, screen_width);
        float scaleY = OpenGL::Proportion(rect.h, screen_width);

        aFPoint pos = OpenGL::PixelsToNormal(aPoint({rect.x, rect.y}), screen_width, screen_height);

        Instanced body[] = {
            {vec3(pos.x + defaultNormilizedWidth * scaleX, pos.y - defaultNormilizedHeight * scaleY, 0),
             vec3(scaleX, scaleY, 1),
             vec4(1, 1, 1, 1),
             vec4(background.r, background.g, background.b, background.a),
             vec4(border.r, border.g, border.b, border.a),
             vec4(rect.x, rect.y, rect.w, rect.h)}
        };

        //TODO: optimize
        OpenGL::UseProgram("icolor");
        glBufferData(GL_ARRAY_BUFFER, sizeof(Instanced), body, GL_DYNAMIC_DRAW);

        glEnable(GL_STENCIL_TEST);

        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilMask(0xFF);

        glStencilFunc(GL_ALWAYS, 1, 0xFF);

        glDrawArrays(GL_QUADS, 0, 4);

        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        glStencilFunc(GL_EQUAL, 1, 0xFF);
        glStencilMask(0);

        Renderer renderer(rect.x, rect.y, rect.w, rect.h);

        w->Paint(renderer);

        RenderRects(renderer);
        RenderSprites(renderer);
        RenderText(renderer);

        for(Widget * wg : w->GetPull()){
            if(wg->IsVisible() && wg->GetRect().x <= w->GetRect().w && wg->GetRect().y <= w->GetRect().h){
                SDL_Rect wrect = wg->GetRect();
                wrect.x += rect.x;
                wrect.y += rect.y;

                aFColor border = OpenGL::NormilizeColor(wg->style.border);
                aFColor background = OpenGL::NormilizeColor(wg->style.background);

                float scaleX = OpenGL::Proportion(wrect.w, screen_width);
                float scaleY = OpenGL::Proportion(wrect.h, screen_width);

                aFPoint pos = OpenGL::PixelsToNormal(aPoint({wrect.x, wrect.y}), screen_width, screen_height);

                Instanced wbody[] = {
                    {vec3(pos.x + defaultNormilizedWidth * scaleX, pos.y - defaultNormilizedHeight * scaleY, 0),
                    vec3(scaleX, scaleY, 1),
                    vec4(0, 0, 0, 0),
                    vec4(background.r, background.g, background.b, background.a),
                    vec4(border.r, border.g, border.b, border.a),
                    vec4(wrect.x, wrect.y, wrect.w, wrect.h)}
                };

                //TODO: optimize
                glBufferData(GL_ARRAY_BUFFER, sizeof(Instanced), wbody, GL_STATIC_DRAW);

                OpenGL::UseProgram("icolor");

                glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
                glStencilFunc(GL_EQUAL, 1, 0xFF);
                glStencilMask(0xFF);

                glDrawArrays(GL_QUADS, 0, 4);

                glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
                glStencilFunc(GL_EQUAL, 2, 0xFF);
                glStencilMask(0x0);

                Renderer renderer(wrect.x, wrect.y, wrect.w, wrect.h);

                wg->Paint(renderer);

                RenderRects(renderer);
                RenderSprites(renderer);
                RenderText(renderer);

                glStencilOp(GL_DECR, GL_KEEP, GL_KEEP);
                glStencilFunc(GL_LESS, 2, 0xFF);
                glStencilMask(0xFF);

                glBufferData(GL_ARRAY_BUFFER, sizeof(Instanced), wbody, GL_STATIC_DRAW);

                glDrawArrays(GL_QUADS, 0, 4);
            }
        }

        glDisable(GL_STENCIL_TEST);
        glStencilMask(0xFF);

        glClear(GL_STENCIL_BUFFER_BIT);
    }

    void Application::DrawWindowControl(Window* w){
        SDL_Rect wRect = w->GetRect();

        SDL_Rect closeHitBox = w->GetCloseHitBox();
        SDL_Rect minimazeHitBox = w->GetMinimizeHitBox();
        SDL_Rect resizeHitBox = w->GetResizeHitBox();

        aPRect crects[] = {
            {{wRect.x + closeHitBox.x, wRect.y + closeHitBox.y}, {closeHitBox.w, closeHitBox.h}},
            {{wRect.x + minimazeHitBox.x - 1, wRect.y + minimazeHitBox.y}, {minimazeHitBox.w, minimazeHitBox.h}},
            {{wRect.x + resizeHitBox.x - 1, wRect.y + resizeHitBox.y - 1}, {resizeHitBox.w, resizeHitBox.h}}
        };

        // aFColor control = OpenGL::NormilizeColor(w->style.control);

        OpenGL::UseProgram("itexture");
        OpenGL::Set1i("fFlip", 1);

        int elementCount = 0;

        if(w->CanClose())
            elementCount++;

        if(w->CanMinimize())
            elementCount++;

        if(w->CanResize() && !w->IsMinimized())
            elementCount++;

        Instanced inst[3];

        aPoint ui_atlas_scale({Resources::ui.width, Resources::ui.height});

        for(int i = 0; i < elementCount; i++){
            Texture tex;

            //TODO: check this
            switch(i){
                case 0:
                    tex = Resources::ui.textures["close"];
                break;
                case 1:
                    tex = Resources::ui.textures["minimize"];
                break;
                case 2:
                    tex = Resources::ui.textures["resize"];
                break;
            }

            aFPoint pos = OpenGL::PixelsToNormal(crects[i].pos, screen_width, screen_height);
            float scaleX = OpenGL::Proportion(crects[i].size.x, screen_width);
            float scaleY = OpenGL::Proportion(crects[i].size.y, screen_width);

            aFPoint tpos = OpenGL::TexelsToNormal(aPoint({tex.x, tex.y}), ui_atlas_scale.x, ui_atlas_scale.y);
            aFPoint tscale = OpenGL::TexelsToNormal(aPoint({tex.width, tex.height}), ui_atlas_scale.x, ui_atlas_scale.y);

            inst[i].offset = {pos.x + defaultNormilizedWidth * scaleX, pos.y - defaultNormilizedHeight * scaleY, 0};
            inst[i].scale = {scaleX, scaleY, 1};
            inst[i].texOffset = {tpos.x, tpos.y, tscale.x, tscale.y};
        }

        OpenGL::Bind2DTexture(Resources::ui.id);

        glBufferData(GL_ARRAY_BUFFER, sizeof(Instanced) * elementCount, inst, GL_STATIC_DRAW);
    
        glDrawArraysInstanced(GL_QUADS, 0, 4, elementCount);
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
            return;
        }

        GameCore::ProcessKey(event.key);
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
            "Medium", 
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