#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <window.h>
#include <emptywindow.h>
#include <button.h>

namespace AbyssCore{
    class MainWindow : public Window{
        private:
            Button* open;
            Button* hide;

        public:
            EmptyWindow* window;

        public:
            MainWindow();
    };
}

#endif