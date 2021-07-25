#include "core.h"

namespace AbyssCore{
    bool InitCore(){
        Core* core = Core::GetInstance();
        if(core->Init()){
            return true;
        }
        return false;
    }

    void StartCore(){
        Core* core = Core::GetInstance();

        if(core != nullptr){
            core->Start();
        }
    }

    void DisposeCore(){
        Core* core = Core::GetInstance();

        if(core != nullptr){
            if(font != nullptr)
                TTF_CloseFont(font);
            core->Dispose();
            core = nullptr;
        }
    }

    void OpenFont(const char* filePath){
        Core* core = Core::GetInstance();

        if(core != nullptr){
            if(font != nullptr){
                TTF_CloseFont(font);
            }
            font = TTF_OpenFont(filePath, FSIZE);
        }
    }

    void AssignMainWindow(Window * w){
        Core* core = Core::GetInstance();

        w->SetPos(0, 0);
        w->SetSize(RESOLUTION_X, RESOLUTION_Y - HEADER_HEIGHT);

        core->GetGroup()->Create(w, new AString("Main window"));
        core->GetGroup()->FocusWindow(w);
        w->SetVisible(true);
        w->AllowClose(false);
        core->SetMainWindow(w);

        w->AllowResize(true);
    }

    void AssignSubWindow(Window * w, AString* name){
        Core* core = Core::GetInstance();

        w->SetPos(0, 0);
        w->SetSize(100, 100);

        core->GetGroup()->Create(w, name);
        w->SetVisible(true);

        w->AllowResize(true);
    }

    Core::Core(){
        isRunning = false;
    }

    Core* Core::INSTANCE;

    Core* Core::GetInstance(){
        if(INSTANCE == nullptr){
            INSTANCE = new Core();
        }

        return INSTANCE;
    }

    bool Core::Init(){
        if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
            return false;

        if(TTF_Init() != 0)
            return false;

        if(!CreateWindow())
            return false;
        
        if(!CreateRenderer()){
            DisposeWindow();
            return false;
        }

        group = new SystemGroup();
        SDL_ShowCursor(SDL_DISABLE);

        return true;
    }

    void Core::Start(){
        isRunning = true;

        RenderPtrs* ptrs = (RenderPtrs*)malloc(sizeof(RenderPtrs));
        ptrs->corePtr = this;

        renderThread = SDL_CreateThread(Render, "input", ptrs);

        SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);

        if(mainWindow == nullptr){
            Window* mw = new MainWindow();

            mw->SetPos(0, 0);
            mw->SetSize(RESOLUTION_X, RESOLUTION_Y - HEADER_HEIGHT);

            mainWindow = mw;
            mw->SetVisible(true);
            group->FocusWindow(mw);
            group->Create(mw, new AString("Main window"));
        }

