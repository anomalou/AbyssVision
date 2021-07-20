#include "core.h"

using namespace std;

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

        return true;
    }

    void Core::Start(){
        isRunning = true;

        RenderPtrs* ptrs = (RenderPtrs*)malloc(sizeof(RenderPtrs));
        ptrs->corePtr = this;

        renderThread = SDL_CreateThread(Render, "input", ptrs);

        //TODO: testing windows here

        Window* window = new MainWindow();
        Window* test = new MainWindow();
        window->SetRect(SDL_Rect({0, 0, 500, 100}));
        test->SetRect(SDL_Rect({100, 100, 500, 200}));


        group->Create(window, new AString("main_window"));
        group->Create(test, new AString("test"));
        group->FocusWindow(window);
        test->AllowClose(true);
        test->AllowMinimaze(false);
        test->AllowResize(true);
        test->SetVisible(true);
        window->AllowResize(true);
        window->SetVisible(true);

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
            SDL_SetRenderDrawColor(render, WHITE);
            SDL_RenderClear(render);

            for(Window* w : group->GetPull()){
                if(w != group->CurrentFocus()){
                    renderPtrs->corePtr->DrawWindow(render, w);
                }
            }

            Window* currentFocus = group->CurrentFocus();

            renderPtrs->corePtr->DrawWindow(render, currentFocus);

            SDL_RenderPresent(render);
            SDL_Delay(1000/FPS);
        }

        return 0;
    }

    void Core::DrawWindow(SDL_Renderer* render, Window* w){
        DrawWindowHead(render, w);
        if(!w->IsMinimazed())
            DrawWindowBody(render, w);
        DrawWindowControl(render, w);
    }

    void Core::DrawWindowHead(SDL_Renderer *render, Window* w){
        int x = w->GetRect().x;
        int y = w->GetRect().y;
        int width = w->GetRect().w;
        int height = HEADER_HEIGHT;
        SDL_Rect* rect = new SDL_Rect();
        rect->x = x;
        rect->y = y;
        rect->w = width;
        rect->h = height;

        if(group->CurrentFocus() == w)
            SDL_SetRenderDrawColor(render, WHITE);
        else
            SDL_SetRenderDrawColor(render, GRAY);
        SDL_RenderFillRect(render, rect);
        SDL_SetRenderDrawColor(render, BLACK);
        SDL_RenderDrawRect(render, rect);

        rect->x = x + FSIGN_WIDTH / 2;
        rect->y = y + FSIGN_HEIGHT / 2;
        rect->w = FSIGN_WIDTH * w->GetName()->Length();
        rect->h = FSIGN_HEIGHT;

        if((rect->w + FSIGN_WIDTH / 2) > w->GetRect().w)
            rect->w = w->GetRect().w - FSIGN_WIDTH / 2;

        SDL_Color color = {BLACK};

        SDL_Surface* surface = TTF_RenderText_Solid(font, w->GetName()->ToChars(), color);

        SDL_Texture* header = SDL_CreateTextureFromSurface(render, surface);

        SDL_RenderCopy(render, header, NULL, rect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(header);
    }

    void Core::DrawWindowBody(SDL_Renderer *render, Window* w){
        SDL_Rect rect = {w->GetRect().x, w->GetRect().y + HEADER_HEIGHT - 1, w->GetRect().w, w->GetRect().h};

        SDL_Color windowColor = w->GetColor();

        SDL_SetRenderDrawColor(render, windowColor.r, windowColor.g, windowColor.b, windowColor.a);
        SDL_RenderFillRect(render, &rect);

        SDL_SetRenderDrawColor(render, BLACK);
        SDL_RenderDrawRect(render, &rect);

        for(Widget* w : w->GetPull()){
            SDL_Rect wrect = w->GetRect();
            wrect.x += rect.x;
            wrect.y += rect.y;

            if(wrect.x < 0){
                wrect.w += wrect.x;
                wrect.x += abs(wrect.x);
            }
            
            if((wrect.x + wrect.w) > (rect.x + rect.w))
                wrect.w -= (wrect.x + wrect.w) - (rect.x + rect.w);

            if(wrect.y < 0){
                wrect.h += wrect.y;
                wrect.y += abs(wrect.y);
            }

            if((wrect.y + wrect.h) > (rect.y + rect.h))
                wrect.h -= (wrect.y + wrect.h) - (rect.y + rect.h);

            SDL_Color widgetColor = w->GetColor();

            SDL_SetRenderDrawColor(render, widgetColor.r, widgetColor.g, widgetColor.b, widgetColor.a);
            SDL_RenderFillRect(render, &wrect);

            SDL_SetRenderDrawColor(render, BLACK);
            SDL_RenderDrawRect(render, &wrect);
        }
    }

    void Core::DrawWindowControl(SDL_Renderer * render, Window* w){
        SDL_Rect wRect = w->GetRect();

        int hmargin = (CBUTTON_WIDTH - CSIGN_SIZE) / 2;
        int vmargin = (HEADER_HEIGHT - CSIGN_SIZE) / 2;

        SDL_Rect closeHitBox = w->GetCloseHitBox();
        SDL_Rect minimazeHitBox = w->GetMinimazeHitBox();
        SDL_Rect resizeHitBox = w->GetResizeHitBox();

        SDL_Rect crossRect = {wRect.x + closeHitBox.x, wRect.y + closeHitBox.y, closeHitBox.w, closeHitBox.h};
        SDL_Rect minRect = {wRect.x + minimazeHitBox.x, wRect.y + minimazeHitBox.y, minimazeHitBox.w, minimazeHitBox.h};
        SDL_Rect resRect = {wRect.x + resizeHitBox.x, wRect.y + resizeHitBox.y, resizeHitBox.w, resizeHitBox.h};
        SDL_Rect rects[2] = {crossRect, minRect};

        SDL_SetRenderDrawColor(render, WHITE);
        SDL_RenderFillRects(render, rects, 2);

        SDL_SetRenderDrawColor(render, BLACK);
        SDL_RenderDrawRects(render, rects, 2);

        //cross
        if(w->CanClose())
            SDL_SetRenderDrawColor(render, BLACK);
        else
            SDL_SetRenderDrawColor(render, RED);

        SDL_RenderDrawLine(render, crossRect.x + hmargin, crossRect.y + vmargin, crossRect.x + crossRect.w - hmargin, crossRect.y + crossRect.h - vmargin);
        SDL_RenderDrawLine(render, crossRect.x + hmargin, crossRect.y + crossRect.h - vmargin, crossRect.x + crossRect.w - hmargin, crossRect.y + vmargin);

        //minimize

        if(w->CanMinimaze())
            SDL_SetRenderDrawColor(render, BLACK);
        else
            SDL_SetRenderDrawColor(render, RED);

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

        if(InWindow(currentFocus, x, y) && currentFocus->IsVisible())
            currentFocus->ProcessMove(event.motion);
    }

    void Core::DragMouse(SDL_Event event){
        Window* currentFocus = group->CurrentFocus();

        int x = event.motion.x;
        int y = event.motion.y;

        if(InWindow(currentFocus, x, y) && currentFocus->IsVisible())
            currentFocus->ProcessDrag(event.motion);
    }

    void Core::ClickMouse(SDL_Event event){
        int x = event.button.x;
        int y = event.button.y;

        Window* currentFocus = group->CurrentFocus();

        //mouse button down

        if(event.type == SDL_MOUSEBUTTONDOWN){
            if(InWindow(currentFocus, x, y) && currentFocus->IsVisible()){
                currentFocus->ProcessClick(event.button);
                return;
            }

            for(Window* w : group->GetPull()){
                SDL_Rect rect = w->GetRect();

                if(InWindow(w, x, y) && w->IsVisible()){
                    if(w != group->CurrentFocus()){
                        group->FocusWindow(w);
                        break;
                    }
                }
            }
        }
    }

    IWindowsGroup* Core::GetGroup(){
        return group;
    }

    bool Core::IsRunning(){
        return isRunning;
    }

    bool Core::InWindow(Window* w, int x, int y){
        SDL_Rect rect = w->GetRect();

        if(w->IsMinimazed()){
            if(x > rect.x && x < (rect.x + rect.w) && y > rect.y && y < (rect.y + HEADER_HEIGHT))
                return true;
        }else{
            if(x > rect.x && x < (rect.x + rect.w) && y > rect.y && y < (rect.y + rect.h + HEADER_HEIGHT))
                return true;
        }

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

