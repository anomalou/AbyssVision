#ifndef SYSTEMGROUP_H
#define SYSTEMGROUP_H

#include <windowsgroup.h>
#include <list>

using namespace std;

namespace MediumCore{
    class SystemGroup : public IWindowsGroup{
        private:
            list<Window*> windowsPull;

        public:
            SystemGroup();
            virtual vector<Window*> GetPull();
            virtual vector<Window*> GetInvertedPull();
            virtual bool Create(Window* window, string byName);
            virtual bool Destroy(Window* window);
            virtual Window* Find(string byName);
            virtual void FocusWindow(Window* window);
            // virtual void SetBackground(Window* window);
            virtual Window* CurrentFocus();
            // virtual Window* Background();
            virtual void ProcessWindows();
    };
}

#endif