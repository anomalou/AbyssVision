#include <systemgroup.h>

namespace AbyssCore{
    SystemGroup::SystemGroup(){
        windowsPull = list<Window*>();
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
        vector<Window*> pull = vector<Window*>();

        for(Window* w : windowsPull){
            pull.push_back(w);
        }

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
        for(auto w = windowsPull.begin(); w != windowsPull.end(); w++){
            if(*w == window){
                windowsPull.erase(w);
                // if(window == focus)
                //     focus = windowsPull.back();
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
        // focus = window;
        for(auto w = windowsPull.begin(); w != windowsPull.end(); w++){
            if(*w == window){
                windowsPull.erase(w);
                windowsPull.push_back(window);
                break;
            }
        }
    }

    Window* SystemGroup::CurrentFocus(){
        return windowsPull.back();
    }

    void SystemGroup::ProcessWindows(){
        for(Window* w : windowsPull){
            if(w->NeedDestroy())
                Destroy(w);
        }
    }
}