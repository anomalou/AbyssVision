#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <window.h>
#include <emptywindow.h>
#include <widgets/button.h>
#include <widgets/trackbar.h>
#include <widgets/lineedit.h>
#include <resources.h>

namespace MediumCore{
    /**
     * \brief Main window class for debugging new features
     */
    class MainWindow : public Window{
        private:
            Trackbar* trackbar;
            LineEdit* lineedit;

        private:
            EmptyWindow* window;

        public:
            MainWindow();
            void Paint(Renderer &anchor);
            
    };
}

#endif