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
            Button* slide;
            Button* full;

        private:
            EmptyWindow* window;

        public:
            MainWindow();

        friend void Open(Widget* sender, ActionEvent event);
        friend void Hide(Widget* sender, ActionEvent event);
        friend void MoveAction(Widget* sender, ActionEvent event);
        friend void FullAction(Widget* sender, ActionEvent event);
            
    };
}

#endif