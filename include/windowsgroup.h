#ifndef WINDOWSGROUP_H
#define WINDOWSGROUP_H

#include <SDL.h>
#include <window.h>
#include <vector>

#define START_ID 0

using namespace std;

namespace AbyssCore{
    class IWindowsGroup{
        protected:
            virtual int FreeID() = 0;

        public:
            virtual vector<Window*> GetPull() = 0;
            virtual bool Create(Window* window, AString* byName) = 0;
            virtual bool Destroy(Window* window) = 0;
            virtual Window* Find(AString* byName) = 0;
            virtual Window* Find(int byID) = 0;
            virtual void FocusWindow(Window* window) = 0;
            virtual Window* CurrentFocus() = 0;
            virtual void ProcessWindows() = 0;
    };
}

#endif