#include <systemgroup.h>

namespace AbyssCore{
    SystemGroup::SystemGroup(){
        windowsPull = list<Window*>();
        background = NULL;
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

    vector<Window*> SystemGroup::GetInvertedPull(){
        vector<Window*> windowPull = GetPull();
        vector<Window*> invertPull = vector<Window*>();

        while(windowPull.size() != 0){
            invertPull.push_back(windowPull.back());
            windowPull.pop_back();
        }

        return invertPull;
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

        return NULL;
    }

    Window* SystemGroup::Find(int byID){
        for(Window* w : windowsPull){
            if(w->GetID() == byID){
                return w;
            }
        }

        return NULL;
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

    void SystemGroup::SetBackground(Window* window){
        if(window != NULL)
            window->SetFull(false);
        background = window;        
    }

    Window* SystemGroup::CurrentFocus(){
        if(windowsPull.size() > 0)
            return windowsPull.back();
        return NULL;
    }

    Window* SystemGroup::Background(){
        return background;
    }

    void SystemGroup::ProcessWindows(){
        for(auto i = windowsPull.begin(); i != windowsPull.end() && windowsPull.size() > 1; i++){
            if((*i)->NeedDestroy())
                Destroy(*i);
        }
    }
}