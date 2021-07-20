#ifndef SYSTEMGROUP_H
#define SYSTEMGROUP_H

#include <windowsgroup.h>
#include <vector>

using namespace std;

namespace AbyssCore{
    class SystemGroup : public IWindowsGroup{
        private:
            vector<Window*> windowsPull;
            Window* focus;

        protected:
            virtual int FreeID();

        public:
            SystemGroup();
            virtual vector<Window*> GetPull();
            virtual bool Create(Window* window, AString* byName);
            virtual bool Destroy(Window* window);
            virtual Window* Find(AString* byName);
            virtual Window* Find(int byID);
            virtual void FocusWindow(Window* window);
            virtual Window* CurrentFocus();
            virtual void ProcessWindows();
    };
}

#endif