        Input();
    }

    void Core::Dispose(){
        isRunning = false;

        DisposeWindow();
        DisposeRenderer();

        SDL_Quit();
    }

    void Core::Input(){
        SDL_Event event;

        while(isRunning){
            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_QUIT:
                        isRunning = false;
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

        
    }

    int Core::Render(void *rendPtr){
        RenderPtrs* renderPtrs = (RenderPtrs*)rendPtr;
        SDL_Renderer* render = renderPtrs->corePtr->renderer;
        IWindowsGroup* group = renderPtrs->corePtr->group;

        while(renderPtrs->corePtr->isRunning){
            SDL_SetRenderDrawColor(render, LIGHT_GRAY);
            SDL_RenderClear(render);

            for(Window* w : group->GetPull()){
                if(w->IsVisible()){
                    renderPtrs->corePtr->DrawWindow(render, w);
                }
            }

            SDL_Rect rect = {renderPtrs->corePtr->mousePosition.x, renderPtrs->corePtr->mousePosition.y, 10, 10};

            SDL_SetRenderDrawColor(render, BLACK);
            SDL_RenderDrawRect(render, &rect);

            // SDL_Point pos = renderPtrs->corePtr->mousePosition;

            // if(currentFocus->IsVisible())
            //     renderPtrs->corePtr->DrawWindow(render, currentFocus);

            SDL_RenderPresent(render);
            SDL_Delay(1000/FPS);
        }

        return 0;
    }

    void Core::DrawWindow(SDL_Renderer* render, Window* w){
        SDL_Rect rect = w->GetRect();

        int width = rect.w;
        int height = rect.h;

        rect.w += w->style.shadow_size;
        rect.h += w->style.shadow_size;

        if(w->IsMinimazed())
            rect.h -= height;

        if(w->IsFull())
            rect.h += HEADER_HEIGHT;

        SDL_Texture* windowTexture = SDL_CreateTexture(render, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
        SDL_SetRenderTarget(render, windowTexture);
        SDL_SetTextureBlendMode(windowTexture, SDL_BlendMode::SDL_BLENDMODE_BLEND);

        if(w->IsFull())
            DrawWindowHead(render, w);
        if(!w->IsMinimazed())
            DrawWindowBody(render, w);
        if(w->IsFull())
            DrawWindowControl(render, w);

        SDL_SetRenderTarget(render, NULL);
        SDL_RenderCopy(render, windowTexture, NULL, &rect);
        SDL_DestroyTexture(windowTexture);
    }

    void Core::DrawWindowHead(SDL_Renderer *render, Window* w){
        int x = 0;
        int y = 0;
        int width = w->GetRect().w;
        int height = HEADER_HEIGHT;
        SDL_Rect rect = SDL_Rect({x, y, width, height});

        SDL_Color focus = w->style.focus;
        SDL_Color nofocus = w->style.nofocus;

        SDL_Color border = w->style.border;

        if(group->CurrentFocus() == w)
            SDL_SetRenderDrawColor(render, focus.r, focus.g, focus.b, focus.a);
        else
            SDL_SetRenderDrawColor(render, nofocus.r, nofocus.g, nofocus.b, nofocus.a);
        SDL_RenderFillRect(render, &rect);
        SDL_SetRenderDrawColor(render, border.r, border.g, border.b, border.a);
        SDL_RenderDrawRect(render, &rect);

        SDL_Color shadow = w->style.shadow;
        int shadow_size = w->style.shadow_size;

        SDL_SetRenderDrawColor(render, shadow.r, shadow.g, shadow.b, shadow.a);
        SDL_RenderFillRect(render, new SDL_Rect({rect.x + rect.w, rect.y + shadow_size, shadow_size, HEADER_HEIGHT}));

        if(w->IsMinimazed())
            SDL_RenderFillRect(render, new SDL_Rect({rect.x + shadow_size, rect.y + HEADER_HEIGHT, rect.w - shadow_size, shadow_size}));
        
        //window title

        rect.x = x + FSIGN_WIDTH / 2;
        rect.y = y + FSIGN_HEIGHT / 2;
        rect.w = FSIGN_WIDTH * w->GetName()->Length();
        rect.h = FSIGN_HEIGHT;

        if((rect.w + FSIGN_WIDTH / 2) > w->GetRect().w)
            rect.w = w->GetRect().w - FSIGN_WIDTH / 2;

        SDL_Color color = {BLACK};

        SDL_Surface* surface = TTF_RenderText_Solid(font, w->GetName()->ToChars(), color);

        SDL_Texture* header = SDL_CreateTextureFromSurface(render, surface);

        SDL_RenderCopy(render, header, NULL, &rect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(header);
    }

    void Core::DrawWindowBody(SDL_Renderer *render, Window* w){
        SDL_Rect rect = w->GetRect();
        rect.x = 0;

        if(w->IsFull())
            rect.y = HEADER_HEIGHT - 1;
        else
            rect.y = 0;

        // SDL_Color border = w->GetStyle().border;
        SDL_Texture* currTarget = SDL_GetRenderTarget(render);

        SDL_Texture* bodyTex = SDL_CreateTexture(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
        SDL_SetRenderTarget(render, bodyTex);
        w->Paint(render);

        for(Widget* w : w->GetPull()){
            if(w->IsVisible()){
                SDL_Rect wrect = w->GetRect();

                SDL_Texture* widgetTex = SDL_CreateTexture(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, wrect.w, wrect.h);
                SDL_SetRenderTarget(render, widgetTex);
                w->Paint(render);
                SDL_SetRenderTarget(render, bodyTex);
                SDL_RenderCopy(render, widgetTex, NULL, &wrect);
                SDL_DestroyTexture(widgetTex);

                // SDL_Color border = w->GetStyle().border;

                // SDL_SetRenderDrawColor(render, border.r, border.g, border.b, border.a);
                // SDL_RenderDrawRect(render, &wrect);
            }
        }

        SDL_SetRenderTarget(render, currTarget);
        SDL_RenderCopy(render, bodyTex, NULL, &rect);
        SDL_DestroyTexture(bodyTex);

        // SDL_SetRenderDrawColor(render, border.r, border.g, border.b, border.a);
        // SDL_RenderDrawRect(render, &rect);

        SDL_Color shadow = w->style.shadow;
        int shadow_size = w->style.shadow_size;

        SDL_SetRenderDrawColor(render, shadow.r, shadow.g, shadow.b, shadow.a);
        SDL_Rect shadows[2] = {{rect.x + shadow_size, rect.y + rect.h, rect.w - shadow_size, shadow_size},
                               {rect.x + rect.w, rect.y + shadow_size + 1, shadow_size, rect.h - 1}};

        SDL_RenderFillRects(render, shadows, 2);
    }

    void Core::DrawWindowControl(SDL_Renderer * render, Window* w){
        SDL_Rect wRect = w->GetRect();
        wRect.x = 0;
        wRect.y = 0;

        int hmargin = (CBUTTON_WIDTH - CSIGN_SIZE) / 2;
        int vmargin = (HEADER_HEIGHT - CSIGN_SIZE) / 2;

        SDL_Rect closeHitBox = w->GetCloseHitBox();
        SDL_Rect minimazeHitBox = w->GetMinimazeHitBox();
        SDL_Rect resizeHitBox = w->GetResizeHitBox();

        SDL_Rect crossRect = {wRect.x + closeHitBox.x, wRect.y + closeHitBox.y, closeHitBox.w, closeHitBox.h};
        SDL_Rect minRect = {wRect.x + minimazeHitBox.x, wRect.y + minimazeHitBox.y, minimazeHitBox.w, minimazeHitBox.h};
        SDL_Rect resRect = {wRect.x + resizeHitBox.x, wRect.y + resizeHitBox.y, resizeHitBox.w, resizeHitBox.h};
        SDL_Rect rects[2] = {crossRect, minRect};

        SDL_Color control = w->style.control;
        SDL_Color border = w->style.border;
        SDL_Color enabled = w->style.enabled;
        SDL_Color disabled = w->style.disabled;

        SDL_SetRenderDrawColor(render, control.r, control.g, control.b, control.a);
        SDL_RenderFillRects(render, rects, 2);

        SDL_SetRenderDrawColor(render, border.r, border.g, border.b, border.a);
        SDL_RenderDrawRects(render, rects, 2);

        //cross
        if(w->CanClose())
            SDL_SetRenderDrawColor(render, enabled.r, enabled.g, enabled.b, enabled.a);
        else
            SDL_SetRenderDrawColor(render, disabled.r, disabled.g, disabled.b, disabled.a);

        SDL_RenderDrawLine(render, crossRect.x + hmargin, crossRect.y + vmargin, crossRect.x + crossRect.w - hmargin, crossRect.y + crossRect.h - vmargin);
        SDL_RenderDrawLine(render, crossRect.x + hmargin, crossRect.y + crossRect.h - vmargin, crossRect.x + crossRect.w - hmargin, crossRect.y + vmargin);

        //minimize

        if(w->CanMinimaze())
            SDL_SetRenderDrawColor(render, enabled.r, enabled.g, enabled.b, enabled.a);
        else
            SDL_SetRenderDrawColor(render, disabled.r, disabled.g, disabled.b, disabled.a);

        SDL_RenderDrawLine(render, minRect.x + hmargin, minRect.y + HEADER_HEIGHT / 2, minRect.x + minRect.w - hmargin, minRect.y + HEADER_HEIGHT / 2);
    
        //resize

        if(w->CanResize() && !w->IsMinimazed()){
            SDL_SetRenderDrawColor(render, BLACK);

            SDL_Point points[4] = {{resRect.x, resRect.y + resRect.h - 2}, {resRect.x + resRect.w - 1, resRect.y - 1},
                                   {resRect.x + resRect.w - 1, resRect.y + resRect.h - 2}, {resRect.x, resRect.y + resRect.h - 2}};
            
            SDL_RenderDrawLines(render, points, 4);
        }
    }

    void Core::ProcessMouse(SDL_Event event){
        if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP){
            ClickMouse(event);
        }else if(event.type == SDL_MOUSEMOTION){
            if(event.motion.state == SDL_BUTTON_LMASK)
                DragMouse(event);
            else
                MoveMouse(event);
        }
    }

    void Core::MoveMouse(SDL_Event event){
        Window* currentFocus = group->CurrentFocus();

        int x = event.motion.x;
        int y = event.motion.y;

        mousePosition = {x, y};

        if(currentFocus->IsVisible()){
            currentFocus->ProcessGlobalMove(event.motion);
        }

        if(InWindow(currentFocus, x, y) && currentFocus->IsVisible()){
            event.motion.x -= currentFocus->GetRect().x;
            event.motion.y -= currentFocus->GetRect().y;

            currentFocus->ProcessMove(event.motion);
        }
    }

    void Core::DragMouse(SDL_Event event){
        Window* currentFocus = group->CurrentFocus();

        int x = event.motion.x;
        int y = event.motion.y;

        mousePosition = {x, y};

        if(currentFocus->IsVisible()){
            currentFocus->ProcessGlobalDrag(event.motion);
        }

        if(InWindow(currentFocus, x, y) && currentFocus->IsVisible()){
            event.motion.x -= currentFocus->GetRect().x;
            event.motion.y -= currentFocus->GetRect().y;

            currentFocus->ProcessDrag(event.motion);
        }        
    }

    void Core::ClickMouse(SDL_Event event){
        int x = event.button.x;
        int y = event.button.y;

        vector<Window*> windowPull = group->GetPull();
        vector<Window*> invertPull = vector<Window*>();

        while(windowPull.size() != 0){
            invertPull.push_back(windowPull.back());
            windowPull.pop_back();
        }

        for(Window* w : invertPull){
            if(w->IsVisible()){
                if(InWindow(w, x, y)){
                    if(w != group->CurrentFocus()){
                        group->FocusWindow(w);
                    }

                    w->ProcessGlobalClick(event.button);

                    event.button.x -= w->GetRect().x;
                    event.button.y -= w->GetRect().y;

                    w->ProcessClick(event.button);
                    break;
                }
            }
        }
    }

    IWindowsGroup* Core::GetGroup(){
        return group;
    }

    void Core::SetMainWindow(Window* w){
        mainWindow = w;
    }

    bool Core::IsRunning(){
        return isRunning;
    }

    void Core::Stop(){
        isRunning = false;
    }

    bool Core::InWindow(Window* w, int x, int y){
        SDL_Rect rect = w->GetRect();
        int left = rect.x;
        int right = rect.x + rect.w;
        int top = rect.y;
        int bottom = rect.y + rect.h + HEADER_HEIGHT;

        if(w->IsMinimazed()){
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

    bool Core::CreateWindow(){
        window = SDL_CreateWindow(
            "AbyssVision", 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            RESOLUTION_X, 
            RESOLUTION_Y, 
            0
        );

        if(!window)
            return false;
        return true;
    }

    bool Core::CreateRenderer(){
        renderer = SDL_CreateRenderer(window, -1, RENDERER_FLAGS);

        if(!renderer)
            return false;
        return true;
    }

    void Core::DisposeWindow(){
        if(window){
            SDL_DestroyWindow(window);
        }
    }

    void Core::DisposeRenderer(){
        if(renderer){
            SDL_DestroyRenderer(renderer);
        }
    }
}

