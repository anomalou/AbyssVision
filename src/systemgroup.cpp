#include <systemgroup.h>

namespace AbyssCore{
    SystemGroup::SystemGroup(){
        windowsPull = vector<Window*>();
    }

    int SystemGroup::FreeID(){
        int max = START_ID;
        for(Window* w : windowsPull){
            if(w->GetID() > max)
                max = w->GetID();
        }

        return max;
    }

    vector<Window*> SystemGroup::GetPull(){
        vector<Window*> pull = vector<Window*>(windowsPull);

        return pull;
    }

    bool SystemGroup::Create(Window* window, AString* byName){
        if(window == nullptr)
            return false;

        for(Window* w : windowsPull){
            if(strcmp(byName->ToChars(), w->GetName()->ToChars()) == 0)
                return false;
        }

        window->SetName(byName);
        windowsPull.push_back(window);

        return true;
    }

    bool SystemGroup::Destroy(Window* window){
        for(size_t i = 0; i < windowsPull.size(); i++){
            if(windowsPull[i] == window){
                windowsPull.erase(windowsPull.begin() + i);
                if(window == focus)
                    focus = windowsPull.back();
                return true;
            }
        }
        return false;
    }

    Window* SystemGroup::Find(AString* byName){
        for(Window* w : windowsPull){
            if(strcmp(w->GetName()->ToChars(), byName->ToChars()) == 0){
                return w;
            }
        }

        return nullptr;
    }

    Window* SystemGroup::Find(int byID){
        for(Window* w : windowsPull){
            if(w->GetID() == byID){
                return w;
            }
        }

        return nullptr;
    }

    void SystemGroup::FocusWindow(Window* window){
        focus = window;
    }

    Window* SystemGroup::CurrentFocus(){
        return focus;
    }

    void SystemGroup::ProcessWindows(){
        for(Window* w : windowsPull){
            if(w->NeedDestroy())
                Destroy(w);
        }
    }
}