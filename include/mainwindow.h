#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <window.h>
#include <button.h>

namespace AbyssCore{
    class MainWindow : public Window{
        private:
            Button* button;

        public:
            MainWindow();
    };
}

#endif