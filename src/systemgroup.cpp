#include <systemgroup.h>

namespace AbyssCore{
    SystemGroup::SystemGroup(){
        windowsPull = list<Window*>();
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

    bool SystemGroup::Create(Window* window, string byName){
        if(window == nullptr)
            return false;

        for(Window* w : windowsPull){
            if(strcmp(byName.c_str(), w->GetName().c_str()) == 0)
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
                return true;
            }
        }
        return false;
    }

    Window* SystemGroup::Find(string byName){
        for(Window* w : windowsPull){
            if(strcmp(w->GetName().c_str(), byName.c_str()) == 0){
                return w;
            }
        }

        return NULL;
    }

    void SystemGroup::FocusWindow(Window* window){
        for(auto w = windowsPull.begin(); w != windowsPull.end(); w++){
            if(*w == window){
                windowsPull.erase(w);
                windowsPull.push_back(window);
                break;
            }
        }
    }

    Window* SystemGroup::CurrentFocus(){
        if(windowsPull.size() > 0)
            return windowsPull.back();
        return NULL;
    }

    void SystemGroup::ProcessWindows(){
        vector<Window*> toDestroy = vector<Window*>();
        for(auto i = windowsPull.begin(); i != windowsPull.end(); i++){
            if((*i)->NeedDestroy())
                toDestroy.push_back(*i);
        }

        for(Window* w : toDestroy){
            Destroy(w);
        }
    }
}