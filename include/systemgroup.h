#ifndef SYSTEMGROUP_H
#define SYSTEMGROUP_H

#include <windowsgroup.h>
#include <list>

using namespace std;

namespace AbyssCore{
    class SystemGroup : public IWindowsGroup{
        private:
            list<Window*> windowsPull;
            Window* background;

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
            virtual void SetBackground(Window* window);
            virtual Window* CurrentFocus();
            virtual Window* Background();
            virtual void ProcessWindows();
    };
}

#endif