#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <window.h>
#include <emptywindow.h>
#include <widgets/button.h>
#include <widgets/trackbar.h>
#include <resources.h>

namespace AbyssCore{
    /**
     * \brief Main window class for debugging new features
     */
    class MainWindow : public Window{
        private:
            Button* open;
            Button* hide;
            Button* slide;
            Button* full;
            Trackbar* trackbar;

        private:
            EmptyWindow* window;
            unsigned int ozzenVAO, ozzenVBO;
            double currentSize;

        public:
            MainWindow();
            void Paint(Anchor anchor);

        friend void Open(Widget* sender, ActionEvent event);
        friend void Hide(Widget* sender, ActionEvent event);
        friend void MoveAction(Widget* sender, ActionEvent event);
        friend void FullAction(Widget* sender, ActionEvent event);
            
    };
}

#endif